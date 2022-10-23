def safe_div(a, b):
    return a / b if b else 0


def harmonic(a, b):
    return safe_div(2 * a * b, a + b)


K = int(input())
CM = [[int(i) for i in input().split()] for j in range(K)]

# K = 2
# CM = [[0, 1], [1, 3]]

# K = 3
# CM = [[3, 1, 1], [3, 1, 1], [1, 3, 1]]

R = range(K)

C = [sum(CM[i]) for i in R]
ALL = sum(C)

TP = [CM[i][i] for i in R]
FP = [sum([CM[j][i] for j in R if i != j]) for i in R]
FN = [sum([CM[i][j] for j in R if i != j]) for i in R]
TN = [ALL - TP[i] - FP[i] - FN[i] for i in R]

P = [TP[i] + FP[i] for i in R]

prec = [safe_div(TP[i], P[i]) for i in R]
recall = [safe_div(TP[i], TP[i] + FN[i]) for i in R]
F = [harmonic(prec[i], recall[i]) for i in R]
microf = sum([C[i] * F[i] for i in R]) / ALL

precw = sum([safe_div(TP[i] * C[i], P[i]) for i in R]) / ALL
recallw = sum([TP[i] for i in R]) / ALL
macrof = harmonic(precw, recallw)

print(macrof)
print(microf)
