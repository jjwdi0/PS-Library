#include <bits/stdc++.h>
#define MOD 1000000000
using namespace std;
using pr = pair<int, int>;

int N, M, K, chk[200005];
vector<pr> v[200005];

void dfs(int x) {
    for(auto it : v[x]) {
        if(chk[it.first]) {
            if(it.second == 1 && chk[it.first] != chk[x]) { puts("0"); exit(0); }
            else if(it.second == -1 && chk[it.first] == chk[x]) { puts("0"); exit(0); }
            else continue;
        }
        else {
            chk[it.first] = (it.second == 1 ? chk[x] : 3 - chk[x]);
            dfs(it.first);
        }
    }
}

int f(int x, int y) {
    if(x == 1) return y - 1;
    return M - 2 + x;
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for(int i=0, x, y, z; i<K; i++) {
        scanf("%d %d %d", &x, &y, &z);
        if(x > 1 && y > 1) {
            int p = M + x - 2, q = y - 1;
            if(x % 2 == 0 && y % 2 == 0) {
                v[p].push_back(pr(q, z ? 1 : -1));
                v[q].push_back(pr(p, z ? 1 : -1));
            }
            else {
                v[p].push_back(pr(q, z ? -1 : 1));
                v[q].push_back(pr(p, z ? -1 : 1));
            }
        }
        else chk[f(x, y)] = (1 << z);
	}
	if(chk[0] == 2) for(int i=1; i<=N+M-2; i++) for(auto &it : v[i]) it.second *= -1;
    int ans = 2 - !!chk[0];
    for(int i=1; i<=N+M-2; i++) if(chk[i]) dfs(i);
    for(int i=1; i<=N+M-2; i++) if(!chk[i]) { chk[i] = 1; ans = ans * 2 % MOD; dfs(i); }
    printf("%d\n", ans);
}
