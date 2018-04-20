
# Infinite OR Game
# https://www.codechef.com/COOK86/problems/LIKECS03

for t in range(int(input())):
    N, K = map(int, input().split())
    A = list(map(int, input().split()))
    x = 0
    for i in range(K):
        if 1<<i not in A:
            x += 1
    print(x)