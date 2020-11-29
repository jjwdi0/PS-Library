#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
using namespace std;

int N, A[403], B[403], D[2][403][803];
vector<int> v1, v2;

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", A+i);
    for(int i=1; i<=N; i++) scanf("%d", B+i);
    for(int i=1; i<=N; i++) if(A[i]) v1.push_back(A[i]);
    for(int i=1; i<=N; i++) if(B[i]) v2.push_back(B[i]);
    int cnt = N * 2 - sz(v1) - sz(v2);
    if(!sz(v1) || !sz(v2)) return puts("0"),0;
    for(int i=0; i<sz(v1); i++) for(int j=0; j<sz(v2); j++) for(int k=0; k<=cnt; k++) {
        D[i&1][j][k] = -2e9;
        if((i + j + k) % 2 || abs(i - j) > k) continue;
        if(k && abs(i - 1 - j) <= k - 1) D[i&1][j][k] = max(D[i&1][j][k], i ? D[(i+1)&1][j][k-1] : 0);
        if(k && abs(j - 1 - i) <= k - 1) D[i&1][j][k] = max(D[i&1][j][k], j ? D[i&1][j-1][k-1] : 0);
        if(k > 1 && i && j) D[i&1][j][k] = max(D[i&1][j][k], D[i&1][j][k-2]);
        D[i&1][j][k] = max(D[i&1][j][k], (i && j ? D[(i+1)&1][j-1][k] : 0) + v1[i] * v2[j]);
    }
    printf("%d\n", D[(sz(v1)+1)&1][sz(v2)-1][cnt]);
}
