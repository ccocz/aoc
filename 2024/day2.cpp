#include <iostream>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

int sign(int x) {
	if (x == 0) return 0;
	if (x > 0) return 1;
	return -1;
}

bool _safe(multiset<int>&diffs) {
	return *diffs.begin() * *diffs.rbegin() > 0
		&& min(abs(*diffs.begin()), abs(*diffs.rbegin())) >= 1
		&& max(abs(*diffs.begin()), abs(*diffs.rbegin())) <= 3;

}

int main() {
	vector<vector<int> > v;
	std::string line;


    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }

        std::vector<int> row;
        std::istringstream stream(line);
        int value;

        while (stream >> value) {
            row.push_back(value);
        }

        v.push_back(row);
    }
    
    int safe = 0;
    
	for (vector<int>& a: v) {
		multiset<int> diffs;
				
		
		for (int k = 0; k < a.size() - 1; k++) {
			diffs.insert(a[k + 1] - a[k]);
			
		}
		
		if (_safe(diffs)) {
			safe++;
			continue;
		}
		
		for (int k = 0; k < a.size(); k++) {
			vector<int> removed, added;
			
			if (k + 1 < a.size()) {
				diffs.erase(diffs.find(a[k + 1] - a[k]));
				
				removed.push_back(a[k + 1] - a[k]);
			}
			
			if (k > 0) {
				diffs.erase(diffs.find(a[k] - a[k - 1]));
				
				removed.push_back(a[k] - a[k - 1]);
			}
			
			if (k + 1 < a.size() && k > 0) {
				diffs.insert(a[k + 1] - a[k - 1]);
				
				added.push_back(a[k + 1] - a[k - 1]);
			}
			
			if (_safe(diffs)) {
				safe++;
				break;
			}
			
			for (int& x : removed) {
				diffs.insert(x);
			}
			
			for (int& x : added) {
				diffs.erase(diffs.find(x));
			}

		}
	}
	
	cout << "safe: " << safe << endl;

	return 0;
}
