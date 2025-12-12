#include <bits/stdc++.h>

using namespace std;

int cnt(const vector<string>& piece) {
    int count = 0;
    for (const string& row : piece) {
        for (char c : row) {
            if (c == '#') count++;
        }
    }
    return count;
}

bool solve(vector<vector<string>>& grids, pair<vector<int>, vector<int>>& mz) {
    int total = 0;
    for (int i = 0; i < grids.size(); i++) {
        total += cnt(grids[i]) * mz.second[i];
    }
    
    return total <= mz.first[0] * mz.first[1];
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
        if (solve(grids, sal)) {
            ans++;
        }
    }
    
    cout << "ans: " << ans << endl;
    
    return 0;
}
