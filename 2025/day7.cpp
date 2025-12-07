#include <bits/stdc++.h>

using namespace std;

long long part2(vector<string>& gr, int x, int y, vector<vector<long long>>& dp) {
	if (x >= gr.size()) return 1;
	
	if (dp[x][y] != -1) return dp[x][y];
	
	long long sum = 0;
	
	if (gr[x][y] == '^') {
		if (y + 1 < gr[0].length()) sum += part2(gr, x, y + 1, dp);
		if (y - 1 >= 0) sum += part2(gr, x, y - 1, dp);
	} else {
		sum += part2(gr, x + 1, y, dp);
	}
	
	return dp[x][y] = sum;
}

int main() {
	vector<string> v;
	
	string s;
	
	pair<int, int> st;
	
	while (cin >> s) {
		v.push_back(s);
	}
	
	queue<pair<int, int>> mal;
	
	int n = v.size(), m = v[0].length();
	
	vector<vector<long long>> dp(n, vector<long long>(m, -1));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (v[i][j] == 'S') {
				mal.push(make_pair(i, j));
				cout << "part2: " << part2(v, i, j, dp) << endl;;
			} 
		}
	}
	

	int ans = 0;
	set<pair<int, int>> jal, dal;
	
	while (!mal.empty()) {
		auto sl = mal.front();
		mal.pop();
		
		if (dal.find(sl) != dal.end()) continue; 
		
		dal.insert(sl);
				
		if (sl.first + 1 < n) {
			if (v[sl.first + 1][sl.second] == '^') {
				jal.insert(make_pair(sl.first + 1, sl.second));
				
				if (sl.second - 1 >= 0) {
					mal.push(make_pair(sl.first + 1, sl.second - 1));
				}
				if (sl.second + 1 < m) {
					mal.push(make_pair(sl.first + 1, sl.second + 1));
				}
			} else {
				mal.push(make_pair(sl.first + 1, sl.second));
			}
		}
	}
	
	cout << "part1: " << jal.size() << endl;
	
	
	return 0;
}
