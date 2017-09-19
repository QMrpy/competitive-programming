
# Little Chef and Sums
# https://www.codechef.com/SEPT17/problems/CHEFSUM

for t in range(int(input())):
    n = input()
    a = list(map(int, input().split()))
    print(a.index(min(a))+1)