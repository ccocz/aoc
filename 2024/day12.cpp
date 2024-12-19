#include <iostream>
#include <set>
#include <vector>

using namespace std;

int tox[] = {1, -1, 0, 0};
int toy[] = {0, 0, 1, -1};
int jul[][2] = {
  {2, 3},
  {2, 3},
  {0, 1},
  {0, 1}
};

// 0123
// DURL

set<pair<int, int> > perims;

void go(int x,
        int y,
        vector<string>&v,
        vector<vector<bool> >&vis,
        vector<vector<vector<bool> > >&trac_row, 
        vector<vector<vector<bool> > >&trac_col,
        int& area,
        int& perim,
        char now) {
  if (vis[x][y]) {
    return;
  }

  vis[x][y] = true;

  area++;

  for (int i = 0; i < 4; i++) {
    int nx = x + tox[i];
    int ny = y + toy[i];

    if (!(nx >= 0 && nx < v.size() && ny >= 0 && ny < v[0].size() && v[nx][ny] == now)) {
      if (i < 2) {
        trac_row[x][y][i] = true;
      } else {
        trac_col[x][y][i - 2] = true;
      }

    } else {
      go(nx, ny, v, vis, trac_row, trac_col, area, perim, now);
    }
  }

}

int main() {
  int n = 140;

  vector<string> v(n);
  vector<vector<bool> > vis;
  vector<vector<vector<bool> > > trac_row;
  vector<vector<vector<bool> > > trac_col;

  vector<int> mal;

  mal = vector<int>();

  for (string& s : v) {
    cin >> s;

    vis.push_back(vector<bool>(s.size(), false));
  }

  long long ans = 0;

  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++) {
      if (!vis[i][j]) {
        int area = 0, perim = 0;

        trac_row = vector<vector<vector<bool> > >(v.size(), vector<vector<bool> >(v[0].size(), vector<bool>(2, false)));
        trac_col = vector<vector<vector<bool> > >(v[0].size(), vector<vector<bool> >(v.size(), vector<bool>(2, false)));
        
        go(i, j, v, vis, trac_row, trac_col, area, perim, v[i][j]);
        
        perim = 0;
        
        for (int k = 0; k < v.size(); k++) {
          bool mal = false;
          for (int m = 0; m < v[i].size(); m++) {
            if (trac_row[k][m][0]) {
              if (!mal) {
                perim++;
              }
              mal = true;
            } else {
              mal = false;
            }
          }
          mal = false;
          for (int m = 0; m < v[i].size(); m++) {
            if (trac_row[k][m][1]) {
              if (!mal) {
                perim++;
              }
              mal = true;
            } else {
              mal = false;
            }
          }

          mal = false;
          for (int m = 0; m < v[i].size(); m++) {
            if (trac_col[m][k][0]) {
              if (!mal) {
                perim++;
              }
              mal = true;
            } else {
              mal = false;
            }
          }
          mal = false;
          for (int m = 0; m < v[i].size(); m++) {
            if (trac_col[m][k][1]) {
              if (!mal) {
                perim++;
              }
              mal = true;
            } else {
              mal = false;
            }
          }
        }
        ans += 1LL * area * perim;
      }
    }
  }

  cout << "ans: " << ans << endl;


  return 0;
}