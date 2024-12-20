#include <iostream>
#include <vector>
#include <map>

#define mp(x, y) make_pair(x, y)
#define ll long long

using namespace std;

int tox[] = {1, -1, 0, 0};
int toy[] = {0, 0, 1, -1};

void go(int x,
        int y,
        vector<string>& v,
        vector<vector<int> >& dist) {
  if (v[x][y] == 'E') {
    return;
  }
  for (int i = 0; i < 4; i++) {
    int nx = x + tox[i];
    int ny = y + toy[i];

    if (nx >= 0 && nx < v.size() && ny >= 0 && ny < v[x].size() && dist[nx][ny] == -1 && v[nx][ny] != '#') {
      dist[nx][ny] = dist[x][y] + 1;
      go(nx, ny, v, dist);
    }
  }
}

int get_dist(pair<int, int> p1, pair<int, int> p2) {
  return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main() {
  vector<string> v;
  string s;

  while (cin >> s) {
    v.push_back(s);
  }

  vector<vector<int> > dist(v.size(), vector<int>(v[0].size(), -1));
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[0].size(); j++) {
      if (v[i][j] == 'S') {
        dist[i][j] = 0;
        go(i, j, v, dist);
      }
    }
  }

  vector<pair<int, pair<int, int> > > jal;

  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[0].size(); j++) {
      if (dist[i][j] != -1) {
        jal.push_back(mp(dist[i][j], mp(i, j)));
      }
    }
  }

  sort(jal.begin(), jal.end());
  map<int, int> san;

  for (int i = 0; i < jal.size(); i++) {
    for (int j = i + 1; j < jal.size(); j++) {
      int dii = get_dist(jal[i].second, jal[j].second);
      if (dii <= 20) {
        int save = jal[j].first - jal[i].first - dii;

        if (!save) continue;

        if (san.find(save) == san.end()) {
          san[save] = 0;
        }

        san[save]++;
      }
    }
  }

  int ans = 0;
  for (auto &mal: san) {
    if (mal.first >= 100) ans += mal.second;
  }

  cout << "ans: " << ans << endl;

  return 0;
}
