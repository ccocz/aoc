#include <iostream>
#include <map>
#include <set>
#include <vector>

#define mp make_pair

using namespace std;

typedef pair<pair<int, int>, pair<int, int> > mal;

int main() {
  string s;

  vector<mal> v;

  while (getline(cin, s)) {
    int sx = 0, sy = 0, vx = 0, vy = 0;
    int k = 2;

    int sxn = 1, syn = 1, vxn = 1, vyn = 1;

    if (s[k] == '-') sxn = -1, k++;

    for (k = 2; s[k] != ','; k++) {
      sx *= 10;
      sx += s[k] - '0';
    }
    k++;

    if (s[k] == '-') syn = -1, k++;

    for (; s[k] != ' '; k++) {
      sy *= 10;
      sy += s[k] - '0';
    }

    for (; s[k] != '='; k++) {};
    k++;

    if (s[k] == '-') vxn = -1, k++;
    for (; s[k] != ','; k++) {
      vx *= 10;
      vx += s[k] - '0';
    }
    k++;

    if (s[k] == '-') vyn = -1, k++;
    for (; k < s.length(); k++) {
      vy *= 10;
      vy += s[k] - '0';
    }

    sx *= sxn;
    sy *= syn;
    vx *= vxn;
    vy *= vyn;

    v.push_back(mp(mp(sy, sx), mp(vx, vy)));
  }

  int n = 103, m = 101;

  for (int i = 1; ; i++) {
    vector<mal> nxt;
    for (auto& sal : v) {
      mal nw = mp(mp(sal.first.first + sal.second.second, sal.first.second + sal.second.first), mp(sal.second.first, sal.second.second));
      
      while (nw.first.first < 0) nw.first.first += n;
      while (nw.first.second < 0) nw.first.second += m;

      while (nw.first.first >= n) nw.first.first -= n;
      while (nw.first.second >= m) nw.first.second -= m;
      
      nxt.push_back(nw);
    }

    v = nxt;

    vector<vector<int> > jj(n, vector<int>(m, 0));
  
    for (auto& m: v) {
      jj[m.first.first][m.first.second]++;
    }

    bool ok = false;
    for (int ii = 0; ii < n; ii++) {
      string mal = "";
      for (int jjj = 0; jjj < m; jjj++) {
        mal += (jj[ii][jjj] > 0 ? '*' : '.');
      }
      if (mal.find("*****************") != string::npos) {
        ok = true;
      }
    }

    if (ok) {
      cout << "i = " << i << endl;
      for (int ii = 0; ii < n; ii++) {
        for (int jjj = 0; jjj < m; jjj++) {
          cout << (jj[ii][jjj] > 0 ? '*' : '.');
        }
        cout << endl;
      }
    }
  }

  vector<vector<int> > jj(n, vector<int>(m, 0));
  vector<int> quad(4, 0);

  for (auto& m: v) {
    cout << m.first.second << ' ' << m.first.first << endl;
    jj[m.first.first][m.first.second]++;
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i == n / 2 || j == m / 2) continue;

      if (i < n / 2 && j < m / 2) quad[0] += jj[i][j];
      if (i < n / 2 && j > m / 2) quad[1] += jj[i][j];

      if (i > n / 2 && j < m / 2) quad[2] += jj[i][j];
      if (i > n / 2 && j > m / 2) quad[3] += jj[i][j];
    }
  }

  cout << quad[0] << ' ' << quad[1] << ' ' << quad[2] << ' ' << quad[3] << endl;

  cout << 1LL * quad[0] * quad[1] * quad[2] * quad[3] << endl;

  return 0;
}