#include <stdio.h>

int N, M, D1[2222][2222], D2[2222][2222], ans;
char A[2222], B[2222];
int max(int X, int Y){return X>Y?X:Y;}

int main()
{
	scanf("%d %d", &N, &M);
	scanf("%s\n%s", A, B);
	D1[0][1] = B[M-1] == 'I', D1[1][0] = A[N-1] == 'I';
	for(int i=2; i<=M; i++) D1[0][i] = ((B[M-i] == 'I') + D2[0][i-1]) * (B[M-i] == 'I'), D2[0][i] = ((B[M-i] == 'O') + D1[0][i-1]) * ((B[M-i] == 'O') && D1[0][i-1]);
	for(int i=2; i<=N; i++) D1[i][0] = ((A[N-i] == 'I') + D2[i-1][0]) * (A[N-i] == 'I'), D2[i][0] = ((A[N-i] == 'O') + D1[i-1][0]) * ((A[N-i] == 'O') && D1[i-1][0]);
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=M; j++) {
			if(A[N-i] == 'I') D1[i][j] = max(D1[i][j], D2[i-1][j]+1);
			else D2[i][j] = max(D2[i][j], (D1[i-1][j]+1) * (!!D1[i-1][j]));
			if(B[M-j] == 'I') D1[i][j] = max(D1[i][j], D2[i][j-1]+1);
			else D2[i][j] = max(D2[i][j], (!!D1[i][j-1]) * (D1[i][j-1] + 1));
		}
	}
	for(int i=0; i<=N; i++) for(int j=0; j<=M; j++) ans = max(ans, D1[i][j]);
	printf("%d", ans);
}