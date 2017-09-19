def check(i, x):
    j = i
    while j<N and A[j]==x:
        j += 1
    c1 = j - i
    if c1==0: return None
        
    if x==7:
        return j
        
    i = check(j, x+1)
    if i is None: return None
    j = i
    while j<N and A[j]==x:
        j += 1
    c2 = j - i
    return None if c2!=c1 else j

for t in range(int(input())):
    N = int(input())
    A = list(map(int, input().split()))
    x = check(0, 1)
    if x is None or x!=N:
        print('no')
    else:
        print('yes')
