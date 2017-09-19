
// Police Operation
// https://www.hackerrank.com/challenges/police-operation

import java.io.*;
import java.util.*;

class PoliceOperation{
    static int N, H;
    static long A[];
    
    public static void main(String args[]) throws Exception {
        FastReader fr = new FastReader(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        N = fr.nextInt();
        H = fr.nextInt();
        A = new long[N+1];
        for(int i=1; i<=N; i++)
            A[i] = fr.nextInt();
            
        long ans = solve();
        pw.println(ans);
        pw.close();
    }
    
    static long solve() {
        long dp[] = new long[N+1];
        
        ArrayDeque<Line> dq = new ArrayDeque<>();
        dq.addLast(new Line(0, (long)1e15));
        
        for(int i=1; i<=N; i++) {
            
            Line cur = new Line(-2*A[i], dp[i-1] + A[i]*A[i]);
            Line bot = dq.pollLast();
            while(!dq.isEmpty()) {
                if(bot.intersectX(cur) > dq.peekLast().intersectX(cur))
                    break;
                bot = dq.pollLast();
            }
            dq.addLast(bot);
            dq.addLast(cur);
            
            Line top = dq.pollFirst();
            while(!dq.isEmpty()) {
                if(top.eval(A[i]) < dq.peekFirst().eval(A[i]))
                    break;
                top = dq.pollFirst();
            }
            dq.addFirst(top);
            
            dp[i] = top.eval(A[i]) + H + A[i]*A[i];
        }
        
        return dp[N];
    }
}

class Line {
    long m, c;
    Line(long mm, long cc) {
        m = mm;
        c = cc;
    }
    
    long eval(long x) {
        return m*x + c;
    }
    
    double intersectX(Line l) {
        return (c - l.c) * 1.0 / (l.m - m);
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
        return neg?-val:val;
    }
}