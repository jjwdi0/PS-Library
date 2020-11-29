#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, S, E;
ll A[2003], ans;
int D1[2003];
bool D2[103][103];

int main() {
    scanf("%d %d %d", &N, &S, &E);
    for(int i=1; i<=N; i++) scanf("%lld", A+i), A[i] += A[i-1];
    ans = (1LL << 61) - 1;
    if(S == 1) {
        for(int i=60; ~i; i--) {
            for(int j=1; j<=N; j++) D1[j] = 1e4;
            D1[0] = 0;
            ans ^= (1LL << i);
            for(int j=1; j<=N; j++) for(int k=0; k<j; k++) if((~ans & (A[j] - A[k])) == 0) D1[j] = min(D1[j], D1[k] + 1);
            if(D1[N] > E) ans ^= (1LL << i);
        }
    }
    else {
        for(int i=60; ~i; i--) {
            for(int j=1; j<=N; j++) for(int k=1; k<=E; k++) D2[j][k] = 0;
            D2[0][0] = 1;
            ans ^= (1LL << i);
            for(int j=1; j<=N; j++) for(int k=1; k<=E; k++) for(int iter=0; iter<j; iter++)
                if((~ans & (A[j] - A[iter])) == 0) D2[j][k] |= D2[iter][k-1];
            bool chk = 0;
            for(int j=S; j<=E; j++) chk |= D2[N][j];
            if(!chk) ans ^= (1LL << i);
        }
    }
    printf("%lld\n", ans);
}
