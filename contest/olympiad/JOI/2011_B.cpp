#include <bits/stdc++.h>
using namespace std;

vector<int> v[13];
int dp[12][2003], n, m;

void s(int &x){int t;scanf("%d", &t);x=t;}
bool cmp(const int &x, const int &y) { return x > y; }

int main() {
	s(n); s(m);
	for(int i=0; i<n; i++) {
		int x, y;
		s(x); s(y);
		v[y].push_back(x);
	}
	for(int i=1; i<=10; i++) {
		sort(v[i].begin(), v[i].end(), cmp);
		for(int j=1; j<v[i].size(); j++) {
			v[i][j] += v[i][j-1];
		}
	}
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	for(int i=0; i<10; i++) {
		for(int j=0; j<n; j++) {
			if(~dp[i][j]) {
				for(int k=0; k<=min((int)v[i+1].size(), m-j); k++) {
					if(k == 0) dp[i+1][j] = max(dp[i][j], dp[i+1][j]);
					else dp[i+1][j+k] = max(dp[i+1][j+k], dp[i][j] + v[i+1][k-1] + k * (k - 1));
				}
			}
		}
	}
	printf("%d", dp[10][m]);
}