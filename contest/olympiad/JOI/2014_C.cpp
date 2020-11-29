#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll A[200005];

bool f(ll x) {
    ll cnt = 0LL;
    for(int i=1, j=0; i<=N; cnt -= A[i] - A[i-1], i++) {
        while(cnt < x && j <= N * 2) cnt += A[j+1] - A[j++];
        if(cnt > A[N] / 3 || cnt < x) continue;
        int lo = j + 1, hi = i + N - 1;
        while(lo <= hi) {
            int mid = lo + hi >> 1;
            if(A[mid] - A[j] >= cnt) hi = mid - 1;
            else lo = mid + 1;
        }
        if(A[lo] - A[j] >= cnt && A[i + N - 1] - A[lo] >= cnt) return true;
    }
    return false;
}

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", A+i), A[N+i] = A[i];
    for(int i=1; i<=N*2; i++) A[i] += A[i-1];
    ll lo = 0, hi = A[N] / 3;
    while(lo <= hi) {
        ll mid = lo + hi >> 1;
        f(mid) ? lo = mid + 1LL : hi = mid - 1LL;
    }
    printf("%lld\n", hi);
}
