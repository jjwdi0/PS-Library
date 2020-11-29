#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
using namespace std;
using base = complex<double>;
using ll = long long;

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

int T, N[3], A[100005];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	vector<int> v(60005, 0), u(60005, 0), res;
	cin >> N[0];
	for(int i=1, x; i<=N[0]; i++) {
		cin >> x;
		v[x+30000]++;
	}
	cin >> N[1];
	for(int i=1; i<=N[1]; i++) {
		cin >> A[i];
		A[i] += 30000;
	}
	cin >> N[2];
	for(int i=1, x; i<=N[2]; i++) {
		cin >> x;
		u[x+30000]++;
	}
	mul(u, v, res);
	ll ans = 0LL;
	for(int i=1; i<=N[1]; i++) ans += res[A[i]*2];
	cout << ans << "\n";
}
