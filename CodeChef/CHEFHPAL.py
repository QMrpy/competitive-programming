
# Chef Hates Palindromes
# https://www.codechef.com/NOV17/problems/CHEFHPAL

special = [None, '1 a', '1 ab', '2 aab', '2 aabb', '3 aaaba', '3 aaabab', '3 aaababb', '3 aaababbb']
for t in range(int(input())):
    N, A = map(int, input().split())

    if A == 1:
        ans = str(N) + ' ' + 'a' * N
    elif A > 2:
        ans = '1 ' + ('abc' * (N // 3 + 1))[:N]
    elif N <= 8:
        ans = special[N]
    else:
        ans = '4 ' + ('aabbab' * (N // 6 + 1))[:N]
    print(ans)