#include <bits/stdc++.h>
using namespace std;

int T, N;
string A[12];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while(T--) {
        cin >> N;
        for(int i=1; i<=N; i++) cin >> A[i];
        int now = (1 << N) - 1;
        for(int i=0; i<A[1].length(); i++) {
            int c = 0;
            for(int j=1; j<=N; j++) if((1 << (j - 1)) & now) {
                c |= A[j][i] == 'R' ? 1 : (A[j][i] == 'S' ? 2 : 4);
            }
            if(__builtin_popcount(c) != 2) continue;
            for(int j=1; j<=N; j++) if((1 << (j - 1)) & now) {
                if(c == 3 && A[j][i] == 'S') now ^= (1 << (j - 1));
                else if(c == 5 && A[j][i] == 'R') now ^= (1 << (j - 1));
                else if(c == 6 && A[j][i] == 'P') now ^= (1 << (j - 1));
            }
        }
        if(__builtin_popcount(now) != 1) cout << 0 << '\n';
        else {
            for(int i=1; i<=N; i++) if(now & (1 << (i - 1))) cout << i << '\n';
        }
    }
}
