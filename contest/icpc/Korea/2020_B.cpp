#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int A[7], B[7];

int main() {
	for(int i=0; i<6; i++) cin >> A[i];
	for(int i=0; i<6; i++) cin >> B[i];
	int cnt = 0;
	for(int i=0; i<6; i++) for(int j=0; j<6; j++) cnt += (A[i] > B[j]);
	cout << cnt / gcd(cnt, 36) << "/" << 36 / gcd(cnt, 36) << "\n";
}