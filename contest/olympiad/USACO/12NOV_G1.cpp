#include <bits/stdc++.h>
#define MOD 2012
using namespace std;

int N, D[1003][1003], cnt[1003];
char A[1005];

void add(int &x, int y) { x = (x + y) % MOD; }

int main() {
    scanf("%s", A);
    N = strlen(A);
    int st = 0;
    for(int i=0; i<N; i++) {
        cnt[i] = st;
        st += (A[i] == '(' ? 1 : -1);
        if(st < 0) return puts("0"),0;
    }
    if(st) return puts("0"),0;
    D[0][0] = 1;
    for(int i=0; i<N; i++) for(int j=0; j<=N; j++) if(D[i][j]) {
        if(A[i] != ')' || cnt[i] != j) add(D[i+1][j], D[i][j]);
        if(A[i] == '(') add(D[i+1][j+1], D[i][j]);
        else if(A[i] == ')' && j) add(D[i+1][j-1], D[i][j]);
    }
    printf("%d\n", D[N][0] % MOD);
}
