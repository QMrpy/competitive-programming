
// Chef and Subarray Queries
// https://www.codechef.com/NOV17/problems/CSUBQ

// Solution using segment tree
// O(log N) per update / query
// Overall O(N + Q log N)

import java.io.*;
import java.util.*;

class CSUBQ{
    public static void main(String args[]) throws Exception {
        FastReader fr = new FastReader(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int N = fr.nextInt();
        int Q = fr.nextInt();
        int L = fr.nextInt();
        int R = fr.nextInt();

        SegmentTree Ltree = new SegmentTree(N);
        SegmentTree Rtree = new SegmentTree(N);

        while(Q-- > 0) {
            int type = fr.nextInt();
            if(type == 1) {
                int x = fr.nextInt();
                int y = fr.nextInt();
                Ltree.update(x, y < L ? 1 : 0);
                Rtree.update(x, y <= R ? 1 : 0);
            }
            else {
                int l = fr.nextInt();
                int r = fr.nextInt();
                pw.println(Rtree.query(l, r) - Ltree.query(l, r));
            }
        }

        pw.close();
    }
}

class SegmentTree {
    static class SegmentTreeNode {
        int len, pre, suf;
        long count;

        SegmentTreeNode(int v, int l) {
            count = pre = suf = v;
            len = l;
        }

        SegmentTreeNode(SegmentTreeNode lt, SegmentTreeNode rt) {
            update(lt, rt);
        }

        void update(SegmentTreeNode lt, SegmentTreeNode rt) {
            count = lt.count + rt.count + 1L * lt.suf * rt.pre;
            pre = lt.pre + (lt.pre == lt.len ? rt.pre : 0);
            suf = rt.suf + (rt.suf == rt.len ? lt.suf : 0);
            len = lt.len + rt.len;
        }
    }

    int N;
    SegmentTreeNode tree[];

    SegmentTree(int n) {
        N = Integer.highestOneBit(n) << 1;
        tree = new SegmentTreeNode[N << 1];
        for(int i=0; i<N; i++) tree[i+N] = new SegmentTreeNode(1, 1);
        for(int i=N-1; i>0; i--) tree[i] = new SegmentTreeNode(tree[i<<1], tree[i<<1|1]);
    }

    long query(int i, int j){
        SegmentTreeNode lt = new SegmentTreeNode(0, 0),
                        rt = new SegmentTreeNode(0, 0);
        for(i+=N, j+=N; i<=j; i=(i+1)>>1, j=(j-1)>>1){
            if((i&1)==1) lt.update(lt, tree[i]);
            if((j&1)==0) rt.update(tree[j], rt);
        }
        lt.update(lt, rt);
        return lt.count;
    }

    void update(int i, int v){
        tree[i+N] = new SegmentTreeNode(v, 1);
        for(i=(i+N)>>1; i>0; i>>=1)
            tree[i].update(tree[i<<1], tree[i<<1|1]);
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