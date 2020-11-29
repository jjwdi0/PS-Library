#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

int N, A[100005];

double g(int x, double K) { return K * x - A[x]; }

bool f(double x) {
    double mx = g(1, x);
    for(int i=2; i<N; i++) {
        if(g(i, x) - mx <= g(N, x)) return 1;
        mx = max(mx, g(i, x));
    }
    return 0;
}

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", A+i), A[i] += A[i-1];
    double s = 0, e = 1e9;
    for(int i=0; i<100; i++) {
        double mid = (s + e) / 2.0;
        f(mid) ? e = mid : s = mid;
    }
    printf("%.3f\n", s);
}
