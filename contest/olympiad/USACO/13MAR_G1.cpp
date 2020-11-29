#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
using namespace std;
using ll = long long;

int N, M;
vector<int> ne, po;
ll D[1005][1005][2];

ll f(int x, int y, int c) { return 1LL * ((N - x) + (M - y) + 1) * c; }

int main() {
    scanf("%d", &N);
    for(int i=0, x; i<N; i++) {
        scanf("%d", &x);
        if(x < 0) ne.pb(x);
        else po.pb(x);
    }
    ne.pb(0);
    po.pb(0);
    for(auto &it : ne) it *= -1;
    sort(all(ne)), sort(all(po));
    N = sz(ne) - 1, M = sz(po) - 1;
    for(int i=1; i<=N; i++) D[i][0][0] = D[i-1][0][0] + 1LL * (ne[i] - ne[i-1]) * (N + M - i + 1), D[i][0][1] = 1e18;
    for(int i=1; i<=M; i++) D[0][i][1] = D[0][i-1][1] + 1LL * (po[i] - po[i-1]) * (N + M - i + 1), D[0][i][0] = 1e18;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) {
        D[i][j][0] = min(D[i-1][j][0] + f(i, j, ne[i] - ne[i-1]), D[i-1][j][1] + f(i, j, po[j] + ne[i]));
        D[i][j][1] = min(D[i][j-1][0] + f(i, j, ne[i] + po[j]), D[i][j-1][1] + f(i, j, po[j] - po[j-1]));
    }
    printf("%lld\n", min(D[N][M][0], D[N][M][1]));
}
