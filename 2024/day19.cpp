#include <iostream>
#include <vector>
#include <map>

#define mp(x, y) make_pair(x, y)
#define ll long long

using namespace std;

ll can_make(string s,
            int i,
            vector<string>& patterns,
            map<string, ll>& memo) {
  if (i >= s.length()) {
    return 1;
  }

  string suff = s.substr(i);

  if (memo.find(suff) != memo.end()) {
    return memo[suff];
  }

  ll ans = 0;

  for (string& mal: patterns) {
    if (s.substr(i, mal.length()) == mal) {
      ans += can_make(s, i + mal.length(), patterns, memo);
    }
  }

  return memo[suff] = ans;
}

int main() {
  string mal = "";

  getline(cin, mal);

  vector<string> patterns;

  string pattern = "";
  int i = 0;
  while (i < mal.length()) {
    if (mal[i] == ',') {
      patterns.push_back(pattern);
      pattern = "";
      i += 2;
    }

    pattern += mal[i++];
  }

  patterns.push_back(pattern);

  vector<string> designs;

  string s;

  ll ans = 0;
  ll ans1 = 0;

  while (cin >> s) {
    designs.push_back(s);
    map<string, ll> memo;

    ll mal = can_make(s, 0, patterns, memo);
    ans += mal;
    ans1 += !mal;
  }

  cout << "ans: " << ans << endl;

  return 0;
}
