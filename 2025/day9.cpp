#include <bits/stdc++.h>

using namespace std;

int main() {
	string s;
	
	vector<pair<int, int>> v;
	
	while (cin >> s) {
		stringstream ss(s);
		
		int a, b;
		char c;
		
		ss >> a >> c >> b;
		
		v.push_back({b, a});
	}
	
	int n = v.size();
	
	/*long long area = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			area = max(area, 1LL * (abs(v[i].first - v[j].first) + 1) * (abs(v[i].second - v[j].second) + 1));
		}
	}*/
	
	vector<pair<int, pair<int, int>>> hor, ver;
	
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		if (v[i].first == v[j].first) {
			hor.push_back({v[i].first, {min(v[i].second, v[j].second), max(v[i].second, v[j].second)}});
		} else {
			ver.push_back({v[i].second, {min(v[i].first, v[j].first), max(v[i].first, v[j].first)}});
		}
	}
	
	sort(hor.begin(), hor.end());
	sort(ver.begin(), ver.end());
	
	for (auto& jal : hor) {
		cout << jal.second.first << " xx " << jal.second.second << endl; 
	}
	
	long long area = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			int mini_r = min(v[i].first, v[j].first);
			int maxi_r = max(v[i].first, v[j].first);
			
			int mini_c = min(v[i].second, v[j].second);
			int maxi_c = max(v[i].second, v[j].second);
			
			pair<int, int> horr = hor[0].second;
			int hi = 1;
			while (hi < hor.size() && hor[hi].first <= mini_r) {
				horr = {min(horr.first, hor[hi].second.first), max(horr.second, hor[hi].second.second)};
				
				hi++;
			}
			
			if (!(mini_c >= horr.first && maxi_c <= horr.second)) continue;
			
			horr = hor[hor.size() - 1].second;
			hi = hor.size() - 2;
			while (hi >= 0 && hor[hi].first >= maxi_r) {
				horr = {min(horr.first, hor[hi].second.first), max(horr.second, hor[hi].second.second)};
				hi--;
			}
			
			if (!(mini_c >= horr.first && maxi_c <= horr.second)) continue;
			
			pair<int, int> verr = ver[0].second;
			hi = 1;
			while (hi < ver.size() && ver[hi].first <= mini_c) {
				verr = {min(verr.first, ver[hi].second.first), max(verr.second, ver[hi].second.second)};
				hi++;
			}
			
			if (!(mini_r >= verr.first && maxi_r <= verr.second)) continue;
			
			verr = ver[ver.size() - 1].second;
			hi = ver.size() - 2;
			while (hi >= 0 && ver[hi].first >= maxi_c) {
				verr = {min(verr.first, ver[hi].second.first), max(verr.second, ver[hi].second.second)};
				hi--;
			}
			
			if (!(mini_r >= verr.first && maxi_r <= verr.second)) continue;
			
			area = max(area, 1LL * (abs(v[i].first - v[j].first) + 1) * (abs(v[i].second - v[j].second) + 1));
			
			// cout << v[i].first << "x" << v[i].second << " z " << v[j].first << "x" << v[j].second << " " << 1LL * (abs(v[i].first - v[j].first) + 1) * (abs(v[i].second - v[j].second) + 1) << endl;
		}
	}	
	
	cout << area << endl;
	
	return 0;
}
