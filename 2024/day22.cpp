#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define mp(x, y) make_pair(x, y)
#define ll long long

using namespace std;

int main() {
  vector<ll> v;
  ll n;

  const int MOD = 16777216;
  while (cin >> n) {
    v.push_back(n);
  }

  ll ans1 = 0;

  vector<vector<ll> > prices, diffs;

  for (ll& x : v) {
    n = 2000;

    vector<ll> prc, dff;

    prc.push_back(x % 10);
    dff.push_back(0);

    while (n--) {
      x = ((x * 64) xor x) % MOD;
      x = ((x / 32) xor x) % MOD;
      x = ((x * 2048) xor x) % MOD;

      prc.push_back(x % 10);

      dff.push_back((x % 10) - prc[prc.size() - 2]);
    }

    prices.push_back(prc);
    diffs.push_back(dff);
    ans1 += x;
  }

  unordered_map<string, int> pre;

  for (int i = 0; i < v.size(); i++) {
    unordered_set<string> vis;

    for (int j = 1; j + 3 < diffs[i].size(); j++) {
      string mala = to_string(diffs[i][j])
                    + to_string(diffs[i][j + 1])
                    + to_string(diffs[i][j + 2])
                    + to_string(diffs[i][j + 3]);

      if (vis.find(mala) == vis.end()) {
        pre[mala] += prices[i][j + 3];
        vis.insert(mala);
      }
    }
  }

  int ans2 = 0;

  for (auto x: pre) {
    if (x.second > ans2) ans2 = x.second;
  }

  cout << "ans1: " << ans1 << endl;
  cout << "ans2: " << ans2 << endl;

  return 0;
}
