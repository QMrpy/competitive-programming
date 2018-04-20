
# Sum of Cubes
# https://www.codechef.com/problems/SUMCUBE

# Editorial's approach
# https://discuss.codechef.com/questions/108250/sumcube-editorial
# O(m ^ 1.5)


MOD = 10**9 + 7

def pow2(n):
    return 0 if n<0 else pow(2, n, MOD)

def getB():
    gs = [set(g_u) for g_u in g]
    es = set(e)
    B = [0]*(n+1)
    lim = m**0.5
    for u in range(1, n+1):
        if deg[u] < lim:
            B[u] = sum((v, w) in es for v in g[u] for w in g[u])
        else:
            B[u] = sum(v in gs[u] and w in gs[u] for (v, w) in e)
    return B

def solve3():
    a23, a24 = solve2(get_a23_a24=True)
    B = getB()
    tri = sum(B)
    claw = sum(deg_u*(deg_u-1)*(deg_u-2) for deg_u in deg)
    P4 = 3*sum((deg[u]-1)*(deg[v]-1) for u, v in e) - 3*tri

    a32 = m
    a33 = 3*a23 + tri
    a34 = 3*a24 + claw + P4
    a35 = 3*sum(deg[u]*(deg[u]-1)*(m-deg[u]+2)+B[u] - 2*(deg[u]-1)*sum(deg[v] for v in g[u]) for u in range(1, n+1))
    a36 = m*m*m - a32 - a33 - a34 - a35
    return (a32*pow2(n-2) + a33*pow2(n-3) + a34*pow2(n-4) + a35*pow2(n-5) + a36*pow2(n-6)) % MOD

def solve2(get_a23_a24=False):
    a22 = m
    a23 = sum(deg_u*(deg_u-1) for deg_u in deg)
    a24 = m*m - a22 - a23
    if get_a23_a24:
        return a23, a24
    return (a22*pow2(n-2) + a23*pow2(n-3) + a24*pow2(n-4)) % MOD

def solve1():
    return (m * pow2(n-2)) % MOD

T = int(input())
for t in range(T):
    n, m, k = map(int, input().split())
    e = []
    g = [[] for i in range(n+1)]
    for i in range(m):
        u, v = map(int, input().split())
        e.append((u, v))
        e.append((v, u))
        g[u].append(v)
        g[v].append(u)
    deg = [len(g_u) for g_u in g]

    ans = solve1() if k==1 else solve2() if k==2 else solve3()
    print(ans)