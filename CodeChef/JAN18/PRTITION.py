
# Partition the numbers
# https://www.codechef.com/JAN18/problems/PRTITION

for t in range(int(input())):
    x, N = map(int, input().split())
    s = N * (N+1) // 2 - x
    bad = 1
    if s % 2 == 0:
        mark = ['0'] * (N+1)
        c = 0
        s //= 2
        for i in range(N, 0, -1):
            if i == x:
                mark[x] = '2'
            elif c+i <= s and (x != 1 and x != 2 or c+i != s-x):
                c += i
                mark[i] = '1'
        if c == s:
            bad = 0

    if bad: print('impossible')
    else: print(''.join(mark[1:]))
