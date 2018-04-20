
// Mathison and the teleportation game
// https://www.codechef.com/problems/MATTEG
// Dynamic programming
// O(N * 5^N)

import java.io.*;
import java.util.*;

class MATTEG{
    static int NINF = -(int)1e9;
    static int p5[] = {1, 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125};
    static int dir[][] = {{0, -1, -1, 1, 1}, {0, -1, 1, -1, 1}};

    static int R, C, N;
    static int Sx, Sy, tel[][];
    static int board[][];

    public static void main(String args[]) throws Exception {
        FastReader fr = new FastReader(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int T = fr.nextInt();
        while(T-- > 0){
            R = fr.nextInt();
            C = fr.nextInt();
            N = fr.nextInt();
            Sx = fr.nextInt();
            Sy = fr.nextInt();
            tel = new int[2][N];
            for(int i=0; i<N; i++)
                tel[0][i] = fr.nextInt();
            for(int i=0; i<N; i++)
                tel[1][i] = fr.nextInt();
            board = new int[R][C];
            for(int i=0; i<R; i++) for(int j=0; j<C; j++)
                board[i][j] = fr.nextInt();

            pw.println(solve());
        }
        pw.close();
    }

    static long solve() {
        long dp[] = new long[p5[N]];
        long ans = dp[0] = board[Sx][Sy];
        for(int i=1; i<p5[N]; i++) {
            int x = Sx, y = Sy;
            dp[i] = NINF;
            for(int j=0; j<N; j++) {
                int dig = i / p5[j] % 5;
                if(dig > 0) {
                    dp[i] = Math.max(dp[i], dp[i - dig * p5[j]]);
                    x += tel[0][j] * dir[0][dig];
                    y += tel[1][j] * dir[1][dig];
                }
            }
            if(x<0 || x>=R || y<0 || y>=C) dp[i] = NINF;
            else ans = Math.max(ans, dp[i] += board[x][y]);
        }

        return ans;
    }
}

class FastReader{
    byte[] buf = new byte[2048];
    int index, total;
    InputStream in;

    FastReader(InputStream is) {
        in = is;
    }

    int scan() throws IOException {
        if(index >= total){
            index = 0;
            total = in.read(buf);
            if(total <= 0)
                return -1;
        }
        return buf[index++];
    }
    
    String next() throws IOException {
        int c;
        for(c=scan(); c<=32; c=scan());
        StringBuilder sb = new StringBuilder();
        for(; c>32; c=scan())
            sb.append((char)c);
        return sb.toString();
    }

    int nextInt() throws IOException {
        int c, val = 0;
        for(c=scan(); c<=32; c=scan());
        boolean neg = c=='-';
        if(c=='-' || c=='+')
            c = scan();
        for(; c>='0' && c<='9'; c=scan())
            val = (val<<3) + (val<<1) + (c&15);
        return neg ? -val : val;
    }
}