#include <bits/stdc++.h>

using namespace std;

int main() {
	string s;
	vector<string> v;
	
	int maxii = 0;
	
	while (getline(cin, s)) {
		v.push_back(s);
		maxii = max(maxii, (int)s.length());
	}
	
	int n = v.size();
	
	string lst = v[n - 1];
	
	long long ans = 0;
	
	for (int i = 0; i < lst.length(); i++) {
		if (lst[i] == '*') {
			long long lans = 1;
			int k = i;
			while (k < maxii) {
				int dgg = 0;
				for (int j = 0; j <= n - 2; j++) {
					if (v[j][k] != ' ') dgg = dgg * 10 + (v[j][k] - '0');
				}
				
				if (dgg == 0) break;
				lans *= dgg;
				k++;
			}
			
			ans += lans;
			
		} else if (lst[i] == '+') {
			long long lans = 0;
			int k = i;
			while (k < maxii) {
				int dgg = 0;
				for (int j = 0; j <= n - 2; j++) {
					if (v[j][k] != ' ') dgg = dgg * 10 + (v[j][k] - '0');
				}
				
				if (dgg == 0) break;
				lans += dgg;
				k++;
			}
			
			ans += lans;
		}
	}
	
	cout << ans << endl;
	return 0;
}
