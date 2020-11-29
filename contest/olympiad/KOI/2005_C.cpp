#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
using namespace std;
using pr = pair<int, int>;

int N, M, dep = 200000, ans;
pr A[200005];
vector<int> v[400005];

int main() {
    scanf("%d %d", &N, &M);
    for(int i=0; i<N+M; i++) {
        scanf("%d", &A[i].first);
        A[i].second = (i < N ? 1 : 2);
    }
    sort(A, A+N+M);
    for(int i=0; i<N+M; i++) {
        if(A[i].second == 1) v[++dep].push_back(A[i].first);
        else v[dep--].push_back(A[i].first);
    }
    for(int i=0; i<=400000; i++) {
        if(sz(v[i]) <= 1) continue;
        int cnt = 0, mn;
        if(sz(v[i]) & 1) {
            for(int j=0; j+1<sz(v[i]); j+=2) cnt += v[i][j+1] - v[i][j];
            mn = cnt;
            for(int j=sz(v[i])-1; j>1; j-=2) {
                cnt -= v[i][j-1] - v[i][j-2];
                cnt += v[i][j] - v[i][j-1];
                mn = min(mn, cnt);
            }
            ans += mn;
        }
        else for(int j=0; j<sz(v[i]); j+=2) ans += v[i][j+1] - v[i][j];
    }
    printf("%d\n", ans);
}
