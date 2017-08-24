for t in range(int(input())):
    N, D = map(int, input().split())
    A = list(map(int, input().split()))
    s = sum(A)
    if s%N==0:
        x = s//N
        moves = 0
        for i in range(N-D):
            moves += abs(x - A[i])
            A[i+D] -= x - A[i]
        for i in range(N-D, N):
            if A[i]!=x:
                moves = -1
                break
    else:
        moves = -1
    print(moves)
