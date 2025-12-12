#include <bits/stdc++.h>

using namespace std;

vector<string> rotate90(const vector<string>& g) {
    int n = g.size(), m = g[0].size();
    vector<string> r(m, string(n, ' '));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            r[j][n-1-i] = g[i][j];
        }
    }
    return r;
}

vector<string> rotate180(const vector<string>& g) {
    return rotate90(rotate90(g));
}

vector<string> rotate270(const vector<string>& g) {
    return rotate90(rotate180(g));
}

vector<string> flipHorizontal(const vector<string>& g) {
    vector<string> r = g;
    for (auto &row : r) {
        reverse(row.begin(), row.end());
    }
    return r;
}

vector<string> flipVertical(const vector<string>& g) {
    vector<string> r = g;
    reverse(r.begin(), r.end());
    return r;
}

vector<string> flipDiagonalMain(const vector<string>& g) {
    int n = g.size(), m = g[0].size();
    vector<string> r(m, string(n, ' '));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            r[j][i] = g[i][j];
        }
    }
    return r;
}

vector<string> flipDiagonalAnti(const vector<string>& g) {
    int n = g.size(), m = g[0].size();
    vector<string> r(m, string(n, ' '));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            r[m-1-j][n-1-i] = g[i][j];
        }
    }
    return r;
}

set<vector<string>> symms(const vector<string>& g) {
    set<vector<string>> out;
    out.insert(g);
    out.insert(rotate90(g));
    out.insert(rotate180(g));
    out.insert(rotate270(g));
    out.insert(flipHorizontal(g));
    out.insert(flipVertical(g));
    out.insert(flipDiagonalMain(g));
    out.insert(flipDiagonalAnti(g));
    return out;
}

bool place(vector<vector<bool>>& vis, int x, int y, const vector<string>& grid) {
	int n = grid.size(), m = grid[0].length();
	int nn = vis.size(), mm = vis[0].size();

	if (x + (n - 1) >= nn || y + (m - 1) >= mm) return false;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '#' && vis[i + x][j + y]) return false;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '#') vis[i + x][j + y] = true;
		}
	}
	
	return true;
}

void undo(vector<vector<bool>>& vis, int x, int y, const vector<string>& grid) {
	int n = grid.size(), m = grid[0].length();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '#') vis[i + x][j + y] = false;
		}
	}
}

int total = 0;

bool iter(vector<vector<bool>>& vis,
		  vector<vector<string>>& grids,
		  vector<int>& v,
		  int idx,
		  int cnt,
		  map<pair<pair<int, int>, vector<vector<bool>>>, bool>& dp) {
	//if (++total <= 1000) {
		for (int i = 0; i < vis.size(); i++) {
			for (int j = 0; j < vis.size(); j++) {
				cout << (vis[i][j] ? '*' : '.');
			}
			cout << endl;
		}
		
//		for (auto mal: grids[idx]) cout << mal << endl;
		
		puts("");
		
		cout << idx << " " << cnt << " " << dp.count({{idx, cnt}, vis}) << endl;
	//}


	if (idx == v.size()) {
		return true;
	}
	
	if (cnt >= v[idx]) {
		return iter(vis, grids, v, idx + 1, 0, dp);
	}
	
	if (dp.count({{idx, cnt}, vis})) return dp[{{idx, cnt}, vis}];
	int n = vis.size(), m = vis[0].size();
	
	bool ok = false;
		
	for (int i = 0; i < n && !ok; i++) {
		for (int j = 0; j < m && !ok; j++) {
			int kk = 0;
			for (const auto& sal : symms(grids[idx])) {
				kk++;
				if (ok) break;
				if (place(vis, i, j, sal)) {
					cout << "placed: " << " " << idx << " " << cnt << " " << i << " " << j << " " << kk << endl;
					ok |= iter(vis, grids, v, idx, cnt + 1, dp);	
					undo(vis, i, j, sal);
				}
			}
		}
	}
				
	return dp[{{idx, cnt}, vis}] = ok;
}

bool solve(vector<vector<string>>& grids, pair<vector<int>, vector<int>>& mz) {
	vector<vector<bool>> vis(mz.first[0], vector<bool>(mz.first[1]));
	map<pair<pair<int, int>, vector<vector<bool>>>, bool> dp;
	return iter(vis, grids, mz.second, 0, 0, dp);
}

int main() {
	vector<vector<string>> grids;
	
	string s;
	
	while (getline(cin, s)) {
		if (s.length() == 2) {
			vector<string> nxt;
			while (getline(cin, s)) {
				if (s.empty()) break;
				nxt.push_back(s);
			}
			grids.push_back(nxt);
		}
		
		if (grids.size() == 6) break;
	}
	
	vector<pair<vector<int>, vector<int>>> mzs;
	
	while (getline(cin, s)) {
		stringstream mal(s);
		
		char c;
		int x, y;
		mal >> x >> c >> y;
		
		vector<int> mal1{y, x}, mal2;
		
		mal >> c;
		while (mal >> x) {
			mal2.push_back(x);
		}
		
		mzs.push_back({mal1, mal2});
	}
	
	int ans = 0;
	
	for (auto& sal : mzs) {
		ans += solve(grids, sal);
		cout << "ans: " << ans << endl;
	}
	
	cout << ans << endl;
	
		
	return 0;
}
