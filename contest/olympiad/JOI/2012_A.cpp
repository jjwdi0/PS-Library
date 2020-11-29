#include <stdio.h>
#include <string.h>

char a[1000003];
int J, O, I, ans, len;
int max(int X, int Y){ return X>Y?X:Y; }

main() {
	scanf("%s", a);
	len = strlen(a);
	if(a[0] == 'J') J++;
	if(a[0] == 'O')O++;
	if(a[0] == 'I')I++;
	for(int i=1; i<len; i++) {
		if(a[i] == 'J') {
			if(a[i-1] == 'J') J++;
			else {
				if(a[i-1] == 'O') O = 0;
				J = 1;
			}
		} else if(a[i] == 'O') {
			if(a[i-1] == 'O') O++;
			else {
				if(a[i-1] != 'J') J = 0;
				O = 1;
			}
		} else if(a[i] == 'I') {
			if(a[i-1] == 'I') I++;
			else {
				if(a[i-1] == 'J') J = 0;
				I = 1;
			}
			if(O == I && J >= O) ans = max(ans, O);
		}
	}
	printf("%d", ans);
}