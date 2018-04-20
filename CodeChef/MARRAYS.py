
# Chef and Magic Arrays
# https://www.codechef.com/OCT17/problems/MARRAYS

INF = 10**15

for t in range(int(input())):
    N = int(input())
    A = [list(map(int, input().split()))[1:] for i in range(N)]
    M = [len(Ai) for Ai in A]

    dp_firstpos = [-INF]*N
    dp_firstneg = [-INF]*N
    dp_firstpos[N-1] = max(A[N-1])*(N-1)
    dp_firstneg[N-1] = -min(A[N-1])*(N-1)

    for i in range(N-2, -1, -1):
        for j in range(M[i]):
            lastpos = A[i][j-1]*(i+1) + dp_firstneg[i+1]
            lastneg = -A[i][j-1]*(i+1) + dp_firstpos[i+1]
            firstpos = A[i][j]*i
            firstneg = -A[i][j]*i
            dp_firstpos[i] = max(dp_firstpos[i], firstpos+lastpos, firstpos+lastneg)
            dp_firstneg[i] = max(dp_firstneg[i], firstneg+lastpos, firstneg+lastneg)

    ans = max(dp_firstpos[0], dp_firstneg[0])
    print(ans)
