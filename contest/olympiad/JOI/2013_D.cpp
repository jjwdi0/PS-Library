#include <stdio.h>

int n, I, IO, IOI, cnt;
char a[1000005];

int main() {
	scanf("%d\n%s", &n, a);
	for(int i=0; i<n; i++) {
		if(a[i] == 'J') I++;
		else if(a[i] == 'O') {
			if(I > 0) I--, IO++;
			else if(IOI > 0) IOI--, cnt += 2, IO += 2;
		} else if(a[i] == 'I') {
			if(IO > 0) {
				IO--;
				if(IO == cnt - 1) cnt--;
				IOI++;
			}
			else I++;
		}
	}
	printf("%d", IOI + cnt / 2);
}