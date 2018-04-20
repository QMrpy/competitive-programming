
# Chef goes Left Right Left
# https://www.codechef.com/problems/CLRL

for t in range(int(input())):
    N, R = map(int, input().split())
    A = list(map(int, input().split())) + [0]

    lo = 0
    hi = 10**9
    bad = False
    for i in range(N):
        if A[i] < lo or A[i] > hi:
            bad = True
            break
        if A[i+1] > A[i]:
            lo = max(lo, A[i])
        else:
            hi = min(hi, A[i])
    print('NO' if bad else 'YES')
