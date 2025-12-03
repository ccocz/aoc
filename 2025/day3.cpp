#include <bits/stdc++.h>

using namespace std;

long long solve(string& s) {
	int n = s.length();
	
	vector<vector<int>> dp(n, vector<int>(n));
	
	for (int i = 0; i < n; i++) {
		int maxi = i;
		
		for (int j = i; j < n; j++) {
			if (s[j] > s[maxi]) maxi = j;
			
			dp[i][j] = maxi;
		}
	}
	
	long long ans = 0;
	int nw = 0;
	
	for (int i = 1; i <= 12; i++) {
		nw = dp[nw][n - 13 + i];
		ans = 10 * ans + s[nw] - '0';
		nw++;
	}
	
	return ans;
}

int main() {
	vector<string> v;
	
	string s;
	
	while (cin >> s) {
		v.push_back(s);
	}
	
	long long ans = 0;
	
	for (string&s : v) {
		ans += solve(s);
	}
	
	cout << ans << endl;
		
	return 0;
}
