
# K-Concatenation
# https://www.codechef.com/JAN18/problems/KCON

for t in range(int(input())):
    N, K = map(int, input().split())
    A = list(map(int, input().split()))

    dp = [A[0]] * N
    for i in range(1, N):
        dp[i] = max(dp[i-1], 0) + A[i]
    ans = max(dp)

    if K > 1:
        B = A + A
        dp = [B[0]] * 2*N
        for i in range(1, 2*N):
            dp[i] = max(dp[i-1], 0) + B[i]
        ans = max(dp)
        ans = max(ans, ans + sum(A) * (K-2))

    print(ans)
