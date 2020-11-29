#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef pair<int, int> pr;

vector<pr> v1, v2;
int n, a[23];
bool chk[(1<<20)+3];

void f(int x, int y, int cnt) {
	if(x == n / 2) {
		v1.pb({cnt, y});
		return;
	}
	f(x + 1, y | 1 << x, cnt + a[x]);
	f(x + 1, y | 1 << x, cnt - a[x]);
	f(x + 1, y, cnt);
}

void g(int x, int y, int cnt) {
	if(x == n) {
		v2.pb({cnt, y});
		return;
	}
	g(x + 1, y | 1 << x, cnt + a[x]);
	g(x + 1, y | 1 << x, cnt - a[x]);
	g(x + 1, y, cnt);
}

int main() {
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", a + i);
	f(0, 0, 0); g(n / 2, 0, 0);
	sort(v1.begin(), v1.end()); sort(v2.begin(), v2.end());
	for(int i=0; i<v1.size(); i++) if(v1[i].first == 0) chk[v1[i].second] = true;
	for(int i=0; i<v2.size(); i++) if(v2[i].first == 0) chk[v2[i].second] = true;
	int i = 0, j = 0;
	while(i < v1.size() && j < v2.size()) {
		if(v1[i].first < v2[j].first) i++;
		else if(v1[i].first > v2[j].first) j++;
		else {
			int p = i, q = j;
			while(p < v1.size() && v1[p].first == v1[i].first) p++;
			while(q < v2.size() && v2[q].first == v2[j].first) q++;
			for(int ii=i; ii<p; ii++) {
				for(int jj=j; jj<q; jj++) {
					chk[v1[ii].second|v2[jj].second] = true;
				}
			}
			i = p, j = q;
		}
	}
	int ans = 0;
	for(int p=1; p<(1<<n); p++) ans += chk[p];
	printf("%d", ans);
}