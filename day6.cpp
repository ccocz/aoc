#include <iostream>
#include <vector>
#include <map>
using namespace std;

// ^>v<
// 0123

int tox[] = {-1, 0, 1, 0};
int toy[] = {0, 1, 0, -1};

int ch[] = {1, 2, 3, 0};

int N = 130;
vector<string> va(N);
vector<string> ma;

bool vis[135][135][5];

void cnt(int i, int j, vector<string>& v, int dir) {
  v[i][j] = 'X';

  int n = v.size();
  int m = v[i].size();

  int nx = i + tox[dir];
  int ny = j + toy[dir];

  if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
    return;
  }

  if (v[nx][ny] == '#') {
    dir = ch[dir];
    nx = i + tox[dir];
    ny = j + toy[dir];

    if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
      return;
    }

    return cnt(nx, ny, v, dir);
  } else {
    return cnt(nx, ny, v, dir);
  }
}

bool stuck(int i, int j, vector<string>& v, int dir) {
  if (vis[i][j][dir]) {
    return true;
  }

  vis[i][j][dir] = true;

  int n = v.size();
  int m = v[i].size();

  int nx = i + tox[dir];
  int ny = j + toy[dir];

  if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
    return false;
  }

  if (v[nx][ny] == '#') {
    dir = ch[dir];
    return stuck(i, j, v, dir);
  } else {
    return stuck(nx, ny, v, dir);
  }
}

int main() {

  for (string &s : va) {
    cin >> s;
  }

  pair<int, int> st;

  for (int i = 0; i < va.size(); i++) {
    ma.push_back(va[i]);
    for (int j = 0; j < va[i].size(); j++) {
      if (va[i][j] == '^') {
        st = make_pair(i, j);
      }
    }
  }

  cnt(st.first, st.second, ma, 0);

  int sum = 0;

  for (int i = 0; i < va.size(); i++) {
    for (int j = 0; j < va[i].size(); j++) {
      if (va[i][j] == '.' && ma[i][j] == 'X') {
        va[i][j] = '#';
        memset(vis, 0, sizeof(vis));
        if (stuck(st.first, st.second, va, 0)) {
          sum++;
        }
        va[i][j] = '.';
      }
    }
  }

  cout << sum << endl;
  return 0;
}
