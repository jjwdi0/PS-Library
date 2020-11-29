#include <bits/stdc++.h>
#define MOD 11092019
using namespace std;

int N, A[505], B[505];
vector<int> ans;

bool possible(int x) {
	for(int i=1, idx=1; i<=N+1; i++) if(i != x) B[idx++] = A[i];
	sort(B + 1, B + N + 1), reverse(B + 1, B + N + 1);
	for(int i=1; i<=N; i++) {
		int l = 0, r = i * (i - 1);
		for(int j=1; j<=i; j++) l += B[j];
		for(int j=i+1; j<=N; j++) r += min(B[j], i);
		if(l > r) return 0;
		if(i == N && l % 2) return 0;
	}
	return 1;
}

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N+1; i++) scanf("%d", A+i);
	for(int i=1; i<=N+1; i++) if(possible(i)) ans.push_back(i);
	printf("%d\n", int(ans.size()));
	for(auto it : ans) printf("%d\n", it);
}