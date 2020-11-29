#include <bits/stdc++.h>
using namespace std;
using ll = long long;

char a[1505], b[1505];
int alen, blen;
ll prime = 1234567891, ha_sh[26], hash_temp;
set<ll> v[1505];

bool chk(int x) {
	hash_temp = 0;
	for(int k=0; k<x; k++) hash_temp += ha_sh[b[k]-'a'];
	auto it = v[x].find(hash_temp);
	if(it != v[x].end()) return true;
	for(int k=x; k<blen; k++) {
		hash_temp -= ha_sh[b[k-x]-'a'];
		hash_temp += ha_sh[b[k]-'a'];
		it = v[x].find(hash_temp);
		if(it != v[x].end()) return true;
	}
	return false;
}

int main() {
	scanf("%s\n%s", a, b);
	alen = strlen(a); blen = strlen(b);
	ha_sh[0] = prime;
	for(int i=1; i<26; i++) {
		ha_sh[i] = ha_sh[i-1] * prime;
	}
	for(int i=0; i<alen; i++)
		{
			hash_temp = ha_sh[a[i]-'a'];
			for(int j=i+1; j<alen; j++)
			{
				hash_temp += ha_sh[a[j]-'a'];
				v[j-i+1].insert(hash_temp);
			}
		}
	for(int i=blen; i>0; i--) {
		if(chk(i)) {
			printf("%d", i);
			return 0;
		}
	}
	printf("0");
}