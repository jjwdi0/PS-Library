#include <bits/stdc++.h>
using namespace std;

const int ADD = 1e4;
int N, M, A[103];
bool D[103][20005];
vector<char> v;

int main() {
	scanf("%d %d", &N, &M);
	M += ADD;
	for(int i=0; i<N; i++) scanf("%d", A+i);
	D[1][ADD+A[0]] = 1;
	for(int i=1; i<N; i++) for(int j=0; j<=ADD*2; j++) if(D[i][j]) D[i+1][j+A[i]] = D[i+1][j-A[i]] = 1;
	if(!D[N][M]) return puts("0"),0;
	
	for(int i=N; i-1; i--) {
		if(D[i-1][M-A[i-1]]) v.push_back('+'), M -= A[i-1];
		else v.push_back('-'), M += A[i-1];
	}
	reverse(v.begin(), v.end());
	for(vector<char>::iterator it = v.begin(); it < v.end(); it++) {
		if(*it == '+') {
			printf("%d\n", it - v.begin() + 1);
			v.erase(it); it--;
		}
	}
	for(int i=0; i<v.size(); i++) puts("1");
	
}