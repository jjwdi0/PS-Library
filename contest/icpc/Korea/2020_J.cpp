#include <bits/stdc++.h>
using namespace std;

int N, A[505][505], B[505][505];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N;
	for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) cin >> A[i][j];
	for(int i=1; i<=N; i++) B[i][i] = 1;
	for(int i=1; i<=N; i++) {
		for(int j=i; j<=N; j++) if(A[j][i] == 1) {
			for(int k=1; k<=N; k++) {
				swap(A[i][k], A[j][k]);
				swap(B[i][k], B[j][k]);
			}
		}
		if(A[i][i] == 0) return cout << "-1\n", 0;
		for(int j=1; j<=N; j++) if(i != j && A[j][i] == 1) {
			for(int k=1; k<=N; k++) A[j][k] ^= A[i][k];
			for(int k=1; k<=N; k++) B[j][k] ^= B[i][k];
		}
	}
	for(int i=1; i<=N; i++) {
		vector<int> v;
		for(int j=1; j<=N; j++) if(B[i][j]) v.push_back(j);
		for(int it : v) cout << it << " \n"[it==v.back()];
	}
}