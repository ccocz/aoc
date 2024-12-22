#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <map>

#define mp(x, y) make_pair(x, y)
#define ll long long
#define pii pair<int, int>

using namespace std;

char numpad[4][3] = {
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'},
    {'X', '0', 'A'}
};
char dirpad[2][3] = {
    {'X', '^', 'A'},
    {'<', 'v', '>'}
};

map<char, pii> jan = {
  {'7', mp(0, 0)},
  {'8', mp(0, 1)},
  {'9', mp(0, 2)},

  {'4', mp(1, 0)},
  {'5', mp(1, 1)},
  {'6', mp(1, 2)},

  {'1', mp(2, 0)},
  {'2', mp(2, 1)},
  {'3', mp(2, 2)},

  {'X', mp(3, 0)},
  {'0', mp(3, 1)},
  {'A', mp(3, 2)}
};

map<char, pii> janjan = {
  {'X', mp(0, 0)},
  {'^', mp(0, 1)},
  {'A', mp(0, 2)},

  {'<', mp(1, 0)},
  {'v', mp(1, 1)},
  {'>', mp(1, 2)}
};

int tox[] = {1, -1, 0, 0};
int toy[] = {0, 0, 1, -1};
char dir[] = {'v', '^', '>', '<'};

void goNum(pii start,
           pii end,
           string now,
           vector<string>& ways,
           set<char>& vis,
           char pad[][3],
           int lim) {
  if (start == end) {
    ways.push_back(now);
    return;
  }

  if (now.size() > lim) {
    return;
  }

  vis.insert(pad[start.first][start.second]);

  for (int i = 0; i < 4; i++) {
    int nx = start.first + tox[i];
    int ny = start.second + toy[i];

    if (nx >= 0 && nx < 4 && ny >= 0 && ny < 3 && pad[nx][ny] != 'X' && vis.find(pad[nx][ny]) == vis.end()) {
      goNum(mp(nx, ny), end, now + dir[i], ways, vis, pad, lim);
    }
  }

  vis.erase(pad[start.first][start.second]);
}

int dist(pii start, pii end) {
  return abs(end.first - start.first) + abs(end.second - start.second);
}

vector<string> makeNumHelper(string s, map<char, pii> m, char pad[][3]) {
  vector<string> mals;
  mals.push_back("");

  s = "A" + s; // yolo

  for (int i = 0; i < s.size() - 1; i++) {
    auto pos1 = m[s[i]];
    auto pos2 = m[s[i + 1]];

    vector<string> ways;
    set<char> vis;
    goNum(pos1, pos2, "", ways, vis, pad,  dist(pos1, pos2));

    vector<string> newmals;

    for (string& ss: ways) {
        for (string ss2: mals) {
          newmals.push_back(ss2 + ss + "A");
        }
    }

    mals = newmals;
  }

  return mals;
}

vector<string> partition(string s) {
  string ss = "";

  int i = 0;

  vector<string> malak;

  while (i < s.size()) {
    ss += s[i];
    if (s[i] == 'A') {
      malak.push_back(ss);
      ss = "";
    }
    i++;
  }

  return malak;
}

ll solvee(string s,
          int lvl,
          map<pair<string, int>, ll>& dp) {
  if (lvl == 0) {
    return s.size();
  }

  if (dp.find(mp(s, lvl)) != dp.end()) {
    return dp[mp(s, lvl)];
  }

  auto prt = partition(s);

  ll ans = 0;
  for (auto& ss: prt) {
    auto mn = makeNumHelper(ss, janjan, dirpad);
    ll mini = LLONG_MAX;
    for (string& nn : mn) {
      ll mall = solvee(nn, lvl - 1, dp);

      if (mall < mini) {
        mini = mall;
      }
    }
    ans += mini;
  }

  return dp[mp(s, lvl)] = ans;
}

int main() {
  vector<string> v(5);

  long long ans = 0;

  for (string &s : v) {
    cin >> s;

    auto mala = makeNumHelper(s, jan, numpad);

    ll mini = LLONG_MAX;

    for (string mall : mala) {
      map<pair<string, int>, ll> dp;
      ll mm = solvee(mall, 25, dp);

      if (mm < mini) mini = mm;
    }

    ans += 1LL * stoi(s.substr(0, s.length() - 1)) * mini;
  }

  cout << "ans: " << ans << endl;
  return 0;
}
