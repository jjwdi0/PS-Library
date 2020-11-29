#include <bits/stdc++.h>
using namespace std;

struct Z {
    int x, y, c, t;
};

int N, K, A[2002][2002], dir[4] = { 0,0,1,-1 }, par[100005];
queue<Z> q;

int f(int x) { return par[x] = (par[x] == x ? x : f(par[x])); }
void uni(int x, int y) { par[f(x)] = f(y); }

void check(int &cnt, int t) { if(++cnt == K - 1) printf("%d\n", t), exit(0); }
bool out(int x, int y) { return x < 1 || y < 1 || x > N || y > N; }

int main() {
    scanf("%d %d", &N, &K);
    if(K == 1) return puts("0"),0;
    for(int i=1, x, y; i<=K; i++) {
        scanf("%d %d", &x, &y);
        A[x][y] = i;
        par[i] = i;
        q.push({ x, y, i, 0 });
    }
    int cnt = 0;
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) if(A[i][j]) for(int k=0; k<4; k++) {
        int x = i + dir[k], y = j + dir[3-k];
        if(out(x, y) || !A[x][y] || f(A[x][y]) == f(A[i][j])) continue;
        uni(A[x][y], A[i][j]);
        check(cnt, 0);
    }
    while(!q.empty()) {
        auto I = q.front(); q.pop();
        int x = I.x, y = I.y, c = I.c, t = I.t;
        for(int i=0; i<4; i++) {
            int xx = x + dir[i], yy = y + dir[3-i];
            if(out(xx, yy) || A[xx][yy]) continue;
            q.push({ xx, yy, c, t + 1 });
            A[xx][yy] = c;
            for(int j=0; j<4; j++) {
                int xxx = xx + dir[j], yyy = yy + dir[3-j];
                if(out(xxx, yyy) || !A[xxx][yyy] || f(A[xxx][yyy]) == f(A[xx][yy])) continue;
                uni(A[xxx][yyy], A[xx][yy]);
                check(cnt, t + 1);
            }
        }
    }
}
