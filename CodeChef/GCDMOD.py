
# Modular GCD
# https://www.codechef.com/AUG18A/problems/GCDMOD

from math import gcd
MOD = 10 ** 9 + 7

for t in range(int(input())):
    A, B, N = map(int, input().split())
    d = abs(A - B)
    if d == 0:
        ans = (pow(A, N, MOD) + pow(B, N, MOD)) % MOD
    else:
        s = pow(A, N, d) + pow(B, N, d)
        ans = gcd(d, s) % MOD
    print(ans)
