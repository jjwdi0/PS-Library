#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Z {
    int x, y, c;
    bool operator < (const Z &A) const { return x < A.x; }
} A[100005];

int N, M, cur_y1, cur_y2, pre_x, pre_y1, pre_y2;
ll ans;
int cnt;
bool f, g;

int main() {
    scanf("%d %d", &N, &M);
    for(int i=0, x; i<2*N+1; i++) {
        scanf("%d", &x);
        if(i == 0) pre_y1 = cur_y1 = x;
        if(i & 1) A[i / 2].x = x;
        if(i > 0 && i % 2 == 0) A[i / 2 - 1].y = x;
        A[i / 2].c = 1;
    }
    for(int i=0, x; i<2*M+1; i++) {
        scanf("%d", &x);
        if(i == 0) pre_y2 = cur_y2 = x;
        if(i & 1) A[N + i / 2].x = x;
        if(i > 0 && i % 2 == 0) A[N + i / 2 - 1].y = x;
        A[N + i / 2].c = 2;
    }
    sort(A, A+N+M);
    ll res = 0;
    for(int i=0; i<N+M; i++) {
        if(cur_y1 < cur_y2 && !g) {
            if(A[i].c == 1) pre_y1 = cur_y1 = A[i].y;
            else pre_y2 = cur_y2 = A[i].y;
            pre_x = A[i].x;
            continue;
        }
        g = 1;
        if(A[i].c == 1) cur_y1 = A[i].y;
        else cur_y2 = A[i].y;

        if(f) {
            res += 1LL * (A[i].x - pre_x) * (pre_y2 - pre_y1);
        }

        if(cur_y2 > cur_y1) {
            if(!f) cnt++;
            f = 1;
        }
        else f = 0;

        if(!f) ans += res, res = 0LL;

        pre_y1 = cur_y1, pre_y2 = cur_y2, pre_x = A[i].x;
    }
    if(f) cnt--;
    printf("%d %lld\n", cnt, ans);
}
