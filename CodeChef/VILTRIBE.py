
# Villages and Tribes
# https://www.codechef.com/NOV17/problems/VILTRIBE

for t in range(int(input())):
    S = '!' + input().strip() + '@'
    i = 1
    c = {'A' : 0, 'B' : 0}
    while i < len(S)-1:
        if S[i] == '.':
            j = i + 1
            while j < len(S) and S[i] == S[j]:
                j += 1
            if S[i-1] == S[j]:
                c[S[j]] += j - i
            i = j
        else:
            c[S[i]] += 1
            i += 1
    print(c['A'], c['B'])

