#include <bits/stdc++.h>
using namespace std;

int T, N;
string A[103];

bool is_palindrome(string t) {
	for(int i=0; i<t.length(); i++) if(t[i] != t[t.length() - 1 - i]) return false;
	return true;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> T;
	while(T--) {
		cin >> N;
		for(int i=0; i<N; i++) cin >> A[i];
		bool flag = false;
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				if(i == j) continue;
				if(is_palindrome(A[i] + A[j])) {
					cout << (A[i]+A[j]) << '\n';
					flag = true;
					break;
				}
			}
			if(flag) break;
		}
		if(!flag) cout << "0\n";
	}
}