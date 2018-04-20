
# A Balanced Contest
# https://www.codechef.com/OCT17/problems/PERFCONT

for t in range(int(input())):
    N, P = map(int, input().split())
    solved = list(map(int, input().split()))
    cakewalk = sum(x >= P//2 for x in solved)
    hard = sum(x <= P//10 for x in solved)
    print('yes' if cakewalk==1 and hard==2 else 'no')
