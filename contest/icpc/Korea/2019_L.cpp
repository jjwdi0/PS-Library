#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;
using tr = pair<pr, int>;

int M, N, B[105],  D[10005];
tr A[10005];

int main() {
    scanf("%d %d", &M, &N);
    for(int i=1; i<=M; i++) scanf("%d", B+i);
    for(int i=1, x, y, z; i<=N; i++) {
        scanf("%d %d %d", &x, &y, &z);
        A[i] = tr(pr(y, x), (y - x) * B[z]);
    }
    sort(A + 1, A + N + 1);
    int ans = 0;
    for(int i=1; i<=N; i++) {
        D[i] = A[i].second;
        for(int j=1; j<i; j++) if(A[i].first.second >= A[j].first.first) D[i] = max(D[i], D[j] + A[i].second);
        ans = max(ans, D[i]);
    }
    printf("%d\n", ans);
}
