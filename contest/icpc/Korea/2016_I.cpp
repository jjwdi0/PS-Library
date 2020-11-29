#include <bits/stdc++.h>
using namespace std;

string t;
int d[4][2] = {1, 0, 0, -1, -1, 0, 0, 1}, N, M, dir, miss, x, y;

bool get(int p, int q) {
	return !(p < 0 || p > N || q < 0 || q > N);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> M;
	while(M--) {
		cin >> t >> miss;
		if(t == "TURN") {
			dir += (miss ? 1 : -1);
			dir = (dir + 4) % 4;
		} else {
			if(!get(x + miss * d[dir][0], y + miss * d[dir][1])) return cout << "-1\n", 0;
			x += miss * d[dir][0], y += miss * d[dir][1];
		}
	}
	cout << x << " " << y << "\n";
}