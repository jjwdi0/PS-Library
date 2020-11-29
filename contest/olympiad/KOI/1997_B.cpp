#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

struct Z { int xpos, ypos, count; };
queue<Z> q;
int n, a[52][52], dijkstra[52][52];

int main() {
	scanf("%d", &n);
	for(int i=0; i<n; i++) for(int j=0; j<n; dijkstra[i][j]=-1, j++) scanf("%1d", &a[i][j]);
	q.push({0, 0, 0});
	while(!q.empty()) {
		Z t = q.front(); q.pop();
		if(t.xpos < 0 || t.xpos >= n || t.ypos < 0 || t.ypos >= n) continue;
		if(a[t.xpos][t.ypos] == 0) t.count++;
		if(dijkstra[t.xpos][t.ypos] == -1 || dijkstra[t.xpos][t.ypos] > t.count) dijkstra[t.xpos][t.ypos] = t.count;
		else continue;
		q.push({t.xpos + 1, t.ypos, t.count});
		q.push({t.xpos - 1, t.ypos, t.count});
		q.push({t.xpos, t.ypos + 1, t.count});
		q.push({t.xpos, t.ypos - 1, t.count});
	}
	printf("%d", dijkstra[n-1][n-1]);
}