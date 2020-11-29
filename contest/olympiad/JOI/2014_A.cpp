#include <stdio.h>
#include <algorithm>
using namespace std;

int N, M, cnt, ans;
char A[1003][1003], B[3][3];

int f(int x, int y, char ch) {
	int ret = cnt;
	if(x > 0 && y > 0) {
		int c1 = 0;
		for(int i=0; i<2; i++) {
			for(int j=0; j<2; j++) {
				if(A[x+i-1][y+j-1] == B[i][j]) c1++;
			}
		}
		if(c1 == 4 && ch != A[x][y]) ret--;
		if(c1 == 3 && A[x][y] != B[1][1] && ch == B[1][1]) ret++;
	}
	if(x > 0 && y < M - 1) {
		int c1 = 0;
		for(int i=0; i<2; i++) {
			for(int j=0; j<2; j++) {
				if(A[x+i-1][y+j] == B[i][j]) c1++;
			}
		}
		if(c1 == 4 && ch != A[x][y])ret--;
		if(c1 == 3 && A[x][y] != B[1][0] && ch == B[1][0]) ret++;
	}
	if(x < N - 1 && y > 0) {
		int c1 = 0;
		for(int i=0; i<2; i++) {
			for(int j=0; j<2; j++) {
				if(A[x+i][y+j-1] == B[i][j])c1++;
			}
		}
		if(c1 == 4 && ch != A[x][y]) ret--;
		if(c1 == 3 && A[x][y] != B[0][1] && ch == B[0][1]) ret++;
	}
	if(x < N - 1 && y < M - 1) {
		int c1 = 0;
		for(int i=0; i<2; i++) {
			for(int j=0; j<2; j++) {
				if(A[x+i][y+j] == B[i][j]) c1++;
			}
		}
		if(c1 == 4 && ch != A[x][y]) ret--;
		if(c1 == 3 && A[x][y] != B[0][0] && ch == B[0][0]) ret++;
	}
	return ret;
}

int main() {
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++) scanf("%s", A[i]);
	for(int i=0; i<2; i++) scanf("%s", B[i]);
	for(int i=0; i<N-1; i++) {
		for(int j=0; j<M-1; j++) {
			int det = 0;
			for(int k=0; k<2; k++) {
				for(int p=0; p<2; p++) {
					det += (A[i+k][j+p] == B[k][p]);
				}
			}
			cnt += (det == 4);
		}
	}
	for(int i=0; i<N; i++) {
		for(int j=0; j<M; j++) {
			ans = max({ans, cnt, f(i, j, 'J'), f(i, j, 'O'), f(i, j, 'I')});
		}
	}
	printf("%d", ans);
}