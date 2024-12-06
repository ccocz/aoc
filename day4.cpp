#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

int cnt(int x, int y, vector<string>& v) {
    int n = v.size(), m = v[0].size();
    int total = 0;

    total += (x + 3 < n && v[x + 1][y] == 'M' && v[x + 2][y] == 'A' && v[x + 3][y] == 'S');
    total += (y + 3 < m && v[x][y + 1] == 'M' && v[x][y + 2] == 'A' && v[x][y + 3] == 'S');
    total += (x + 3 < m && y + 3 < m && v[x + 1][y + 1] == 'M' && v[x + 2][y + 2] == 'A' && v[x + 3][y + 3] == 'S');

    total += (x - 3 >= 0 && y + 3 < m && v[x - 1][y + 1] == 'M' && v[x - 2][y + 2] == 'A' && v[x - 3][y + 3] == 'S');

    total += (x - 3 >= 0 && v[x - 1][y] == 'M' && v[x - 2][y] == 'A' && v[x - 3][y] == 'S');
    total += (y - 3 >= 0 && v[x][y - 1] == 'M' && v[x][y - 2] == 'A' && v[x][y - 3] == 'S');
    total += (x - 3 >= 0 && y - 3 >= 0 && v[x - 1][y - 1] == 'M' && v[x - 2][y - 2] == 'A' && v[x - 3][y - 3] == 'S');

    total += (x + 3 < n && y - 3 >= 0 && v[x + 1][y - 1] == 'M' && v[x + 2][y - 2] == 'A' && v[x + 3][y - 3] == 'S');
    return total;
}

int cnt2(int x, int y, vector<string>& v) {
    int n = v.size(), m = v[0].size();

    return (x + 1 < n && x - 1 >= 0 && y + 1 < m && y - 1 >= 0
        && ((v[x + 1][y + 1] == 'M' && v[x - 1][y - 1] == 'S') || (v[x + 1][y + 1] == 'S' && v[x - 1][y - 1] == 'M'))
        && ((v[x + 1][y - 1] == 'M' && v[x - 1][y + 1] == 'S') || (v[x + 1][y - 1] == 'S' && v[x - 1][y + 1] == 'M')));
}


int main() {
    int n = 140;
    vector<string> v(n);

    for (string& s : v) {
        cin >> s;
    }

    int xmas = 0;

    for (int i  = 0; i < n; i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (v[i][j] == 'A') {
                //xmas += cnt(i, j, v);
                xmas += cnt2(i, j, v);
            }
        }
    }

    cout  << xmas << endl;

    return 0;
}
