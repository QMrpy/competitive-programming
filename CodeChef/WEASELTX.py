
# Weasel does Xor on Tree 
# https://www.codechef.com/SEPT17/problems/WEASELTX

from collections import deque

N, Q = map(int, input().split())
g = [[] for i in range(N)]
for i in range(N-1):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)
    
X0 = list(map(int, input().split()))
A = [0] * N
P = 0
q = deque()
q.append((0, -1, 0))
while q:
    u, p, d = q.popleft()
    P = d
    A[d] ^= X0[u]
    for v in g[u]:
        if v != p:
            q.append((v, u, d+1))

P += 1
B = P.bit_length()
P = 1 << P.bit_length()
A += [0] * (P - len(A))

for b in range(B):
    j = 1 << b
    j2 = j << 1
    for i in range(0, P, j2):
        L = A[i:i+j]
        R = A[i+j:i+j2]
        A[i:i+j] = [Lk ^ Rk for Lk, Rk in zip(L, R)]
        A[i+j:i+j2] = L

for q in range(Q):
    d = int(input())
    d = (d - 1) % P
    print(A[d])
