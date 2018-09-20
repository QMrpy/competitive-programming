
# Factorize
# https://www.codechef.com/SEPT18A/problems/FCTR

# Math stuff, see links under "Ref" for details

from random import randint
from math import gcd
import sys
sys.setrecursionlimit(10 ** 6)

MAX_LG = 1666

ispr = {}
primes = []

def init():
    global ispr, primes
    for i in range(2, MAX_LG):
        if i not in ispr:
            ispr[i] = True
            primes.append(i)
        for j in range(i * i, MAX_LG, i):
            ispr[j] = False

def solve(n, phi):
    e2 = 0
    while n & 1 == 0:
        n >>= 1
        e2 += 1
    if n == 1:
        return [(2, e2)]

    if e2: phi >>= e2 - 1
    if phi == n - 1:
        ans = [(n, 1)]
        if e2: ans.append((2, e2))
        return ans

    def perfect_pow(n):
        # Returns a, b such that a ^ b = n
        global primes
        l = n.bit_length() - 1
        for b in primes:
            if b > l: break
            k = l // b
            m = 1 << k
            for i in range(k - 1, -1, -1):
                cur = m + (1 << i)
                if cur ** b == n:
                    return cur, b
                if cur ** b < n:
                    m = cur
        return None

    small_primes = {2, 3, 5, 7, 11}
    def probablyprime(n):
        # Miller-Rabin primality test
        nonlocal small_primes
        global ispr
        if n in small_primes:
            return True
        if n in ispr:
            return ispr[n]
        if any(n % p == 0 for p in small_primes):
            return False
        t = n - 1
        h = 0
        while t & 1 == 0:
            t >>= 1
            h += 1
        # n - 1 = 2 ^ h * t
        for it in range(3):
            a = randint(2, n - 2)
            x = pow(a, t, n)
            if x == 1 or x == n - 1:
                continue
            for i in range(h - 1):
                x = x * x % n
                if x == n - 1:
                    break
            if x == n - 1:
                continue
            return False
        return True

    # Refs:
    # A Computational Introduction to Number Theory and Algebra, http://shoup.net/ntb/
    # https://groups.google.com/forum/#!topic/comp.theory/O3RXaAXQ9wg

    t = phi
    h = 0
    while t & 1 == 0:
        t >>= 1
        h += 1
    # phi = 2 ^ h * t

    ans = {}
    def recur(n):
        nonlocal t, h, ans

        if probablyprime(n):
            ans[n] = ans.get(n, 0) + 1
            return

        r = perfect_pow(n)
        if r:
            a, b = r
            for x in range(b):
                recur(a)
            return

        while True:
            alpha = randint(2, n - 1)
            d = gcd(alpha, n)
            if d != 1:
                break
            beta = pow(alpha, t, n)
            if beta == 1 or beta == n - 1:
                continue
            while True:
                beta2 = beta * beta % n
                if beta2 == 1:
                    break
                beta = beta2
            if beta == n - 1:
                continue
            d = gcd(beta + 1, n)
            assert d > 1
            break
            
        recur(d)
        recur(n // d)

    recur(n)
    if e2: ans[2] = e2
    return ans.items()

init()
for t in range(int(input())):
    n, phi = map(int, input().split())
    ans = solve(n, phi)
    ans = sorted(ans)
    print(len(ans))
    ans = ['{} {}'.format(p, e) for p, e in ans]
    print(*ans, sep='\n')
