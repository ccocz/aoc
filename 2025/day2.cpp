#include <bits/stdc++.h>

using namespace std;

bool isInvalid(long long x) {
	string s = "";
	
	while (x) {
		s += '0' + (x % 10);
		x /= 10;
	}
	
	int n = s.length();
	
	for (int i = 1; i <= n / 2; i++) {
		if (n % i != 0) continue;
		
		set<string> ss;
		
		for (int j = 1; j <= n / i; j++) {
			ss.insert(s.substr((j - 1) * i, i));
		}
		
		if (ss.size() == 1) return true;
	}
	
	return false;
}

int main() {
	string s;
	
	getline(cin, s);
		
	long long a, b;
	char c;
	
	stringstream ss(s);
	
	long long ans = 0;
	
	while (ss >> a >> c >> b) {
		for (long long i = a; i <= b; i++) {
			ans += isInvalid(i) * i;			
		}
		ss >> c;
	}
	
	cout << ans;
		
	return 0;
}
