#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Z {
    int x, y;
    ll c;
    Z() {x = y = c = 0;}
    Z(int _x, int _y, ll _c) {x = _x, y = _y, c = _c;}
    bool operator < (const Z &A) const {
        return c < A.c;
    }
    bool operator > (const Z &A) const {
        return c > A.c;
    }
};

int N;
ll T, A[103][103];
ll D[103][103];
int dx[16][2] = {
    1, 0,
    -1, 0,
    0, 1,
    0, -1,
    -3, 0,
    3, 0,
    0, 3,
    0, -3,
    2, 1,
    2, -1,
    1, -2,
    1, 2,
    -1, 2,
    -1, -2,
    -2, 1,
    -2, -1
};
priority_queue<Z, vector<Z>, greater<Z>> q;

bool get(int x, int y) {return x > 0 && y > 0 && x <= N && y <= N;}

int main() {
    scanf("%d %lld", &N, &T);
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) scanf("%lld", &A[i][j]), D[i][j] = 1e18;
    q.push(Z(1, 1, 0LL));
    while(!q.empty()) {
        Z P = q.top(); q.pop();
        int x = P.x, y = P.y; ll c = P.c;
        if(D[x][y] < c) continue;
        D[x][y] = c;
        if(x == N && y == N) return !printf("%lld\n", D[N][N]);
        if(N * 2 - x - y <= 2 && D[N][N] > c + (ll)(N * 2 - x - y) * T) D[N][N] = c + (ll)(N * 2 - x - y) * T, q.push(Z(N, N, D[N][N]));
        for(int i=0; i<16; i++) {
            int xx = x + dx[i][0], yy = y + dx[i][1];
            if(!get(xx, yy)) continue;
            if(D[xx][yy] <= c + 3LL * T + A[xx][yy]) continue;
            D[xx][yy] = c + 3LL * T + A[xx][yy];
            q.push(Z(xx, yy, D[xx][yy]));
        }
    }
}