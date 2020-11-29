#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ans[3], N, A[5003];
ll comp = 1e18;

int main() {
    scanf("%d", &N);
    for(int i=0; i<N; i++) scanf("%d", A+i);
    sort(A, A+N);
    for(int i=0; i<N; i++) {
        int idx = N - 1;
        for(int j=i+1; j<idx; j++) {
            ll cnt = A[i] + A[j];
            while(idx > j + 1 && abs(cnt + A[idx]) > abs(cnt + A[idx-1])) idx--;
            if(comp > abs(cnt + A[idx])) comp = abs(cnt + A[idx]), ans[0] = A[i], ans[1] = A[j], ans[2] = A[idx];
        }
    }
    for(int i=0; i<3; i++) printf("%d ", ans[i]);
}
