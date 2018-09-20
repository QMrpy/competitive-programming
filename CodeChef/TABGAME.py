
# Table Game
# https://www.codechef.com/SEPT18A/problems/TABGAME

# O(N + M + Q)

for t in range(int(input())):
    top = list(map(int, list(input().strip())))
    left = list(map(int, list(input().strip())))
    row0 = [not top[0] or not left[0]]
    for i in range(1, len(top)):
        row0.append(not top[i] or not row0[-1])
    if len(left) > 1:
        row1 = [not row0[0] or not left[1]]
        for i in range(1, len(top)):
            row1.append(not row0[i] or not row1[-1])
    col0 = [not left[0] or not top[0]]
    for i in range(1, len(left)):
        col0.append(not left[i] or not col0[-1])
    if len(top) > 1:
        col1 = [not col0[0] or not top[1]]
        for i in range(1, len(left)):
            col1.append(not col0[i] or not col1[-1])
    ans = []
    for q in range(int(input())):
        x, y = map(int, input().split())
        x, y = x - 1, y - 1
        if x == 0:
            res = row0[y]
        elif y == 0:
            res = col0[x]
        elif x <= y:
            res = row1[y - (x - 1)]
        else:
            res = col1[x - (y - 1)]
        ans.append(int(res))
    print(*ans, sep='')