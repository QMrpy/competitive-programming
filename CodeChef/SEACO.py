
# Sereja and Commands
# https://www.codechef.com/SEPT17/problems/SEACO

MOD = 10**9 + 7

class SegTree:
    
    def __init__(self, n):
        self.N = 1 << n.bit_length()
        self.tree = [0] * (self.N<<1)
    
    def update(self, i, j, v):
        i += self.N
        j += self.N
        while i <= j:
            if i%2==1: self.tree[i] += v
            if j%2==0: self.tree[j] += v
            i, j = (i+1) >> 1, (j-1) >> 1
    
    def query(self, i):
        v = 0
        i += self.N
        while i > 0:
            v += self.tree[i]
            i >>= 1
        return v
    
for t in range(int(input())):
    n, m = map(int, input().split())
    sa = SegTree(n)
    sq = SegTree(m)
    Q = [None] + [list(map(int, input().split())) for i in range(m)]
    for i in range(m, 0, -1):
        t, l, r = Q[i]
        c = sq.query(i) + 1
        if t==1: sa.update(l, r, c)
        else: sq.update(l, r, c)
        
    a = [sa.query(i) % MOD for i in range(1, n+1)]
    print(*a)