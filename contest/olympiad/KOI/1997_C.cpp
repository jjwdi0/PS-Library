#include <stdio.h>

int p, q, mission[22], n, qnum, min = 20160215;
int abs(int x) { return x>0?x:-x; }
int minor(int x, int y) { return x>y?y:x; }

void f(int x, int cnt, int wall1, int wall2) {
    int i;
    if(x == qnum) {
		if(cnt < min) min = cnt;
		return;
	}
    if(cnt > min) return;
    if((wall1 - mission[x]) * (wall2 - mission[x]) > 0) {
		if(abs(wall1 - mission[x]) > abs(wall2 - mission[x])) f(x + 1, cnt + abs(wall2 - mission[x]), wall1, mission[x]);
		else f(x + 1, cnt + abs(wall1 - mission[x]), mission[x], wall2);
	}
    else {
        f(x + 1, cnt + abs(wall2 - mission[x]), wall1, mission[x]);
        f(x + 1, cnt + abs(wall1 - mission[x]), mission[x], wall2);
    }
}

int main() {
    scanf("%d %d %d %d", &n, &p, &q, &qnum);
    for(int t=0; t<qnum; t++) scanf("%d", mission + t);
    f(0, 0, p, q);
    printf("%d", min);
}