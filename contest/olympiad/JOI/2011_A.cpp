#include <stdio.h>

int n, m, q, jungle[1003][1003], ocean[1003][1003], ice[1003][1003];
char a[1003];

int s1(int x1, int y1, int x2, int y2) {
	return jungle[x2][y2]-jungle[x2][y1-1]-jungle[x1-1][y2]+jungle[x1-1][y1-1];
}

int s2(int x1, int y1, int x2, int y2) {
	return ocean[x2][y2]-ocean[x2][y1-1]-ocean[x1-1][y2]+ocean[x1-1][y1-1];
}

int s3(int x1, int y1, int x2, int y2) {
	return ice[x2][y2]-ice[x2][y1-1]-ice[x1-1][y2]+ice[x1-1][y1-1];
}

int main() {
	scanf("%d %d %d", &n, &m, &q);
	for(int i=1; i<=n; i++) {
		scanf("%s", a);
		for(int j=0; j<m; j++) {
			if(a[j] == 'J') jungle[i][j+1] = 1;
			if(a[j] == 'O') ocean[i][j+1] = 1;
			if(a[j] == 'I') ice[i][j+1] = 1;
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			jungle[i][j] = jungle[i][j] + jungle[i-1][j] + jungle[i][j-1] - jungle[i-1][j-1];
			ocean[i][j] = ocean[i][j] + ocean[i-1][j] + ocean[i][j-1] - ocean[i-1][j-1];
			ice[i][j] = ice[i][j] + ice[i-1][j] + ice[i][j-1] - ice[i-1][j-1];
		}
	}
	while(q--) {
		int x, y, z, w;
		scanf("%d %d %d %d", &x, &y, &z, &w);
		printf("%d %d %d\n", s1(x, y, z, w), s2(x, y, z, w), s3(x, y, z, w));
	}
}