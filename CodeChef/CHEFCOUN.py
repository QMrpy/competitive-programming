
# Counter Test For CHEFSUM
# https://www.codechef.com/OCT17/problems/CHEFCOUN

for t in range(int(input())):
    n = int(input())
    x = 2**32 // (n + 1)
    y = 2**32 - x * (n + 1)
    a = [x] * n
    a[1] += y//2 + 5
    print(*a)
