
# Subsequence Equality
# https://www.codechef.com/COOK86/problems/LIKECS01

from collections import Counter
for t in range(int(input())):
    S = input().strip()
    c = Counter(S)
    c, x = c.most_common(1)[0]
    print('yes' if x>1 else 'no')