
# String Merging
# https://www.codechef.com/JAN18/problems/STRMRG
# Dynamic programming, O(NM)

# Python time limit too strict
# Submitted with compiler as Pypy 2
input = raw_input
range = xrange

INF = 10**9
for t in range(int(input())):
    N, M = map(int, input().split())
    A = '$' + input().strip()
    B = '$' + input().strip()

    dpA = [[0] * (M+1) for i in range(N+1)]
    dpB = [[0] * (M+1) for i in range(N+1)]
    for i in range(1, N+1):
        dpA[i][0] = dpA[i-1][0] + (A[i] != A[i-1])
        dpB[i][0] = INF
    for j in range(1, M+1):
        dpA[0][j] = INF
        dpB[0][j] = dpB[0][j-1] + (B[j] != B[j-1])
    for i in range(1, N+1):
        for j in range(1, M+1):
            x = dpA[i-1][j] + (A[i] != A[i-1])
            y = dpB[i-1][j] + (A[i] != B[j])
            dpA[i][j] = min(x, y)
            x = dpA[i][j-1] + (B[j] != A[i])
            y = dpB[i][j-1] + (B[j] != B[j-1])
            dpB[i][j] = min(x, y)

    ans = min(dpA[N][M], dpB[N][M])
    print(ans)