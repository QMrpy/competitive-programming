
# Maximum Score
# https://www.codechef.com/JAN18/problems/MAXSC
# Greedy

from bisect import bisect_left
for t in range(int(input())):
    n = int(input())
    a = [sorted(list(map(int, input().split()))) for i in range(n)]
    s = 0
    p = 10**10
    for ai in reversed(a):
        j = bisect_left(ai, p) - 1
        if j == -1:
            s = -1
            break
        s += ai[j]
        p = ai[j]
    print(s)

