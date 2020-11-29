#include <stdio.h>
#include <queue>
using namespace std;
int T, A, B;
queue<pair<int, int>> q;
bool go[5555555][2];
int main()
{
	scanf("%d %d %d", &T, &A, &B);
	q.push(make_pair(0, 0));
	while(!q.empty())
	{
		int u = q.front().first, v = q.front().second; q.pop();
		if(u + A <= T && !go[u + A][v]) go[u + A][v] = 1, q.push(make_pair(u + A, v));
		if(u + B <= T && !go[u + B][v]) go[u + B][v] = 1, q.push(make_pair(u + B, v));
		if(!v && !go[u / 2][v]) go[u / 2][v + 1] = 1, q.push(make_pair(u / 2, v + 1));
	}
	for(int i=T; ~i; i--) if(go[i][0] || go[i][1]) return printf("%d", i),0;
}