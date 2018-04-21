
# Count Good Prefixes
# https://www.codechef.com/APRIL18A/problems/GOODPREF/
# O(|S|^2)

for t in range(int(raw_input())):
    S, N = raw_input().split()
    N = int(N)

    M = len(S) * min(len(S), N)
    ans = dif = one = 0
    for j in xrange(min(len(S), N)):
        for i, c in enumerate(S):
            dif += 1 if c == 'a' else -1
            if dif > 0: ans += 1
        if j == 0 and dif == 0: one = ans
    if N > len(S):
        if dif == 0: ans += one * (N - len(S))
        if dif > 0: ans += len(S) * (N - len(S))
    print(ans)