from collections import Counter
for t in range(int(input())):
    A, B = input().strip(), input().strip()
    
    sa, sb = set(A), set(B)
    ca, cb = Counter(A), Counter(B)
    if sa<=sb:
        winner = 'B'
    elif sa>sb:
        winner = 'A'
    else:
        winner = 'B'
        sda = sa - sb
        for c in sda:
            if ca[c]>1:
                winner = 'A'
                break
        
    print(winner)