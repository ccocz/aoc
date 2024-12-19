#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <set>

#define mp(x, y) make_pair(x, y)

using namespace std;

typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> node;

// LRUD
// 0123

int tox[] = {0, 0, -1, 1};
int toy[] = {-1, 1, 0, 0};

int tox_rev[] = {0, 0, 1, -1};
int toy_rev[] = {1, -1, 0, 0};

void find(vector<string>& v) {
    pii stra, endd;
    map<node, int> dist;

    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (v[i][j] == 'S') {
                stra = mp(i, j);
            } else if (v[i][j] == 'E') {
                endd = mp(i, j);
            }

            for (int k = 0; k < 4; k++) {
                dist[mp(mp(i, j), k)] = INT_MAX / 2;
            }
        }
    }

    priority_queue<pair<int, node>, vector<pair<int, node> >, greater<pair<int, node> > > pq;

    for (int k = 0; k < 4; k++) {
        dist[mp(stra, k)] = 0;
    }

    pq.push(mp(0, mp(stra, 1)));

    while (!pq.empty()) {
        node u = pq.top().second;
        pq.pop();

        int x = u.first.first;
        int y = u.first.second;

        for (int i = 0; i < 4; i++) {
            int nx = x + tox[i];
            int ny = y + toy[i];

            int jul = i == u.second ? 1 : 1001;

            if (nx >= 0 && nx < v.size() && ny >= 0 && ny < v[0].size() && v[nx][ny] != '#') {
                if (dist[mp(mp(nx, ny), i)] > dist[mp(mp(x, y), u.second)] + jul) {
                    dist[mp(mp(nx, ny), i)] = dist[mp(mp(x, y), u.second)] + jul;
                    pq.push(mp(dist[mp(mp(nx, ny), i)], mp(mp(nx, ny), i)));
                }
            }
        }
    }

    int kk = 0;
    for (int k = 1; k < 4; k++) {
        if (dist[mp(endd, k)] < dist[mp(endd, kk)]) {
            kk = k;
        }
    }

    stack<node> stt;
    for (int k = 0; k < 4; k++) {
        if (dist[mp(endd, k)] == dist[mp(endd, kk)]) {
            stt.push(mp(endd, k));
        }
    }

    set<pii> saljan;

    while (!stt.empty()) {
        auto gul = stt.top();
        auto nw = gul.first;
        stt.pop();

        saljan.insert(nw);

        if (nw == stra) continue;

        int kk = 0;
        for (int k = 1; k < 4; k++) {
            if (dist[mp(nw, k)] + 1000 * (k != gul.second) < (dist[mp(nw, kk)] + 1000 * (kk != gul.second))) {
                kk = k;
            }
        }

        for (int k = 0; k < 4; k++) {
            if (dist[mp(nw, k)] + 1000 * (k != gul.second) == (dist[mp(nw, kk)] + 1000 * (kk != gul.second))) {
                stt.push(mp(mp(nw.first + tox_rev[k], nw.second + toy_rev[k]), k));
            }
        }
    }

    int ans1 = INT_MAX;
    for (int k = 0; k < 4; k++) {
        ans1 = min(ans1, dist[mp(endd, k)]);
    }

    cout << "ans: " << saljan.size() << endl;
}

int main() {
    vector<string> v;

    string s;

    while (cin >> s) {
        v.push_back(s);
        cout << s << endl;
    }

    find(v);

    return 0;
}
