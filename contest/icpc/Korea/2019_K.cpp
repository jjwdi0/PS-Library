#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, K, R[105], G[105], B[105];
int rr, gg, bb, r, g, b;

ll f(ll x) { return x * x; }

int main() {
    scanf("%d %d", &N, &K);
    if(N <= K) return puts("0.000000"),0;
    for(int i=1; i<=N; i++) scanf("%d %d %d", R+i, G+i, B+i);
    for(int i=1; i<=N; i++) {
        rr += f(R[i]), r += R[i];
        gg += f(G[i]), g += G[i];
        bb += f(B[i]), b += B[i];
    }
    double ans1 = 0, ans2 = 1e18;
    ans1 = -(double)(f(r) + f(g) + f(b)) / N + rr + gg + bb;
    if(K == 1) return !printf("%.6f\n", ans1);
    for(int i=1; i<=N; i++) for(int j=i+1; j<=N; j++) for(int k=j+1; k<=N; k++) {
        ll dx1 = R[i] - R[j], dy1 = G[i] - G[j], dz1 = B[i] - B[j];
        ll dx2 = R[i] - R[k], dy2 = G[i] - G[k], dz2 = B[i] - B[k];
        ll z = dx1 * dy2 - dx2 * dy1;
        ll x = dy1 * dz2 - dy2 * dz1;
        ll y = dz1 * dx2 - dz2 * dx1;
        ll cmp = x * R[i] + y * G[i] + z * B[i];
        int cnt1 = 0, cnt2 = 0;
        int x1 = 0, y1 = 0, z1 = 0;
        int x2 = 0, y2 = 0, z2 = 0;
        for(int p=1; p<=N; p++) {
            ll res = x * R[p] + y * G[p] + z * B[p];
            if(res < cmp) cnt1++, x1 += R[p], y1 += G[p], z1 += B[p];
            else if(res > cmp) cnt2++, x2 += R[p], y2 += G[p], z2 += B[p];
        }
        for(int p=0; p<8; p++) {
            if(p & 1) cnt1++, x1 += R[i], y1 += G[i], z1 += B[i];
            else cnt2++, x2 += R[i], y2 += G[i], z2 += B[i];

            if(p & 2) cnt1++, x1 += R[j], y1 += G[j], z1 += B[j];
            else cnt2++, x2 += R[j], y2 += G[j], z2 += B[j];

            if(p & 4) cnt1++, x1 += R[k], y1 += G[k], z1 += B[k];
            else cnt2++, x2 += R[k], y2 += G[k], z2 += B[k];

            if(cnt1 && cnt2) ans2 = min(ans2, -(double)(f(x1) + f(y1) + f(z1)) / cnt1 - (double)(f(x2) + f(y2) + f(z2)) / cnt2 + rr + gg + bb);

            if(p & 1) cnt1--, x1 -= R[i], y1 -= G[i], z1 -= B[i];
            else cnt2--, x2 -= R[i], y2 -= G[i], z2 -= B[i];

            if(p & 2) cnt1--, x1 -= R[j], y1 -= G[j], z1 -= B[j];
            else cnt2--, x2 -= R[j], y2 -= G[j], z2 -= B[j];

            if(p & 4) cnt1--, x1 -= R[k], y1 -= G[k], z1 -= B[k];
            else cnt2--, x2 -= R[k], y2 -= G[k], z2 -= B[k];
        }
    }
    printf("%.6f\n", min(ans1, ans2));
}
