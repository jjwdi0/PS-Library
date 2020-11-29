#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
using namespace std;
using base = complex<double>;

void FFT(vector<base> &v, bool inv) {
    int N = sz(v);
    for(int i=1, j=0; i<N; i++) {
        int bit = N >> 1;
        while(j >= bit) j -= bit, bit >>= 1;
        j += bit;
        if(i < j) swap(v[i], v[j]);
    }
    for(int i=2; i<=N; i<<=1) {
        double ang = 2 * 3.1415926535897932384626 / i * (inv ? -1 : +1);
        base wlen(cos(ang), sin(ang));
        for(int j=0; j<N; j+=i) {
            base w(1);
            for(int k=0; k<i/2; k++) {
                base p = v[j+k], q = v[j+k+i/2] * w;
                v[j+k] = p + q;
                v[j+k+i/2] = p - q;
                w *= wlen;
            }
        }
    }
    if(inv) for(int i=0; i<N; i++) v[i] /= N;
}

void mul(vector<int> &v1, vector<int> &v2, vector<int> &res) {
    int N = 1;
    while(N < sz(v1) + sz(v2)) N <<= 1;
    vector<base> V1(v1.begin(), v1.end()), V2(v2.begin(), v2.end());
    V1.resize(N), V2.resize(N), res.resize(N);
    FFT(V1, 0), FFT(V2, 0);
    for(int i=0; i<N; i++) V1[i] *= V2[i];
    FFT(V1, 1);
    for(int i=0; i<N; i++) res[i] = (int)round(V1[i].real());
}

int N, M;
char A[300005], B[300005];
vector<int> u[3], v[3], poly[3];

int main() {
	scanf("%d %d %s %s", &N, &M, A, B);
	reverse(B, B + M);
	for(int i=0; i<N; i++) u[0].push_back(A[i] == 'R');
	for(int i=0; i<N; i++) u[1].push_back(A[i] == 'S');
	for(int i=0; i<N; i++) u[2].push_back(A[i] == 'P');
	for(int i=0; i<M; i++) v[0].push_back(B[i] == 'R');
	for(int i=0; i<M; i++) v[1].push_back(B[i] == 'S');
	for(int i=0; i<M; i++) v[2].push_back(B[i] == 'P');
	for(int i=0; i<3; i++) mul(u[(i+1)%3], v[i], poly[i]);
	int ans = 0;
	for(int i=M-1; i<poly[0].size(); i++) ans = max(ans, poly[0][i] + poly[1][i] + poly[2][i]);
	printf("%d\n", ans);
}
