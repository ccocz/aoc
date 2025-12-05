#include <bits/stdc++.h>

using namespace std;

int main() {
	string s;
	
	vector<pair<long long, long long>> rngs;
	
	while (getline(cin, s)) {
		if (s.empty()) break;
		
		stringstream mal(s);
		long long a, b;
		char c;
		mal >> a >> c >> b;
					
		rngs.push_back(make_pair(a, b));
	}
	
	long long n;
	int ans1 = 0;
	
	while (cin >> n) {
		for (auto& s : rngs) {
			if (n >= s.first && n <= s.second) {
				ans1++;
				break;
			}
		}
	}
	
	
	int na = rngs.size();
	long long ans = 0;
	
	sort(rngs.begin(), rngs.end());
	long long maxii = 0;
	
	for (int i = 0; i < na; i++) {
		auto sal = rngs[i];
		if (!i) {
			ans += sal.second - sal.first + 1;
			maxii = max(maxii, sal.second);
			continue;
		}
		
		if (sal.first > maxii) {
			ans += sal.second - sal.first + 1;
			maxii = max(maxii, sal.second);
			continue;
		}
		
		if (sal.second <= maxii) continue;
		
		ans += sal.second - maxii;
		maxii = max(maxii, sal.second);
	}
	
	cout << ans << endl;
	
	return 0;
}
