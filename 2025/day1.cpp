#include <bits/stdc++.h>

using namespace std;

int main() {
	int n = 10;
	
	int st = 50;
	int ans = 0;
	
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		
		int mal = stoi(s.substr(1));
		
		if (s[0] == 'L') {
			for (int j = 0; j < mal; j++) {
				st--;
				
				if (st == 0) ans++;
				if (st == -1) st = 99;
			}
						
		} else {
			for (int j = 0; j < mal; j++) {
				st++;
				
				if (st == 0) ans++;
				if (st == 100) st = 0, ans++;
			}
			
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
