#include <bits/stdc++.h>
using namespace std;

int N;
double A[1000005];

int main() {
    scanf("%d", &N);
    for(int i=1, x; i<=N; i++) {
        scanf("%d", &x);
        A[i] = x / 1000000.0;
    }
    double cur = 0, cnt = 0, ans = 0;
    int j = 1;
    for(int i=1; i<=N && j<=N; i++) {
        while(j <= N && cnt < 1) {
            double r = (cnt < 1e-9 ? 1 : cur / cnt);
            r *= 1 - A[j];
            cnt += A[j] / (1 - A[j]);
            cur = r * cnt;
            j++;
        }
        ans = max(ans, cur);
        double r = (cnt < 1e-9 ? 0 : cur / cnt);
        r /= (1 - A[i]);
        cnt -= A[i] / (1 - A[i]);
        cur = r * cnt;
    }
    printf("%d\n", int(1000000.0 * ans));
}
