#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int T;
char A[100005], B[100005];

ll f(int x) { return (ll)(x > 0 ? x : -x); }

int main() {
    scanf("%d", &T);
    while(T--) {
        ll ans = 0;
        scanf("%s %s", A, B);
        int alen = strlen(A), blen = strlen(B);
        if(alen != blen) { puts("-1"); continue; }
        int idx1 = 0, idx2 = 0;
        while(idx1 < alen && idx2 < blen) {
            while(idx1 < alen && A[idx1] == 'a') idx1++;
            while(idx2 < blen && B[idx2] == 'a') idx2++;
            ans += f(idx2 - idx1);
            idx1++, idx2++;
        }
        printf("%lld\n", ans);
    }
}
