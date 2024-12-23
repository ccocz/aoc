#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define mp(x, y) make_pair(x, y)
#define ll long long

using namespace std;

void bron(unordered_set<string>& r,
          unordered_set<string>& p,
          unordered_set<string>& x,
          unordered_map<string, unordered_set<string> >& edge,
          unordered_set<string>& maxi) {

  if (p.empty() && x.empty()) {
    if (r.size() > maxi.size()) {
      maxi = r;
    }
    return;
  }

  unordered_set<string> phelp = p;

  for (const string& v: phelp) {
    unordered_set<string> rnxt = r;
    rnxt.insert(v);

    unordered_set<string> pnxt;
    for (const string& u: p) {
      if (edge[v].count(u)) {
        pnxt.insert(u);
      }
    }

    unordered_set<string> xnext;
    for (const string& u: x) {
      if (edge[v].count(u)) {
        xnext.insert(u);
      }
    }

    bron(rnxt, pnxt, xnext, edge, maxi);

    p.erase(v);
    x.insert(v);
  }
}

void part_1(vector<string>& mal, unordered_map<string, unordered_set<string> >& edge) {
  int ans = 0;

  for (int i = 0; i < mal.size(); i++) {
    for (int j = i + 1; j < mal.size(); j++) {
      for (int k = j + 1; k < mal.size(); k++) {
        string a = mal[i], b = mal[j], c = mal[k];
        if (a[0] != 't' && b[0] != 't' && c[0] != 't') continue;

        ans += edge[a].count(b)
               && edge[a].count(c)
               && edge[b].count(c);
      }
    }
  }

  cout << "ans: " << ans << endl;
}

int main() {
  string s;

  unordered_map<string, unordered_set<string> > edge;
  unordered_set<string> all;

  while (cin >> s) {
    string from = s.substr(0, 2), to = s.substr(3, 2);

    edge[from].insert(to);
    edge[to].insert(from);

    all.insert(from);
    all.insert(to);
  }

  unordered_set<string> r, p(all.begin(), all.end()), x;

  unordered_set<string> maxi;
  bron(r, p, x, edge, maxi);

  vector<string> maa(maxi.begin(), maxi.end());
  sort(maa.begin(), maa.end());

  vector<string> mall(all.begin(), all.end());

  string ans = "";
  for (int i = 0; i < maa.size(); i++) {
    ans += maa[i];

    if (i != maa.size() - 1) {
      ans += ",";
    }
  }
  cout << ans << endl;

  return 0;
}
