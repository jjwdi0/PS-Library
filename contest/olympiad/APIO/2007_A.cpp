#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, par[100003], count_mobile[100005], level[100005], log_n, ans;
vector<int> v[100005];
queue<pair<int, int>> q;
bool answer=true;

int log_2(int x) {
	int k = 1, cnt = 0;
	while(k <= x) k <<= 1, cnt++;
	return cnt - 1;
}

void f(int x) {
	int U1 = v[x][0], U2 = v[x][1];
	if(U1 < 0 && U2 < 0) return;
	if(U1 < 0 && U2 > 0) ans++, f(U2);
	if(U1 > 0 && U2 < 0) f(U1);
	if(U1 > 0 && U2 > 0) {
		if( ( count_mobile[U1] != (1 << (log_n - log_2(x))) && count_mobile[U2] != (1 << (log_n - log_2(x))) )
		 && ( count_mobile[U1] != (1 << (log_n - log_2(x) - 1)) && count_mobile[U2] != (1 << (log_n - log_2(x) - 1)) )) {
			answer = false;
			return;
		}
		else if(count_mobile[U1] < count_mobile[U2]) ans++;
		f(U1), f(U2);
	}
}

int main() {
	scanf("%d", &n);
	log_n = log_2(n);
	for(int i=1; i<=n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		v[i].push_back(x); v[i].push_back(y);
		if(~x) par[x] = i; else count_mobile[i]++;
		if(~y) par[y] = i; else count_mobile[i]++;
	}
	q.push({1, 0});
	while(!q.empty()) {
		pair<int, int> temp = q.front(); q.pop();
		level[temp.first] = temp.second;
		for(auto i : v[temp.first]) {
			if(i < 0)continue;
			q.push({i, temp.second + 1});
		}
	}
	for(int i=1; i<=n; i++) if(log_2(i) != level[i]) return puts("-1"), 0;
	for(int i=n; i>0; i--) count_mobile[par[i]] += count_mobile[i];
	f(1);
	if(!answer) return puts("-1"), 0;
	printf("%d", ans);
}