#include <bits/stdc++.h>
using namespace std;

int N, M, cnt[100005], D[100005], indeg[100005];
vector<int> v1[100005], v2[100005];
queue<int> q;

int main() {
    scanf("%d %d", &N, &M);
    for(int i=0, x, y; i<M; i++) {
        scanf("%d %d", &x, &y), x++, y++;
        v1[x].push_back(y);
        v1[y].push_back(x);
        cnt[x]++, cnt[y]++;
    }
    for(int i=1; i<=N; i++) {
        for(int it : v1[i]) {
            if(cnt[i] < cnt[it]) v2[i].push_back(it), indeg[it]++;
        }
    }
    for(int i=1; i<=N; i++) if(!indeg[i]) q.push(i), D[i] = 1;
    int ans = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int it : v2[u]) {
            D[it] = max(D[it], D[u] + 1);
            indeg[it]--;
            if(!indeg[it]) q.push(it);
        }
        ans = max(ans, D[u]);
    }
    printf("%d\n", ans);
}
