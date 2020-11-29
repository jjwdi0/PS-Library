#include <bits/stdc++.h>
#define SQRT 333
#define all(x) (x).begin(),(x).end()
using namespace std;

int N, A[100005];
vector<int> v[100005];
int dfn[100005], sz[100005], cnt;
int idx[100005];
vector<int> B[SQRT];

void dfs(int x) {
    dfn[++cnt] = x;
    for(int i : v[x]) dfs(i), sz[x] += sz[i];
    sz[x]++;
}

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", A+i);
    for(int i=2, x; i<=N; i++) {
        scanf("%d", &x);
        v[x].push_back(i);
    }
    dfs(1);
    for(int i=1; i<=N; i++) idx[dfn[i]] = i;
    for(int i=1; i<=N; i++) B[i / SQRT].push_back(A[dfn[i]]);
    for(int i=0; i<SQRT; i++) sort(all(B[i]));
    for(int i=1; i<=N; i++) {
        int ans = 0;
        int s = idx[i], e = idx[i] + sz[i] - 1;
        if(s / SQRT + 1 >= e / SQRT) {
            for(int j=s; j<=e; j++) ans += (A[i] < A[dfn[j]]);
        }
        else {
            int l = s, r = e;
            while(l / SQRT == s / SQRT) ans += (A[i] < A[dfn[l++]]);
            while(r / SQRT == e / SQRT) ans += (A[i] < A[dfn[r--]]);
            for(int j=l/SQRT; j<=r/SQRT; j++) ans += (int)(upper_bound(all(B[j]), 2e9) - upper_bound(all(B[j]), A[i]));
        }
        printf("%d\n", ans);
    }
}
