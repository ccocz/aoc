#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

vector<vector<bool> >v(100, vector<bool>(100, false));

bool cmp(int a, int b) {
  return v[a][b];
}

int main() {
  int n = 1176;

  for (int i = 0; i < n; i++) {
    int a, b;
    char c;
    cin >> a >> c >> b;
    v[a][b] = true;
  }

  int sum = 0;

  string line;
  while (getline(cin, line)) {
    istringstream iss(line);
    int num;
    char c;
    vector<int> mal;
    while (iss >> num) {
      mal.push_back(num);
      iss >> c;
    }

    if (mal.size() == 0) {
      continue;
    }

    bool ok = true;

    for (int i = 0; i < mal.size(); i++) {
      for (int j = i + 1; j + 1 < mal.size(); j++) {
        if (!v[mal[i]][mal[j]]) {
          ok = false;
        }
      }
    }

    if (ok) {
      // sum += mal[mal.size() / 2];
    } else {
      sort(mal.begin(), mal.end(), cmp);
      sum += mal[mal.size() / 2];
    }
  }

  cout << sum << endl;

  return 0;
}
