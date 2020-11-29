#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

int N, B[200005], C[200005];
pr A[200005];
multiset<int> ms;

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N+1; i++) {
		scanf("%d", &A[i].first);
		A[i].second = i;
	}
	sort(A + 1, A + N + 2);
	for(int i=1; i<=N; i++) scanf("%d", B+i);
	sort(B + 1, B + N + 1);
	for(int i=1; i<=N; i++) ms.insert(max(A[i+1].first - B[i], 0));
	for(int i=1; i<=N+1; i++) {
		C[A[i].second] = *ms.rbegin();
		if(i <= N) ms.erase(ms.find(max(0, A[i+1].first - B[i])));
		ms.insert(max(A[i].first - B[i], 0));
	}
	for(int i=1; i<=N+1; i++) printf("%d ", C[i]);
}
