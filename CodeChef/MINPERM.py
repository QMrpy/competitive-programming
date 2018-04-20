
# Minimum Good Permutation
# https://www.codechef.com/SEPT17/problems/MINPERM

for t in range(int(input())):
    n = int(input())
    p = [i+1 if i%2 else i-1 for i in range(1, n+1)]
    if n%2:
        p[-2], p[-1] = n, n-2
    print(*p) 