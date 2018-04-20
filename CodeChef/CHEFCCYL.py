
# Chef and Cycled Cycles
# https://www.codechef.com/OCT17/problems/CHEFCCYL

for t in range(int(input())):
    N, Q = map(int, input().split())
    E = [list(map(int, input().split()))[1:] for i in range(N)]
    L, R, W = [0]*N, [0]*N, [0]*N
    for i in range(N):
        v1, v2, W[i] = map(int, input().split())
        R[i], L[(i+1)%N] = v1-1, v2-1

    def filldist(Ei, src, dist):
        n = len(Ei)
        d = 0
        cur = (src+1)%n
        while cur != src:
            d += Ei[(cur-1)%n]
            dist[cur] = d
            cur = (cur+1)%n
        d = 0
        cur = (src-1)%n
        while cur != src:
            d += Ei[cur]
            dist[cur] = min(dist[cur], d)
            cur = (cur-1)%n

    Ldist = [[0]*len(Ei) for Ei in E]
    Rdist = [[0]*len(Ei) for Ei in E]
    for i in range(N):
        filldist(E[i], L[i], Ldist[i])
        filldist(E[i], R[i], Rdist[i])

    jump = [Rdist[i][L[i]] + W[i] for i in range(N)]
    pre = [0]*(N+1)
    for i in range(N):
        pre[i] = pre[i-1] + jump[i]

    for q in range(Q):
        v1, c1, v2, c2 = map(int, input().split())
        v1, c1, v2, c2 = v1-1, c1-1, v2-1, c2-1
        if c2 < c1:
            v1, c1, v2, c2 = v2, c2, v1, c1

        dist1 = Rdist[c1][v1] + W[c1] + pre[c2-1] - pre[c1] + Ldist[c2][v2]
        dist2 = Rdist[c2][v2] + W[c2] + pre[N-1] - pre[c2] + pre[c1-1] + Ldist[c1][v1]
        ans = min(dist1, dist2)
        print(ans)
