
# Triple-tree decomposition
# https://www.codechef.com/problems/TREE3

# Approach attempts to eliminates leaves whenever possible,
# creating new leaves and decomposing the tree
# O(N)

for t in range(int(input())):
    N = int(input())
    G = [set() for i in range(N + 1)]
    for i in range(N - 1):
        u, v = map(int, input().split())
        G[u].add(v)
        G[v].add(u)

    leaves = [u for u in range(1, N + 1) if len(G[u]) == 1]
    cur = [set() for i in range(N + 1)]
    for leaf in leaves:
        p = G[leaf].pop()
        cur[p].add(leaf)

    cnt2, cnt3 = set(), set()
    for u in range(1, N + 1):
        if len(cur[u]) >= 3:
            cnt3.add(u)
        elif len(cur[u]) == 2 and len(G[u]) == 3:
            cnt2.add(u)

    ans = []
    while cnt3 or cnt2:
        while cnt3:
            u = cnt3.pop()
            leaf1, leaf2, leaf3 = cur[u].pop(), cur[u].pop(), cur[u].pop()
            ans.append((u, leaf1, leaf2, leaf3))
            G[u].remove(leaf1)
            G[u].remove(leaf2)
            G[u].remove(leaf3)
            if len(cur[u]) >= 3:
                cnt3.add(u)
            elif len(cur[u]) == 2 and len(G[u]) == 3:
                cnt2.add(u)
            if len(G[u]) == 1:
                p = G[u].pop()
                cnt2.discard(p)
                cnt3.discard(p)
                cur[p].add(u)
                if len(cur[p]) >= 3:
                    cnt3.add(p)
                elif len(cur[p]) == 2 and len(G[p]) == 3:
                    cnt2.add(p)
        
        while cnt2:
            u = cnt2.pop()
            leaf1, leaf2 = cur[u].pop(), cur[u].pop()
            G[u].remove(leaf1)
            G[u].remove(leaf2)
            leaf3 = G[u].pop()
            ans.append((u, leaf1, leaf2, leaf3))
            u, leaf3 = leaf3, u
            G[u].remove(leaf3)
            if len(G[u]) == 1:
                p = G[u].pop()
                cnt2.discard(p)
                cnt3.discard(p)
                cur[p].add(u)
                if len(cur[p]) >= 3:
                    cnt3.add(p)
                elif len(cur[p]) == 2 and len(G[p]) == 3:
                    cnt2.add(p)

    if len(ans) * 3 == N - 1:
        print('YES')
        for triple in ans:
            print(*triple)
    else:
        print('NO')