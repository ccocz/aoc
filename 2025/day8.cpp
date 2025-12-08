#include <bits/stdc++.h>

using namespace std;

double dist(vector<double> x1, vector<double> x2) {
	return sqrt(pow(x1[0] - x2[0], 2) + pow(x1[1] - x2[1], 2) + pow(x1[2] - x2[2], 2));
}

void make_set(int v, vector<int>& parent, vector<int>& szz) {
    parent[v] = v;
    szz[v] = 1;
}

int find_set(int v, vector<int>& parent) {
    if (v == parent[v])
        return v;
    return find_set(parent[v], parent);
}

void union_sets(int a, int b, vector<int>& parent, vector<int>& szz) {
	a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b) {
        parent[b] = a;
		szz[a] += szz[b];
	}
}

int main() {
	string s;
	
	vector<vector<double>> v;
	
	while (cin >> s) {
		stringstream jj(s);
		
		double a, b, c;
		char d;
		jj >> a >> d >> b >> d >> c;
		
		vector<double> jal;
		jal.push_back(a);
		jal.push_back(b);
		jal.push_back(c);
		
		v.push_back(jal);
	}
	
	int n = v.size();
	
	vector<int> gr(n), sz(n);
	for (int i = 0; i < n; i++) {
		make_set(i, gr, sz);
	}
	
	vector<pair<double, pair<int, int>>> dista;
	
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			auto jal = dist(v[i], v[j]);
			dista.push_back({jal, {i, j}});
		}
	}
	
	sort(dista.begin(), dista.end());
	int cnt = 0;
	
	for (auto& jal : dista) {
		union_sets(jal.second.first, jal.second.second, gr, sz);
		
		if (sz[find_set(jal.second.first, gr)] == n) {
			cout << v[jal.second.first][0] << " " << v[jal.second.first][1] << " " << v[jal.second.first][2] << " xxx ";
			cout << v[jal.second.second][0] << " " << v[jal.second.second][1] << " " << v[jal.second.second][2] << endl;
			cout << 1LL * v[jal.second.first][0] * v[jal.second.second][0]  << endl;
			break;
		}
	}
	
	map<int, int> jll;
	
	for (int i = 0; i < n; i++) {
		jll[find_set(i, gr)]++;
	}
	
	
	vector<int> aaa;
	
	for (auto& x: jll) {
		aaa.push_back(x.second);
	}
	
	sort(aaa.begin(), aaa.end());
	
	int jla = aaa.size();

	cout << 1LL * aaa[jla - 1] * aaa[jla - 2] * aaa[jla - 3] << endl;
	return 0;
}
