#include <bits/stdc++.h>

using namespace std;

long long total(string& now,
		  string& end,
		  map<string, vector<string>>& edg,
		  map<string, long long>& dp) {
	
	if (now == end) {
		return 1;
	}
	
	if (dp.count(now)) {	
		return dp[now];
	}
	
	long long ttl = 0;
	
	for (string& jal : edg[now]) {
		ttl += total(jal, end, edg, dp);
	}
	
	return dp[now] = ttl;
}

int main() {
	string s;
	
	map<string, vector<string>> path;
	
	while (getline(cin, s)) {
		stringstream ss(s);
		
		string my, mal;
		ss >> my;
		
		my = my.substr(0, my.size() - 1);
		
		while (ss >> mal) {
			path[my].push_back(mal);
		}
	}
	
	string st = "svr", en = "fft";
	map<string, long long> dp;
	
	auto mal1 = total(st, en, path, dp);
	
	st = "fft", en = "dac";
	dp.clear();
	auto mal2 = total(st, en, path, dp);
	
	st = "dac", en = "out";
	dp.clear();
	auto mal3 = total(st, en, path, dp);
	
	cout << mal1 * mal2 * mal3 << endl;
	return 0;
}
