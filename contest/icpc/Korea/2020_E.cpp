#include <bits/stdc++.h>
using namespace std;

int N, A[1000005];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N;
	for(int i=1; i<=N; i++) cin >> A[i];
	for(int i=1; i<N; i++) {
		if(A[i] >= 2) return cout << "NO\n",0;
		if(A[i] == 1) {
			A[i]--;
			if(A[i+1] == 0) A[i+1] = 1;
			else A[i+1]--;
		}
	}
	cout << (A[N] ? "NO\n" : "YES\n");
}