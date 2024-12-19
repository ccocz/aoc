#include <iostream>
#include <vector>
#include <queue>

#define mp(x, y) make_pair(x, y)
#define ll long long

using namespace std;

int tox[] = {1, -1, 0, 0};
int toy[] = {0, 0, 1, -1};

int main() {
  int a, b;
  char c;

  const int N = 71;
  vector<vector<char> > v(N, vector<char>(N, '.'));
  vector<pair<int, int> > blocks;

  while (cin >> a >> c >> b) {
    blocks.push_back(mp(b, a));
  }

  for (auto block : blocks) {
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));

    v[block.first][block.second] = '#';

    vector<vector<int> > dist(N, vector<int>(N, -1));

    dist[0][0] = 0;

    while (!q.empty()) {
      pair<int, int> p = q.front();
      q.pop();

      for (int i = 0; i < 4; i++) {
        int nx = p.first + tox[i], ny = p.second + toy[i];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N && v[nx][ny] != '#' && dist[nx][ny] == -1) {
          dist[nx][ny] = dist[p.first][p.second] + 1;
          q.push(mp(nx, ny));
        }
      }
    }

    if (dist[70][70] == -1) {
      cout << block.first << "x" << block.second << endl;
      break;
    }
  }

  return 0;
}
