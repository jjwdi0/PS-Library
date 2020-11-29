#include <bits/stdc++.h>
#define kill() return puts("-1"),0
using namespace std;
using pr = pair<int, int>;

int N, K;
char A[200005];
deque<int> dq[3];

int main() {
	scanf("%d %d %s", &N, &K, A + 1);
	for(int i=1; i<=N; i++) {
		if(A[i] == 'J') dq[0].push_back(i);
		if(dq[0].size() == K) break;
	}
	if(dq[0].size() != K) kill();
	for(int i=dq[0].back()+1; i<=N; i++) {
		if(A[i] == 'O') dq[1].push_back(i);
		if(dq[1].size() == K) break;
	}
	if(dq[1].size() != K) kill();
	for(int i=dq[1].back()+1; i<=N; i++) {
		if(A[i] == 'I') dq[2].push_back(i);
		if(dq[2].size() == K) break;
	}
	if(dq[2].size() != K) kill();
	int ans = dq[2].back() - dq[0].front();
	for(int i=dq[0].back()+1; i<=N; ) {
		dq[0].pop_front();
		while(i <= N && A[i] != 'J') i++;
		if(i > N) break;
		dq[0].push_back(i++);
		while(!dq[1].empty() && dq[1].front() < i) dq[1].pop_front();
		int j;
		if(dq[1].empty()) j = i;
		else j = dq[1].back() + 1;
		while(dq[1].size() < K && j <= N) {
			if(A[j] == 'O') dq[1].push_back(j);
			if(dq[1].size() == K) break;
			j++;
		}
		if(dq[1].size() != K) break;
		while(!dq[2].empty() && dq[2].front() < dq[1].back()) dq[2].pop_front();
		if(dq[2].empty()) j = dq[1].back();
		else j = dq[2].back() + 1;
		while(dq[2].size() < K && j <= N) {
			if(A[j] == 'I') dq[2].push_back(j);
			if(dq[2].size() == K) break;
			j++;
		}
		if(dq[2].size() != K) break;
		ans = min(ans, dq[2].back() - dq[0].front());
	}
	printf("%d\n", ans + 1 - K * 3);
}
