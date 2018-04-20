
# Max Mex
# https://www.codechef.com/OCT17/problems/MEX

for t in range(int(input())):
    N, K = map(int, input().split())
    s = set(map(int, input().split()))
    for i in range(10**9):
        if i not in s:
            if K > 0:
                K -= 1
            else:
                ans = i
                break
    print(ans)
