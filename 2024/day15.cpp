#include <iostream>
#include <map>
#include <set>
#include <vector>

#define mp make_pair

using namespace std;

int go(int x, int y, vector<string>&v, string& mov) {
  
  for (int pos = 0; pos < mov.length(); pos++) {
    if (mov[pos] == '>') {
    int k = y;

    while (k + 1 < v[x].length() && (v[x][k + 1] == '[' || v[x][k + 1] == ']')) {
      k++;
    }

    int mal = y;

    if (k + 1 < v[x].length() && v[x][k + 1] == '.') {
      mal = y + 1;
      for (int m = k; m >= y; m--) {
        swap(v[x][m], v[x][m + 1]);
      }
    }

    y = mal;
  } else if (mov[pos] == '<') {
    int k = y;

    while (k - 1 >= 0 && (v[x][k - 1] == '[' || v[x][k - 1] == ']')) {
      k--;
    }

    int mal = y;

    if (k - 1 >= 0 && v[x][k - 1] == '.') {
      mal = y - 1;
      for (int m = k; m <= y; m++) {
        swap(v[x][m], v[x][m - 1]);
      }
    }

    y = mal;

  } else if (mov[pos] == '^') {
    vector<set<pair<int, int> > > levels;
    
    set<pair<int, int> > sak;
    sak.insert(mp(x, y));
    levels.push_back(sak);
    bool blocked = false;

    while (true) {
      bool sal = true, all_clean = true;
      for (auto& jan : levels.back()) {
        if (jan.first - 1 >= 0 && v[jan.first - 1][jan.second] == '#') {
          sal = false;
          all_clean = false;
        }

        if (jan.first - 1 >= 0 && v[jan.first - 1][jan.second] != '.') {
          all_clean = false;
        }
      }

      if (!sal || all_clean) {
        if (!sal) blocked = true;
        break;
      }

      set<pair<int, int> > nxt_level;

      for (auto& jan : levels.back()) {
        if (jan.first - 1 >= 0 && v[jan.first - 1][jan.second] == '[') {
          nxt_level.insert(mp(jan.first - 1, jan.second));
          nxt_level.insert(mp(jan.first - 1, jan.second + 1));
        }
        if (jan.first - 1 >= 0 && v[jan.first - 1][jan.second] == ']') {
          nxt_level.insert(mp(jan.first - 1, jan.second));
          nxt_level.insert(mp(jan.first - 1, jan.second - 1));
        }
      }

      if (!nxt_level.empty()) levels.push_back(nxt_level);
    }

    if (blocked) {
      continue;
    }

    for (int i = levels.size() - 1; i >= 0; i--) {
      for (auto& jan : levels[i]) {
        swap(v[jan.first - 1][jan.second], v[jan.first][jan.second]);
      }
    }
    x = x - 1;

  } else if (mov[pos] == 'v') {

    vector<set<pair<int, int > > > levels;
    
    set<pair<int, int> > sak;
    sak.insert(mp(x, y));
    levels.push_back(sak);
    bool blocked = false;
    bool allclean = true;

    while (true) {
      bool sal = true, all_clean = true;
      
      for (auto& jan : levels.back()) {
        if (jan.first + 1 < v.size() && v[jan.first + 1][jan.second] == '#') {
          sal = false;
          all_clean = false;
          allclean = false;
        }

        if (jan.first + 1 < v.size() && v[jan.first + 1][jan.second] != '.') {
          all_clean = false;
          allclean = false;
        }
      }

      if (!sal || all_clean) {
        if (!sal) blocked = true;
        break;
      }

      set<pair<int, int> > nxt_level;

      for (auto& jan : levels.back()) {
        if (jan.first + 1 < v.size() && v[jan.first + 1][jan.second] == '[') {
          nxt_level.insert(mp(jan.first + 1, jan.second));
          nxt_level.insert(mp(jan.first + 1, jan.second + 1));
        }
        if (jan.first + 1 < v.size() && v[jan.first + 1][jan.second] == ']') {
          nxt_level.insert(mp(jan.first + 1, jan.second));
          nxt_level.insert(mp(jan.first + 1, jan.second - 1));
        }
      }

      if (!nxt_level.empty()) levels.push_back(nxt_level);
    }

    if (blocked) {
      continue;
    }

    for (int i = levels.size() - 1; i >= 0; i--) {
      for (auto& jan : levels[i]) {
        swap(v[jan.first + 1][jan.second], v[jan.first][jan.second]);
      }
    }

    x = x + 1;

  } else {
    cout << "Unexpected move!";
    exit(-1);
  }
  }

  long long ans = 0;

  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].length(); j++) {
      if (v[i][j] == '[') {
        ans += 100 * i + j;
      }
    }
  }

  cout << "ans: " << ans << endl;
}

int main() {
  const int N = 50;
  vector<string> v;

  pair<int, int> st;

  string s;
  for (int i = 0; i < N; i++) {
    cin >> s;

    string mal = "";
    for (char& c : s) {
      if (c == '#') {
        mal += "##";
      } else if (c == 'O') {
        mal += "[]";
      } else if (c == '.') {
        mal += "..";
      } else {
        mal += "@.";
      }
    }

    v.push_back(mal);
  }

  string dar, sam = "";

  getline(cin, dar);

  while (getline(cin, dar)) {
    sam += dar;
  }

  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++) {
      if (v[i][j] == '@') {
        st = mp(i, j);
        break;
      }
    }
  }

  go(st.first, st.second, v, sam);
  return 0;
}