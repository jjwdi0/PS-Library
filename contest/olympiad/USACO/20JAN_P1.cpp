#include <bits/stdc++.h>
#define NUM(i,j) (((i)-1)*M+(j))
#define MOD 1000000007
using namespace std;
using ll = long long;
using pr = pair<int, int>;

char A[1005][1005];
int N, M, par[1005005], idx[1005][1005];
vector<int> v[1000005];
vector<pr> coor;
ll D[1000005];
bool chk[1000005], exist[1000005];

int f(int x) { return par[x] = (par[x] == x ? x : f(par[x])); }
void uni(int x, int y) { par[f(y)] = f(x); }

ll dp(int x) {
	ll res = 1LL;
	for(int it : v[x]) res = (res * dp(it)) % MOD;
	return (res + 1) % MOD;
}

int main() {
	scanf("%d %d", &N, &M);
	for(int i=1; i<=N; i++) scanf("%s", A[i] + 1);
	iota(par, par + N * M + 1, 0);
	int cnt = 0, pre = 0;
	for(int i=N-1; i>=2; i--) {
		for(int j=2; j<M; j++) if(A[i][j] == '.') idx[i][j] = ++cnt;
		for(int j=2; j<M; j++) if(A[i][j] == '.') {
			if(A[i][j-1] == A[i][j]) uni(NUM(i, j - 1), NUM(i, j));
			if(A[i+1][j] == A[i][j]) uni(NUM(i, j), NUM(i + 1, j));
		}
		for(int j=2; j<M; j++) if(A[i][j] == '.') {
			int c = f(NUM(i, j));
			idx[i][j] = idx[c/M+1][(c-1)%M+1];
			if(A[i+1][j] == '.') coor.emplace_back(idx[i][j], idx[i+1][j]);
		}
	}
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) exist[idx[i][j]] = 1;
	sort(coor.begin(), coor.end());
	coor.resize(unique(coor.begin(), coor.end()) - coor.begin());
	for(auto it : coor) v[it.first].push_back(it.second), chk[it.second] = 1;
	ll ans = 1LL;
	for(int i=1; i<=cnt; i++) if(!chk[i] && exist[i]) ans = (ans * dp(i)) % MOD;
	printf("%lld\n", ans);
}