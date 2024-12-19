#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	
	string str = "";
	string s;
	
	while (cin >> s) {
		str += s;
	}
	
	vector<int> mal;
		
	vector<pair<int, int> > mala;
	vector<int> julluk;
	
	map<int, int> dar;
	
	int id = 0;
	int jad = -1;
	
	for (int i = 0; i < s.length(); i++) {
		if (i % 2 == 0) {
			for (int k = 0; k < s[i] - '0'; k++) {
				mal.push_back(id);
			}
			
			dar[id] = s[i] - '0';
			
			id++;
		} else {
			int nw = (int)mal.size();
			mala.push_back(make_pair(nw, nw + (s[i] - '0') - 1));
			julluk.push_back(nw);
						
			for (int k = 0; k < s[i] - '0'; k++) {
				mal.push_back(-1);
			}
			
		}
	}
	
	int j = mal.size() - 1, jj = mal.size() - 1;
	long long ans = 0;
	
	int balak = 0;
	
	while (jj > 0) {
		if (mala[0].first > jj) {
			break;
		}
		
		if (mal[jj] == -1) {
			jj--;
			continue;
		}
				
		bool found = false;
		
		while (julluk[balak] > mala[balak].second) balak++;
		
		for (int k = balak; k < mala.size(); k++) {
			if (julluk[k] > mala[k].second) continue;
			
			if (mala[k].second - julluk[k] + 1 < dar[mal[jj]]) continue;
			
			if (julluk[k] > jj) continue;
			
			int old = dar[mal[jj]];
			
			
			for (int m = julluk[k]; m < julluk[k] + old; m++) {
				swap(mal[m], mal[jj--]);
			}
			
			julluk[k] += old;
			
			found = true;
			break;
		}
		
		if (!found) jj--;
	}
		
	for (int i = 0; i < mal.size(); i++) {
		if (mal[i] > -1)
		ans += 1LL * i * mal[i];
	}
		
	/*for (int i = 0; i < mal.size(); i++) {
		if (mal[i] == -1) {
			while (j > i && mal[j] == -1) {
				j--;
			}
			
			if (j > i) mal[i] = mal[j], mal[j] = -1, j--;
		}
		
		if (mal[i] != -1)
		ans += 1LL * i * mal[i];
	}*/
	
	cout << ans << endl;
	return 0;
}
