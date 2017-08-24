for t in range(int(input())):
    N, M = map(int, input().split())
    min_sal = list(map(int, input().split()))
    off_sal, max_job = [None]*M, [None]*M
    for i in range(M):
        off_sal[i], max_job[i] = map(int, input().split())
    max_job_copy = max_job[:]
    qual = [input().strip() for i in range(N)]
    
    happy = total = 0
    for i in range(N):
        choices = [(off_sal[j], j) for j in range(M) if qual[i][j]=='1' and off_sal[j]>=min_sal[i] and max_job[j]>0]
        if choices:
            max_sal, comp = max(choices)
            happy += 1
            total += max_sal
            max_job[comp] -= 1
    sad = sum(m1==m2 for m1, m2 in zip(max_job, max_job_copy))
    
    print(happy, total, sad)