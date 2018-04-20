
# Periodic Palindrome Construction
# https://www.codechef.com/problems/PERPALIN

for t in range(int(input())):
    N, P = map(int, input().split())

    ans = 'impossible'
    if N % P == 0 and P >= 3:
        s = 'a' * ((P-1) // 2)
        s = s + 'b' + s if P % 2 == 1 else s + 'bb' + s
        ans = s * (N // P)
    print(ans)