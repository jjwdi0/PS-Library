#include <bits/stdc++.h>
using namespace std;

char A[1000005], B[100005];
int N, M, idx[100005][29];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> (A + 1) >> (B + 1);
	N = strlen(A + 1), M = strlen(B + 1);
	for(int i=0; i<=M+1; i++) for(int j=0; j<26; j++) idx[i][j] = -1;
	for(int i=M; i; i--) {
		for(int j=0; j<26; j++) idx[i][j] = idx[i+1][j];
		idx[i][B[i]-'a'] = i;
	}
	int ans = 1, cur = 1;
	for(int i=1; i<=N; i++) {
		int cidx = idx[cur][A[i]-'a'];
		if(cidx < 1) {
			ans++;
			cur = 1;
			cidx = idx[cur][A[i]-'a'];
			if(cidx < 1) {
				cout << "-1\n";
				return 0;
			}
			cur = cidx + 1;
		} else {
			cur = cidx + 1;
		}
	}
	cout << ans << "\n";
}