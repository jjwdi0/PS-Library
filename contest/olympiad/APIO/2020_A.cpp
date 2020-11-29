#include "paint.h"
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())

#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

int minimumInstructions(int N, int M, int K, vector<int> C, vector<int> A, vector<vector<int>> B) {
	vector<vector<int>> dp(N), col(K);
	vector<int> mx(N), v, dp2;
	for(int i=0; i<sz(B); i++) for(auto it : B[i]) col[it].push_back(i);
	for(int i=0; i<sz(dp); i++) dp[i].resize(sz(col[C[i]]));
	for(auto &it : dp[0]) it = 1;
	mx[0] = !!sz(dp[0]);
	for(int i=1; i<sz(dp); i++) for(int j=0, k=-1; j<sz(dp[i]); j++) {
		int siz = sz(col[C[i-1]]);
		int idx = col[C[i]][j];
		int pre = (idx + M - 1) % M;
		if(k == -1) {
			if(pre == M - 1) {
				if(siz > 0 && col[C[i-1]][k+siz] == pre) {
					dp[i][j] = dp[i-1][k+siz] + 1;
				} else {
					dp[i][j] = 1;
				}
				mx[i] = max(mx[i], dp[i][j]);
				k++;
				continue;
			}
			else k++;
		}
		while(k < siz && col[C[i-1]][k] < pre) k++;
		// printf("%d %d: %d %d %d\n", i, j, idx, pre, k);
		if(k == siz || col[C[i-1]][k] != pre) dp[i][j] = 1;
		else dp[i][j] = dp[i-1][k] + 1;
		mx[i] = max(mx[i], dp[i][j]);
	}
	for(int i=0; i<N; i++) if(mx[i] >= M) v.push_back(i);
	dp2.resize(sz(v));
	for(int i=0; i<sz(v); i++) {
		int idx = lower_bound(all(v), v[i] - M) - v.begin();
		if(v[idx] == v[i]) {
			if(i == 0) dp2[i] = 1;
			else return -1;
		} else dp2[i] = dp2[idx] + 1;
		// printf("%d %d %d\n", i, idx, dp2[i]);
	}
	if(sz(v) == 0) return -1;
	if(*v.begin() != M - 1 || *v.rbegin() != N - 1) return -1;
	return *dp2.rbegin();
}
