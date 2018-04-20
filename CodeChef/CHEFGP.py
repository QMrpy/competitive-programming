
# Chef and a great voluntary Program
# https://www.codechef.com/OCT17/problems/CHEFGP

def solve(a, b, x, y, c1, c2, c3):
    breaks = a//x - (a%x==0)
    if b > breaks*y + y:
        return -1
    if b < breaks:
        s1 = (c1*x + c2)*b
        a -= x*b
        breaks = a//x - (a%x==0)
        s2 = (c1*x + c3)*breaks
        a -= x*breaks
        s3 = c1*a if a>0 else ''
        return s1 + s2 + s3
    else:
        s1 = s2 = s3 = s4 = ''
        if b >= y*breaks:
            dif = b - y*breaks
            s4 = c2*dif
            b -= dif
        if breaks > 0:
            bcnt = b//breaks
            brem = b%breaks
            s1 = (c1*x + c2*(bcnt+1))*brem
            s2 = (c1*x + c2*bcnt)*(breaks - brem)
            a -= x*breaks
        s3 = c1*a if a>0 else ''
        return s1 + s2 + s3 + s4

for t in range(int(input())):
    s = input().strip()
    x, y = map(int, input().split())
    a, b = s.count('a'), s.count('b')

    s = solve(a, b, x, y, 'a', 'b', '*')
    if s==-1: s = solve(b, a, y, x, 'b', 'a', '*')
    print(s)
