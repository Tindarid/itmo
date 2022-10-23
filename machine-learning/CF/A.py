def get_ints():
    return map(int, input().split())


[N, M, K] = get_ints()
objects = list(enumerate(get_ints(), start=1))
assert(len(objects) == N)

objects.sort(key=lambda o: o[1])
buckets = [[] for x in range(K)]

for ind in range(N):
    buckets[ind % K].append(objects[ind][0])

for b in buckets:
    print(str(len(b)) + " " + " ".join(map(str, b)))
