#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, M, X, Y, A[505][505], B[505];

bool possible(int x) {
    int cnt = 0, res = 0;
    for(int i=1; i<=M; i++) {
        res += B[i];
        if(res >= x) res = 0, cnt++;
    }
    return cnt >= Y;
}

bool f(int x) {
    int Q = X, cur = 1;
    while(Q--) {
        while(!possible(x) && cur <= N) {
            for(int i=1; i<=M; i++) B[i] += A[cur][i];
            cur++;
        }
        bool flag = possible(x);
        memset(B, 0, sizeof(B));
        if(cur > N && Q >= 0) return Q ? 0 : flag;
    }
    return 1;
}

int main() {
    scanf("%d %d %d %d", &N, &M, &X, &Y);
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) scanf("%d", &A[i][j]);
    int s = 1, e = 1e9;
    while(s <= e) {
        int mid = s + e >> 1;
        f(mid) ? s = mid + 1 : e = mid - 1;
    }
    printf("%d\n", e);
}
