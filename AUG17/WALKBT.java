import java.io.*;
import java.util.*;

// Editorial's approach
// https://discuss.codechef.com/questions/108219/walkbt-editorial

class WALKBT{
    static int N, Q;
    public static void main(String args[]) throws Exception {
        FastReader fr = new FastReader(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = fr.nextInt();
        while(t-->0){
            N = fr.nextInt();
            Q = fr.nextInt();

            boolean num[] = new boolean[N];
            SegTreeNode stNum = SegTreeNode.build(0, N-1);
            TreeSet<SegTreeNode> set = new TreeSet<>(SegTreeNode::comp);
            long ans = 1;

            while(Q-->0) {
                String type = fr.next();
                if(type.charAt(0)=='?')
                    pw.println(ans);
                else {
                    int C = fr.nextInt();
                    int qs, qe = N-1-C;
                    for(qs=qe; qs>=0; qs--) {
                        num[qs] ^= true;
                        if(num[qs])
                            break;
                    }
                    if(qs<0) qs = 0;

                    stNum = SegTreeNode.flip(stNum, qs, qe);
                    if(!set.contains(stNum)) {
                        SegTreeNode prev = set.lower(stNum);
                        SegTreeNode next = set.higher(stNum);
                        if(prev==null && next==null)
                            ans += N;
                        else if(prev==null) 
                            ans += N - SegTreeNode.getLCP(stNum, next);
                        else if(next==null)
                            ans += N - SegTreeNode.getLCP(stNum, prev);
                        else
                            ans +=   (N - SegTreeNode.getLCP(stNum, prev))
                                   + (N - SegTreeNode.getLCP(stNum, next))
                                   - (N - SegTreeNode.getLCP(prev, next));
                        set.add(stNum);
                    }

                }
            }
        }
        pw.close();
    }
}

class SegTreeNode {
    static int MAX_SIZE = (int)1e6;
    static int prime = (int)1e9 + 7;
    static int pow2[] = new int[MAX_SIZE];
    static {
        pow2[0] = 1;
        for(int i=1; i<MAX_SIZE; i++)
            pow2[i] = (pow2[i-1] + pow2[i-1]) % prime;
    }


    boolean bit;
    SegTreeNode lt, rt;
    int s, e;
    long hash0, hash1;

    SegTreeNode(int x) {
        s = e = x;
        hash0 = 1;
        hash1 = 0;
    }

    SegTreeNode(SegTreeNode l, SegTreeNode r) {
        s = l.s;
        e = r.e;
        lt = l; rt = r;
        hash0 = (lt.hash0 * pow2[rt.e-rt.s+1] + rt.hash0) % prime;
        hash1 = (lt.hash1 * pow2[rt.e-rt.s+1] + rt.hash1) % prime;
    }

    SegTreeNode(SegTreeNode node) {
        bit = node.bit;
        lt = node.lt; rt = node.rt;
        s = node.s; e = node.e;
        hash0 = node.hash0; hash1 = node.hash1;
    }

    void applyFlip() {
        bit ^= true;
        long tmp = hash0;
        hash0 = hash1;
        hash1 = tmp;
    }

    void propagate() {
        if(bit && lt!=null) { // && rt!=null
            bit = false;
            lt = new SegTreeNode(lt);
            lt.applyFlip();
            rt = new SegTreeNode(rt);
            rt.applyFlip();
        }
    }

    static SegTreeNode build(int s, int e) {
        if(s==e)
            return new SegTreeNode(s);
        int m = (s + e)>>1;
        return new SegTreeNode(build(s, m), build(m+1, e));
    }

    static SegTreeNode flip(SegTreeNode node, int qs, int qe) {
        if(qe < node.s || node.e < qs)
            return node;
        if(qs <= node.s && node.e <= qe) {
            SegTreeNode copy = new SegTreeNode(node);
            copy.applyFlip();
            return copy;
        }
        node.propagate();
        return new SegTreeNode(flip(node.lt, qs, qe), flip(node.rt, qs, qe));
    }

    static int comp(SegTreeNode root1, SegTreeNode root2) {
        SegTreeNode n1 = root1, n2 = root2;
        while(n1.lt!=null) {
            n1.propagate();
            n2.propagate();
            if(n1.lt.hash0==n2.lt.hash0 && n1.lt.hash1==n2.lt.hash1) {
                n1 = n1.rt; n2 = n2.rt;
            }
            else {
                n1 = n1.lt; n2 = n2.lt;
            }
        }
        return Boolean.compare(n1.bit, n2.bit);
    }

    static int getLCP(SegTreeNode root1, SegTreeNode root2) {
        SegTreeNode n1 = root1, n2 = root2;
        int lcp = 0;
        while(n1.lt!=null) {
            n1.propagate();
            n2.propagate();
            if(n1.lt.hash0==n2.lt.hash0 && n1.lt.hash1==n2.lt.hash1) {
                lcp += n1.lt.e - n1.lt.s + 1;
                n1 = n1.rt; n2 = n2.rt;
            }
            else {
                n1 = n1.lt; n2 = n2.lt;
            }
        }
        return lcp;
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