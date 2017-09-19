
# Statistics Construction
# https://www.codechef.com/COOK86/problems/LIKECS02

for t in range(int(input())):
    N = int(input())
    s = N - N//2
    a = [s+i for i in range(N)]
    print(*a)