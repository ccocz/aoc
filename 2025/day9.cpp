#include <iostream>
#include <vector>
#include <sstream>

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

	long long area = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int mini_r = min(v[i].first, v[j].first);
			int maxi_r = max(v[i].first, v[j].first);
			
			int mini_c = min(v[i].second, v[j].second);
			int maxi_c = max(v[i].second, v[j].second);
			
			vector<pair<int, int>> jul;

			int hi = 0;
			while (hi < hor.size() && hor[hi].first <= mini_r) {
				if (max(hor[hi].second.first, mini_c) <= min(hor[hi].second.second, maxi_c)) jul.push_back(hor[hi].second);
				hi++;
			}

			sort(jul.begin(), jul.end());
			if (jul.empty() || !(mini_c >= jul[0].first && maxi_c <= jul[jul.size() - 1].second)) continue;

			bool ok = true;
			int maxx = jul[0].second;
			for (int ii = 1; ii < jul.size(); ii++) {
				ok &= jul[ii].first <= maxx;
				maxx = max(maxx, jul[ii].second);
			}

			if (!ok) continue;
			jul.clear();

			hi = hor.size() - 1;
			while (hi >= 0 && hor[hi].first >= maxi_r) {
				if (max(hor[hi].second.first, mini_c) <= min(hor[hi].second.second, maxi_c)) jul.push_back(hor[hi].second);
				hi--;
			}

			sort(jul.begin(), jul.end());
			if (jul.empty() || !(mini_c >= jul[0].first && maxi_c <= jul[jul.size() - 1].second)) continue;

			ok = true;
			maxx = jul[0].second;
			for (int ii = 1; ii < jul.size(); ii++) {
				ok &= jul[ii].first <= maxx;
				maxx = max(maxx, jul[ii].second);
			}

			if (!ok) continue;
			jul.clear();
			
			hi = 0;
			while (hi < ver.size() && ver[hi].first <= mini_c) {
				if (max(ver[hi].second.first, mini_r) <= min(ver[hi].second.second, maxi_r)) jul.push_back(ver[hi].second);
				hi++;
			}

			sort(jul.begin(), jul.end());
			if (jul.empty() || !(mini_r >= jul[0].first && maxi_r <= jul[jul.size() - 1].second)) continue;

			ok = true;
			maxx = jul[0].second;
			for (int ii = 1; ii < jul.size(); ii++) {
				ok &= jul[ii].first <= maxx;
				maxx = max(maxx, jul[ii].second);
			}
						
			if (!ok) continue;
			jul.clear();
			hi = ver.size() - 1;
			while (hi >= 0 && ver[hi].first >= maxi_c) {
				if (max(ver[hi].second.first, mini_r) <= min(ver[hi].second.second, maxi_r)) jul.push_back(ver[hi].second);
				hi--;
			}
			
			sort(jul.begin(), jul.end());
			if (jul.empty() || !(mini_r >= jul[0].first && maxi_r <= jul[jul.size() - 1].second)) continue;

			ok = true;
			maxx = jul[0].second;
			for (int ii = 1; ii < jul.size(); ii++) {
				ok &= jul[ii].first <= maxx;
				maxx = max(maxx, jul[ii].second);
			}

			if (!ok) continue;
			jul.clear();
			
			area = max(area, 1LL * (abs(v[i].first - v[j].first) + 1) * (abs(v[i].second - v[j].second) + 1));
		}
	}	
	
	cout << area << endl;
	
	return 0;
}
