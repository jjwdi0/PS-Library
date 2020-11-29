#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

int N, K, A[505][4];
vector<int> vx, vy;
set<pr> S;
vector<pr> v, tr;
vector<vector<int>> px, py;

int sgn(int x) { return x < 0 ? -1 : (x > 0); }

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> K;
	for(int i=1; i<=N; i++) {
		for(int j=0; j<4; j++) cin >> A[i][j];
		S.insert(pr(A[i][0], A[i][1]));
		S.insert(pr(A[i][2], A[i][3]));
		vx.push_back(A[i][0]), vx.push_back(A[i][2]);
		vy.push_back(A[i][1]), vy.push_back(A[i][3]);
		v.push_back(pr(A[i][0], A[i][1]));
		v.push_back(pr(A[i][2], A[i][3]));
	}
	for(int i=1; i<=N; i++) for(int j=i+1; j<=N; j++) if((A[i][0] == A[i][2]) ^ (A[j][0] == A[j][2])) {
		int x = (A[i][0] == A[i][2] ? A[i][0] : A[j][0]);
		int y = (A[i][0] == A[i][2] ? A[j][1] : A[i][1]);
		if(min(A[i][0], A[i][2]) <= x && x <= max(A[i][0], A[i][2]) &&
		   min(A[i][1], A[i][3]) <= y && y <= max(A[i][1], A[i][3]) &&
		   min(A[j][0], A[j][2]) <= x && x <= max(A[j][0], A[j][2]) &&
		   min(A[j][1], A[j][3]) <= y && y <= max(A[j][1], A[j][3])) v.push_back(pr(x, y));
	}
	sort(vx.begin(), vx.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	px.resize(vx.size() + 3);
	py.resize(vy.size() + 3);
	for(auto it : v) {
		int x = it.first, y = it.second;
		x = (lower_bound(vx.begin(), vx.end(), x) - vx.begin()) + 1;
		y = (lower_bound(vy.begin(), vy.end(), y) - vy.begin()) + 1;
		px[x].push_back(it.second), py[y].push_back(it.first);
	}
	for(int i=1; i<=(int)vx.size(); i++) sort(px[i].begin(), px[i].end());
	for(int i=1; i<=(int)vy.size(); i++) sort(py[i].begin(), py[i].end());
	int cnt = 0;
	int cx = A[1][0], cy = A[1][1], dir;
	if(A[1][0] == A[1][2]) dir = (A[1][0] > A[1][2] ? 1 : 3);
	else dir = (A[1][1] > A[1][3] ? 2 : 0);
	for(;;) {
		tr.emplace_back(cx, cy);
		int x = (lower_bound(vx.begin(), vx.end(), cx) - vx.begin()) + 1;
		int y = (lower_bound(vy.begin(), vy.end(), cy) - vy.begin()) + 1;
		int nx, ny;
		if(dir == 0) {
			auto it = upper_bound(py[y].begin(), py[y].end(), cx);
			if(it == py[y].end()) { dir = 2; continue; }
			nx = *it, ny = cy;
		} else if(dir == 1) {
			auto it = lower_bound(px[x].begin(), px[x].end(), cy);
			if(it == px[x].begin()) { dir = 3; continue; }
			it--;
			nx = cx, ny = *it;
		} else if(dir == 2) {
			auto it = lower_bound(py[y].begin(), py[y].end(), cx);
			if(it == py[y].begin()) { dir = 0; continue; }
			nx = *(--it), ny = cy;
		} else if(dir == 3) {
			auto it = upper_bound(px[x].begin(), px[x].end(), cy);
			if(it == px[x].end()) { dir = 1; continue; }
			nx = cx, ny = *it;
		}
		if(cnt + (abs(nx - cx) + abs(ny - cy)) >= K) {
			cout << (cx + sgn(nx - cx) * (K - cnt)) << " " << (cy + sgn(ny - cy) * (K - cnt)) << "\n";
			return 0;
		}
		cnt += (abs(nx - cx) + abs(ny - cy));
		if(S.find(pr(nx, ny)) != S.end()) dir = (dir + 2) % 4;
		else dir = (dir + 3) % 4;
		cx = nx, cy = ny;
		if(nx == A[1][0] && ny == A[1][1]) break;
	}
	tr.push_back(pr(A[1][0], A[1][1]));
	K %= cnt;
	for(auto it : tr) {
		int dist = abs(it.second - cy) + abs(it.first - cx);
		if(K - dist <= 0) {
			cout << (cx + sgn(it.first - cx) * K) << " " << (cy + sgn(it.second - cy) * K) << "\n";
			return 0;
		}
		K -= dist;
		cx = it.first, cy = it.second;
	}
}