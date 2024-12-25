#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <sstream>
#include <string>
#include <stack>

#define mp(x, y) make_pair(x, y)
#define ll long long

using namespace std;

ll get_ans(set< vector<string> >& oprs,
           unordered_map<string, int> wires) {

  vector< vector<string> > mal(oprs.begin(), oprs.end());
  while (!mal.empty()) {
    set<vector<string> > rem;

    for (auto& op: mal) {
      if (!wires.count(op[0]) || !wires.count(op[2])) continue;

      if (op[1] == "AND") {
        wires[op[3]] = wires[op[0]] & wires[op[2]];
      } else if (op[1] == "OR") {
        wires[op[3]] = wires[op[0]] | wires[op[2]];
      } else {
        wires[op[3]] = wires[op[0]] xor wires[op[2]];
      }

      rem.insert(op);
    }

    if (rem.empty()) {
      return -1;
    }

    vector< vector<string> > nxt;

    for (auto moo : mal) {
      if (!rem.count(moo)) {
        nxt.push_back(moo);
      }
    }
    mal = nxt;
  }

  ll maljan = 0;
  ll xx = 0, yy = 0;

  for (auto& mal : wires) {
    if (mal.first[0] == 'z') {
      int bit = stoi(mal.first.substr(1));
      maljan |= mal.second * 1ULL << bit;
    }

    if (mal.first[0] == 'x') {
      int bit = stoi(mal.first.substr(1));
      xx |= mal.second * 1ULL << bit;
    }

    if (mal.first[0] == 'y') {
      int bit = stoi(mal.first.substr(1));
      yy |= mal.second * 1ULL << bit;
    }
  }

  return maljan;
}

int main() {
  string s;

  unordered_map<string, int> wires;
  unordered_map< string, vector<string> > reverse;

  while (getline(cin, s)) {
    if (s.empty()) break;
    auto mal = s.find(":");

    string wire = s.substr(0, mal);
    int val = stoi(s.substr(mal + 2));
    wires[wire] = val;
  }

  set< vector<string> > oprs;
  vector< vector<string> > oprs_part;

  vector<string> sw1, sw2;

  while (getline(cin, s)) {
    istringstream ss(s);

    vector<string> opr;

    while (ss >> s) {
      if (s != "->") {
        opr.push_back(s);
      }
    }

    reverse[opr[3]] = opr;
    oprs.insert(opr);

    if (opr[3] != "z21") {
      oprs_part.push_back(opr);
    } else {
      sw1 = opr;
    }
  }

  cout << get_ans(oprs, wires) << endl;

  for (auto& op: oprs) {
    if (op[1] == "XOR") {
      if (op[3][0] != 'z' && !(op[0][0] == 'x' || op[0][0] == 'y')) {
          cout << op[0] << ' ' << op[1] << ' ' << op[2] << ' ' << op[3] << endl;
      }
    } else if (op[1] == "OR") {
      if (op[3][0] == 'z') {
        cout << op[0] << ' ' << op[1] << ' ' << op[2] << ' ' << op[3] << endl;
      }
    } else {
      if ((op[0][0] == 'x' || op[0][0] == 'y') && op[3][0] == 'z') {
        cout << op[0] << ' ' << op[1] << ' ' << op[2] << ' ' << op[3] << endl;
      }
    }
  }

  // Got the part 2 answer by combining outputs from different sub-solutions,
  // the last pair I got by looking at `x XOR y C` pairs which do not
  // end up in a ZXX wire. It would mean that bit would be
  // lost if not swapped correctly.
  // Too lazy to put that solution back.

  return 0;
}
