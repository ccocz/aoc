#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define mp(x, y) make_pair(x, y)
#define ll long long

using namespace std;

pair< bool, vector<int> > convert(vector<string>& v) {
  vector<int> res;
  if (v[0][0] == '#') {
    for (int j = 0; j < v[0].size(); j++) {
      int i = 1, resa = 0;

      while (i < v.size() && v[i][j] == '#') {
        resa++;
        i++;
      }

      res.push_back(resa);
    }

    return mp(true, res);
  } else {
    for (int j = 0; j < v[0].size(); j++) {
      int i = v.size() - 2, resa = 0;

      while (i >= 0 && v[i][j] == '#') {
        resa++;
        i--;
      }
      res.push_back(resa);
    }

    return mp(false, res);
  }
}

int main() {
  string s;

  vector<string> mal;

  vector< vector<int> > locks, keys;

  while (getline(cin, s)) {
    if (s.empty()) {
      const auto& tip = convert(mal);

      if (tip.first) {
        locks.push_back(tip.second);
      } else {
        keys.push_back(tip.second);
      }

      mal.clear();
    } else {
      mal.push_back(s);
    }
  }

  int ans = 0;
  for (auto& t : locks) {
    for (auto& v : keys) {
      bool ok = true;
      for (int i = 0; i < v.size() && ok; i++) {
        ok &= (v[i] + t[i]) <= 5;
      }

      ans += ok;
    }
  }

  cout << "ans: " << ans << endl;
  return 0;
}
