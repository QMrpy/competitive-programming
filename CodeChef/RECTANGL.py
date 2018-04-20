
# Rectangle
# https://www.codechef.com/JAN18/problems/RECTANGL

for t in range(int(input())):
    a = list(map(int, input().split()))
    a.sort()
    print('YES' if a[0]==a[1] and a[2]==a[3] else 'NO')