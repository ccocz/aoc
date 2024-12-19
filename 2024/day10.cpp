#include <iostream>
#include <set>
#include <vector>

using namespace std;

int tox[] = {1, -1, 0, 0};
int toy[] = {0, 0, 1, -1};

int go(int x, int y, int now, vector<string>& v, set<pair<int, int> >& mal) {
  if (now == 9) {
    //mal.insert(make_pair(x, y));
    return 1;
  }

  int sum = 0;

  for (int i = 0; i < 4; i++) {
    int nx = x + tox[i];
    int ny = y + toy[i];

    if (nx >= 0 && nx < v.size() && ny >= 0 && ny < v[0].size() && v[nx][ny] - '0' == now + 1) {
      sum += go(nx, ny, now + 1, v, mal);
    }
  }

  return sum;
}

int main() {
  int n = 50;
  vector<string> v(n);
  for (string& s : v) {
    cin >> s;
  }

  int sum = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < v[i].size(); j++) {
      if (v[i][j] == '0') {
        set<pair<int, int> > mal;
        sum += go(i, j, 0, v, mal);;

      }
    }
  }

  cout << "sum: " << sum << endl;
  return 0;
}