#include <stdio.h>
#include <vector>
#define INF 987654321
using namespace std;

struct edge {int to, cost, chk; };
vector<edge> v[130];
struct vertex { int cost, prev; } t[130];
int n, score[3][3] = { 100, 70, 40, 70, 50, 30, 40, 30, 20 }, k = 1;
int dir[4][2] = { -1, 0, 1, 0, 0, -1, 0, 1 }, ans;
char board[13][13];

int bellman_ford() {
	for(int i=0; i<=n*n+1; i++) {
		t[i].cost = -INF;
		t[i].prev = -1;
	}
	t[0].cost = 0;
	for(;;) {
		bool update = false;
		for(int i=0; i<=n*n+1; i++) {
			for(int j=0; j<v[i].size(); j++) {
				if(!v[i][j].chk) continue;
				if(t[i].cost != -INF && t[v[i][j].to].cost < t[i].cost + v[i][j].cost) {
					t[v[i][j].to].cost = t[i].cost + v[i][j].cost;
					t[v[i][j].to].prev = i;
					update = true;
				}
			}
		}
		if(!update) break;
	}
	return t[n*n+1].cost;
}

void make_rev() {
	int loc = n * n + 1;
	while(loc) {
		int temp = t[loc].prev;
		for(int i=0; i<v[temp].size(); i++) {
			if(v[temp][i].to == loc) {
				v[temp][i].chk = 0;
				break;
			}
		}
		for(int i=0; i<v[loc].size(); i++) {
			if(v[loc][i].to == temp) {
				v[loc][i].chk = 1;
				break;
			}
		}
		loc = temp;
	}
}

int main() {
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%s", board[i]);
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if((i + j + 1) % 2 == 0) {
				v[i*n+j+1].push_back({n * n + 1, 0, 1});
				continue;
			}
			v[0].push_back({i * n + j + 1, 0, 1});
			for(int p=0; p<4; p++) {
				if(i + dir[p][0] < 0 || i + dir[p][0] >= n || j + dir[p][1] < 0 || j + dir[p][1] >= n) continue;
				if(board[i+dir[p][0]][j+dir[p][1]] == 'F' || board[i][j] == 'F') {
					v[i*n+j+1].push_back({(i + dir[p][0]) * n + j + dir[p][1] + 1, 0, 1});
					v[(i+dir[p][0])*n+j+dir[p][1]+1].push_back({i * n + j + 1, 0, 0});
				} else {
					v[i*n+j+1].push_back({(i + dir[p][0]) * n + j + dir[p][1] + 1, score[board[i][j]-'A'][board[i+dir[p][0]][j+dir[p][1]]-'A'], 1});
					v[(i+dir[p][0])*n+j+dir[p][1]+1].push_back({i * n + j + 1, -score[board[i][j]-'A'][board[i+dir[p][0]][j+dir[p][1]]-'A'], 0});
				}
			}
		}
	}
	for(;;) {
		int increase_path = bellman_ford();
		if(increase_path < 0) break;
		ans += increase_path;
		make_rev();
	}
	printf("%d", ans);
}