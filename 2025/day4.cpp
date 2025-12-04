#include <bits/stdc++.h>

using namespace std;

int main() {
	vector<string> v;
	
	string s;
	
	while (cin >> s) {
		v.push_back(s);
	}
	
	int n = v.size(), m = v[0].size();
	
	int di[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
	int dj[] = { 0, 0, 1, -1, 1, -1, -1, 1 };
	
	int ans = 0;
	
	vector<pair<int, int>> rmd;
	
	while (true) {
		vector<pair<int, int>> rmd;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (v[i][j] != '@') continue;
				
				int mal = 0;
				
				for (int k = 0; k < 8; k++) {
					int nx = i + di[k];
					int ny = j + dj[k];
					
					if (nx >= 0 && nx < n && ny >= 0 && ny < m && v[nx][ny] == '@') mal++;
				}
				
				if (mal < 4) ans++, rmd.push_back(make_pair(i, j));
			}
		}
		
		if (rmd.empty()) break;
		
		for (auto& sal : rmd) {
			v[sal.first][sal.second] = 'x';
		}
	}
	
	
	cout << ans << endl;
			
	return 0;
}
