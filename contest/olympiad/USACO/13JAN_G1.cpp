#include <stdio.h>
#include <map>
#include <algorithm>
#define sz(x) ((int)(x).size())
using namespace std;

int N, K, A[100005], ans;
map<int, int> m;

int main() {
	scanf("%d %d", &N, &K);
	for(int i=0; i<N; i++) scanf("%d", A+i);
	int i = 0, j = 0;
	m[A[0]]++;
	while(i < N && j < N) {
		if(sz(m) <= K + 1) {
			m[A[++j]]++;
			if(sz(m) <= K + 1) ans = max(ans, m[A[j]]);
		}
		else {
			m[A[i]]--;
			if(!m[A[i]]) m.erase(A[i]);
			i++;
		}
	}
	printf("%d", ans);
}