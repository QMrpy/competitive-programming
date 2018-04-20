
# Chef and Pick Digit
# https://www.codechef.com/SEPT17/problems/CHEFPDIG

from collections import Counter
d = [(i%10, i//10, i) for i in range(65, 65+26)]
for t in range(int(input())):
    c = Counter(map(int, list(input().strip())))
    print(''.join(chr(i) for d0, d1, i in d if d0==d1 and c[d0]>1 or d0!=d1 and c[d0]>0 and c[d1]>0)) 