#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;

int N, L;
pr A[100005];
ll D[100005][2], ans;
int X[100005], Y[100005];

ll dist(int x) { return abs(A[x].first - A[x].second) + L; }

int main() {
    scanf("%d %d", &N, &L);
    for(int i=1; i<=N; i++) {
        scanf("%d %d", &A[i].first, &A[i].second);
        X[i] = A[i].first, Y[i] = A[i].second;
    }
    sort(A+1, A+N+1);
    sort(X+1, X+N+1), sort(Y+1, Y+N+1);
    for(int i=1; i<=N; i++) {
        int idx1 = (int)(lower_bound(X+1, X+N+1, A[i].first) - X)
          , idx2 = (int)(lower_bound(Y+1, Y+N+1, A[i].second) - Y);
        ll d1 = D[idx1][0], d2 = D[idx2][1];
        D[idx2][1] = max(d2, d1 + dist(i));
        D[idx1][0] = max(d1, d2 + dist(i));
        ans = max(ans, max(D[idx1][0], D[idx2][1]));
    }
    printf("%lld\n", ans);
}
