#include <stdio.h>
#include <vector>
using namespace std;

int N, A[111111], cnt = 1;
vector<int> v;

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) scanf("%d", A+i);
	A[N] = A[N-1];
	for(int i=1; i<=N; i++) {
		if(A[i] != A[i-1]) cnt++;
		else v.push_back(cnt), cnt = 1;
	}
	if((int)v.size() == 1) printf("%d", v[0]);
	else if((int)v.size() == 2) printf("%d", v[0] + v[1]);
	else {
		int ans = 0;
		for(int i=0; i<v.size()-2; i++) ans = (ans > v[i] + v[i+1] + v[i+2] ? ans : v[i] + v[i+1] + v[i+2]);
		printf("%d", ans);
	}
}