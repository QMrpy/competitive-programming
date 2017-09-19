for t in range(int(input())):
    n, m = map(int, input().split())
    g = [[] for i in range(n+1)]
    for i in range(m):
        u, v = map(int, input().split())
        g[u].append(v)
    
    val = [None]*(n+1)
    nums = set()
    g[0].sort()
    for i in range(len(g[0])):
        val[g[0][i]] = i+1
        nums.add(i+1)
    
    invalid = False
    for u in range(1, n+1):
        if val[u] is None:
            invalid = True; break
        ss = set()
        nxt = None
        for v in g[u]:
            ss.add(val[v])
            if val[v] is None:
                nxt = v
        
        if len(g[u])!=len(ss) or (len(ss)!=len(nums) and len(ss)!=len(nums)-1):
            invalid = True; break
        if None in ss:
            ss.remove(None)
            ss.add(val[u])
            if ss!=nums:
                invalid = True; break
            val[nxt] = val[u]
        else:
            nums.remove(val[u])
            if ss!=nums:
                invalid = True; break
    
    if invalid:
        print(-1)
    else:
        print(*val[1:])
    
    