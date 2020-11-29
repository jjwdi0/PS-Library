#include <bits/stdc++.h>
#define ITER 50000
using namespace std;

int N;
double X[1003], Y[1003];
double x, y;

double sq(double x) { return x * x; }

int main() {
    scanf("%d", &N);
    for(int i=0; i<N; i++) scanf("%lf %lf", X+i, Y+i), x += X[i], y += Y[i];
    x /= N, y /= N;
    double temp = 1, ans = 0;
    for(int i=0; i<ITER; i++) {
        double mx = 0; int idx;
        for(int j=0; j<N; j++) {
            double dist = sq(X[j] - x) + sq(Y[j] - y);
            if(mx < dist) mx = dist, idx = j;
        }
        x += (X[idx] - x) * temp, y += (Y[idx] - y) * temp;
        temp *= 0.999;
        ans = sqrt(mx);
    }
    printf("%.3f %.3f\n%.3f", x, y, ans);
}
