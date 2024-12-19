#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {
    const int N = 50;
    vector<string> v(N);

    for (string& s : v) {
        cin >> s;
    }

    map<char, vector<pair<int, int> > > maps;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < v[i].length(); j++) {
            if (v[i][j] != '.') {
                maps[v[i][j]].push_back(make_pair(i, j));
            }
        }
    }

    set<pair<int, int> > sala;

    for (auto sal : maps) {
        auto jal = sal.second;
        for (int k = 0; k < jal.size(); k++) {
            for (int m = k + 1; m < jal.size(); m++) {

                int jor = 0;

                while (true) {
                    pair<int, int> fr = make_pair(jal[k].first + jor * (jal[k].first - jal[m].first), jal[k].second + jor * (jal[k].second - jal[m].second));
                    pair<int, int> sc = make_pair(jal[m].first + jor * (jal[m].first - jal[k].first), jal[m].second + jor * (jal[m].second - jal[k].second));

                    bool one = false;

                    if (fr.first >= 0 && fr.first < N && fr.second >= 0 && fr.second < N) {
                        sala.insert(fr);
                        v[fr.first][fr.second] = '#';
                        one = true;
                    }

                    if (sc.first >= 0 && sc.first < N && sc.second >= 0 && sc.second < N) {
                        sala.insert(sc);
                        v[sc.first][sc.second] = '#';
                        one = true;
                    }

                    if (!one) {
                        break;
                    }

                    jor++;
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        cout << v[i] << endl;
    }

    cout << sala.size() << endl;

    return 0;
}
