import java.io.*;
import java.util.*;

class FLOWERPO{
    static long INF = (long)1e18;

    static int N, B, C, A[];
    static long dpf[][], dpb[][], dpc[][];

    public static void main(String args[]) throws Exception {
        FastReader fr = new FastReader(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = fr.nextInt();
        while(t-->0){
            N = fr.nextInt();
            B = fr.nextInt();
            C = fr.nextInt();
            A = new int[N+1];
            for(int i=1; i<=N; i++)
                A[i] = fr.nextInt();

            long ans = solve();
            pw.println(ans);
        }
        pw.close();
    }
    
    // neat approach by alexander86
    // https://discuss.codechef.com/questions/108287/approach-to-solve-flowerpo-august-long-challenge-17/108339
    static long solve() {
        
        dpf = new long[B+1][N+1];
        dpc = new long[B+1][N+1];
        dpb = new long[B+1][N+1];
        
        performDP(1, dpf);
        performDP(C, dpc);
        performDP(N, dpb);
        
        long ans = INF;
        for(int x=1; x<=N; x++) {
            for(int b=0; b<B; b++) {
                int x1=1, x2=N;
                do {
                    long cost = dpc[b][x] + sq(Math.max(A[x2]-A[x], A[x]-A[x1])) + dpf[B-b-1][x1] + dpb[B-b-1][x2];
                    ans = Math.min(ans, cost);
                    if(A[x2]-A[x]<A[x]-A[x1])
                        x1++;
                    else
                        x2--;
                } while(x1<x || x<x2);
            }
        }
        
        return ans;
    }
    
    static void performDP(int c, long dp[][]) {
        Arrays.fill(dp[0], INF);
        dp[0][c] = 0;
        for(int b=1; b<=B; b++) {
            for(int i=1; i<=N; i++) {
                dp[b][i] = INF;
                for(int j=1; j<=N; j++)
                    dp[b][i] = Math.min(dp[b][i], dp[b-1][j] + sq(A[i]-A[j]));
            }
        }
    }

    static long sq(long x) {
        return x * x;
    }
}

class FastReader{
    byte[] buf = new byte[2048];
    int index, total;
    InputStream in;

    FastReader(InputStream is){
        in = is;
    }

    int scan() throws IOException {
        if(index>=total){
            index = 0;
            total = in.read(buf);
            if(total<=0)
                return -1;
        }
        return buf[index++];
    }

    int nextInt() throws IOException {
        int c, val = 0;
        for(c=scan(); c<=32; c=scan());
        boolean neg = c=='-';
        if(c=='-' || c=='+')
            c = scan();
        for(; c>='0' && c<='9'; c=scan())
            val = (val<<3) + (val<<1) + (c&15);
        return neg?-val:val;
    }
}