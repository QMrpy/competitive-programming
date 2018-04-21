
# Highway Crossing
# https://www.codechef.com/APRIL18A/problems/HIGHWAYC
# O(N) per test case

EPS = 1e-6
for t in range(int(input())):
    N, S, Y = map(int, input().split())
    V = list(map(int, input().split()))
    D = list(map(int, input().split()))
    V = [Vi if Di else -Vi for Vi, Di in zip(V, D)]
    P = list(map(int, input().split()))
    C = list(map(int, input().split()))

    arr = [-Pi / Vi - EPS for Pi, Vi in zip(P, V)]
    dep = [-Pi / Vi + Ci / abs(Vi) + EPS for Pi, Ci, Vi in zip(P, C, V)]

    cur = 0
    for i in range(N):
        nxt = cur + Y / S
        cur = nxt if dep[i] < cur or arr[i] > nxt else dep[i] + Y / S
    print('{:.4f}'.format(cur))