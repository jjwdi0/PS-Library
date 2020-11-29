#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

int N, A[105], D[105][105][105];
vector<pr> v;

void trace(int s, int e, int k) {
    if(D[s][e][k] == D[s][e][k-1]) { trace(s, e, k - 1); return; }
    if(s == e - 1) { v.push_back(pr(s, e)); return; }
    if(A[s] != A[e] && D[s][e][k] == k + k + e - s + D[s+1][e-1][k-1]) {
        v.push_back(pr(s, e));
        trace(s + 1, e - 1, k - 1);
        return;
    }
    for(int i=s+2; i<e; i+=2) {
        if(D[s][e][k] == D[s][i-1][k] + D[i][e][k]) {
            trace(s, i - 1, k);
            trace(i, e, k);
            return;
        }
    }
}

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N; i++) scanf("%1d", A+i);
	for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) for(int k=0; k<=N; k++) D[i][j][k] = 1e9;
	for(int i=1; i<N; i++) if(A[i] != A[i+1]) for(int j=1; j<=N; j++) D[i][i+1][j] = 3;
	for(int i=3; i<N; i+=2) for(int j=1; i+j<=N; j++) {
        int s = j, e = i + j;
        for(int k=1; k<=N; k++) {
            D[s][e][k] = min(D[s][e][k], D[s][e][k-1]);
            if(A[s] != A[e]) D[s][e][k] = min(D[s][e][k], D[s+1][e-1][k-1] + k + k + e - s);
            for(int p=s+2; p<e; p+=2) D[s][e][k] = min(D[s][e][k], D[s][p-1][k] + D[p][e][k]);
        }
	}
	int idx = 0;
	for(int i=1; i<=N; i++) if(D[1][N][idx] > D[1][N][i]) idx = i;
	printf("%d\n", D[1][N][idx]);
	trace(1, N, idx);
	sort(v.begin(), v.end());
	for(auto it : v) printf("%d %d\n", it.first, it.second);
}
