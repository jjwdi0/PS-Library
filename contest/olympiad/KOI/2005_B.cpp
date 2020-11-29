#include <bits/stdc++.h>
using namespace std;

int N, K, A[1005][1005], X[1005], Y[1005], dist[1005];

int po(int x) { return x * x; }

int adj(int x) {
	int res = (int)(sqrt(x) / 10);
	return res * res * 100 >= x ? res : res + 1; 
}

bool f(int x) {
	for(int i=2; i<=N; i++) dist[i] = 1e9;
	dist[1] = 0;
	queue<int> q;
	q.push(1);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i=1; i<=N; i++) if(A[u][i] <= x && dist[i] > dist[u] + 1) {
			q.push(i);
			dist[i] = dist[u] + 1;
		}
	}
	return dist[N] <= K;
}

int main() {
	scanf("%d %d", &N, &K), K++;
	for(int i=2; i<=N+1; i++) scanf("%d %d", X+i, Y+i);
	X[1] = Y[1] = 0, X[N+2] = Y[N+2] = 10000;
	N += 2;
	for(int i=1; i<=N; i++) for(int j=i+1; j<=N; j++) {
		int dx = X[i] - X[j], dy = Y[i] - Y[j];
		A[i][j] = A[j][i] = adj(po(dx) + po(dy));
	}
	int s = 1, e = 1e9;
	while(s <= e) {
		int mid = (s + e) >> 1;
		f(mid) ? e = mid - 1 : s = mid + 1;
	}
	printf("%d\n", s);
}