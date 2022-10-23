import math


def get_ints(N):
    result = [int(i) for i in input().split()]
    assert(len(result) == N)
    return result


def get_ints_matrix(N, M):
    result = [[int(i) for i in input().split()] for j in range(N)]
    assert(len(result) == N)
    for i in result:
        assert(len(i) == M)
    return result


def get_lines(N):
    result = [input() for i in range(N)]
    assert(len(result) == N)
    return result


def distance_helper(x, y, fold, inner):
    return fold(map(lambda ab: inner(ab[0] - ab[1]), zip(x, y)))


distances = {
    'manhattan': (lambda x, y: distance_helper(x, y, sum, abs)),
    'euclidean': (lambda x, y: math.sqrt(distance_helper(x, y, sum, lambda u: u ** 2))),
    'chebyshev': (lambda x, y: distance_helper(x, y, max, abs)),
}

kernels = {
    'uniform':      (lambda u: 0.5),
    'triangular':   (lambda u: 1 - abs(u)),
    'epanechnikov': (lambda u: 0.75 * (1 - u ** 2)),
    'quartic':      (lambda u: (15 / 16) * (1 - u ** 2) ** 2),
    'triweight':    (lambda u: (35 / 32) * (1 - u ** 2) ** 3),
    'tricube':      (lambda u: (70 / 81) * (1 - abs(u) ** 3) ** 3),
    'gaussian':     (lambda u: (math.e ** (-0.5 * u ** 2) / math.sqrt(2 * math.pi))),
    'cosine':       (lambda u: math.cos(math.pi * u / 2) * math.pi / 4),
    'logistic':     (lambda u: 1 / (math.e ** u + 2 + math.e ** (-u))),
    'sigmoid':      (lambda u: 2 / (math.pi * (math.e ** u + math.e ** (-u)))),
}


def simple_goal(objects):
    return sum(map(lambda x: x[-1], objects)) / len(objects)


def resolve(objects, target, distance, kernel, window, window_value):
    k = kernels[kernel]
    d = distances[distance]

    objects.sort(key=lambda x: d(x, target))
    if window == "fixed":
        h = window_value
    else:
        h = d(objects[window_value], target)

    def w(x):
        t = d(x, target) / h
        if (t < 1 or kernel == "sigmoid" or kernel == "gaussian" or kernel == "logistic"):
            return k(t)
        else:
            return 0

    goal = simple_goal(objects)

    if h == 0:
        filtered = list(filter(lambda x: d(x, target) == 0, objects))
        if len(filtered) != 0:
            return simple_goal(filtered)

        return goal

    a = sum(map(lambda x: x[-1] * w(x), objects))
    b = sum(map(w, objects))

    return a / b if b != 0 else goal


if __name__ == '__main__':
    [N, M] = get_ints(2)
    objects = get_ints_matrix(N, M + 1)
    target = get_ints(M)
    [distance, kernel, window] = get_lines(3)
    [window_value] = get_ints(1)
    print(resolve(objects, target, distance, kernel, window, window_value))
