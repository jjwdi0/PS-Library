#include <bits/stdc++.h>
using namespace std;

int N, M, A[2005][2005], B[2005][2005], mx, mn;

bool f(int x) {
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) {
        if(mx - x <= A[i][j] && mn + x >= A[i][j]) B[i][j] = 0;
        else if(mx - x > A[i][j] && mn + x < A[i][j]) return 0;
        else if(mx - x <= A[i][j]) B[i][j] = 1;
        else B[i][j] = -1;
    }
    int idx = M + 1;
    for(int i=1; i<=N; i++) {
        int l = 0, r = M + 1;
        for(int j=1; j<=M; j++) {
            if(B[i][j] == 1) l = j;
            if(B[i][j] == -1 && r == M + 1) r = j;
        }
        if(l > r) return 0;
        if(idx <= l) return 0;
        if(idx >= r) idx = r;
    }
    return 1;
}

int solve(int s, int e) {
    while(s <= e) {
        int mid = s + e >> 1;
        f(mid) ? e = mid - 1 : s = mid + 1;
    }
    return s;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> N >> M;
    mn = 1e9;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) cin >> A[i][j], mx = max(mx, A[i][j]), mn = min(mn, A[i][j]);
    int s = 0, e = mx - mn, ans = 1e9;
    for(int t=0; t<2; t++) {
        ans = min(ans, solve(s, e));
        for(int i=1; i<=N; i++) for(int j=1; j<M-j+1; j++) swap(A[i][j], A[i][M-j+1]);
        ans = min(ans, solve(s, e));
        for(int i=1; i<N-i+1; i++) for(int j=1; j<=M; j++) swap(A[i][j], A[N-i+1][j]);
    }
    cout << ans << '\n';
}