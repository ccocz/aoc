#include <bits/stdc++.h>

using namespace std;

// INCOMPLETE SOLUTION

long long back(vector<int>& state,
		 vector<int>& target,
		 vector<vector<int>>& combs,
		 int idx,
		 map<pair<vector<int>, int>, int>& dp) {
	if (idx == combs.size()) {
		return equal(state.begin(), state.end(), target.begin()) ? 0 : INT_MAX;
	}
	
	if (dp.count({state, idx})) return dp[{state, idx}];
	
	long long ans = LLONG_MAX;
	
	int mini = INT_MAX;
	for (int k : combs[idx]) {
		mini = min(mini, target[k] - state[k]);
	}
		
	for (int i = 0; i <= mini; i++) {
		// if (i > 0 && i <= mini / 2) continue;
		
			
	for (int i = 0; i <= mini; i++) {
		for (int k : combs[idx]) {
			state[k] += i;
		}
		
		bool ok = true;
		
		for (int j = 0; j < target.size() && ok; j++) {
			if (state[j] == target[j]) continue;
			
			bool found = false;
			
			for (auto& sal : combs) {
				bool found1 = true, found2 = false;
				for (int& jj : sal) {
					if (state[jj] == target[jj]) found1 = false;
					if (jj == j) found2 = true;
				}
				
				if (found1 && found2) {
					found = true;
					break;
				}
			}
			
			ok &= found;
		}
		
		if (ok) ans = min(ans, back(state, target, combs, idx + 1, dp) + i);
		
		for (int k : combs[idx]) {
			state[k] -= i;
		}
	}
	
	return dp[{state, idx}] = ans;
}

bool cmp(vector<int>& a, vector<int>& b) {
	return a.size() >= b.size();
}

long long solve(vector<string>& v) {
	int len_main = v[0].length();
	string state = v[0].substr(1, len_main - 2);
	
	vector<vector<int>> combs;
	vector<int> target, stt(len_main - 2, 0);
	
	for (int i = 1; i <= v.size() - 2; i++) {
		stringstream ss(v[i]);
		
		char c;
		ss >> c;
		ss >> c;
		
		vector<int> mal;
		
		while (true) {
			mal.push_back(c - '0');
			ss >> c;
			
			if (c == ')') break;
			ss >> c;
		}
		
		combs.push_back(mal);
	}
	
	sort(combs.begin(), combs.end());
	
	stringstream sz(v[v.size() - 1]);
	char cc;
	sz >> cc;
	int mal;
	while (sz >> mal) {
		target.push_back(mal);
		sz >> cc; 
	}
	
	map<pair<vector<int>, int>, int> dp;
	
	return back(stt, target, combs, 0, dp);
}

int main() {
	string s;
	
	long long ans = 0;
	
	while (getline(cin, s)) {
		stringstream ss(s);
		
		string sz;
		vector<string> v;
	
		while (ss >> sz) {
			v.push_back(sz);
		}
		
		ans += solve(v);
	}
	
	cout << "ans: " << ans << endl;
	return 0;
}
