#include <iostream>
#include <vector>
#include <sstream>

#define mp(x, y) make_pair(x, y)
#define ll long long

using namespace std;

ll get_combo(ll a, ll b, ll c, ll opd) {
  if (opd >= 0 && opd <= 3) {
    return opd;
  }

  switch (opd) {
    case 4:
      return a;
    case 5:
      return b;
    case 6:
      return c;
  }
}

vector<ll> run(ll a, ll b, ll c, vector<int>& program) {
  vector<ll> output;
  int i = 0;
  while (i < program.size()) {
    int opc = program[i];
    ll opd = program[i + 1];

    bool jumped = false;

    switch (opc) {
      case 0:
        a = a / (1 << get_combo(a, b, c, opd));
        break;
      case 1:
        b = b xor opd;
        break;
      case 2:
        b = get_combo(a, b, c, opd) % 8;
        break;
      case 3:
        if (!a) break;
        i = opd;
        jumped = true;
        break;
      case 4:
        b = b xor c;
        break;
      case 5:
        output.push_back(get_combo(a, b, c, opd) % 8);
        cout << get_combo(a, b, c, opd) % 8 << ',';
        break;
      case 6:
        b = a / (1 << get_combo(a, b, c, opd));
        break;
      case 7:
        c = a / (1 << get_combo(a, b, c, opd));
        break;
    }

    if (!jumped) i += 2;
  }

  return output;
}

void funcSimpl(long long a, vector<int>& program, int n) {
  if (n == -1) {
    cout << "ans: " << a << endl;
    return;
  }

  for (int k = 0; k <= 7; k++) {
    ll sal = a * 8 + k;

    ll mal = ((((sal % 8) xor 2) xor sal / (1 << ((sal % 8) xor 2))) xor 7) % 8;
    if (mal == program[n]) {
      funcSimpl(sal, program, n - 1);
    }
  }
}


int main() {
  ll a, b, c;
  vector<int> program;

  string s;

  getline(cin, s);
  sscanf(s.c_str(), "Register A: %lld", &a);

  getline(cin, s);
  sscanf(s.c_str(), "Register B: %lld", &b);

  getline(cin, s);
  sscanf(s.c_str(), "Register C: %lld", &c);

  getline(cin, s);
  getline(cin, s);

  istringstream mal(s);

  string jal;
  mal >> jal;
  int n;
  char cc;

  while (mal >> n) {
    program.push_back(n);
    mal >> cc;
  }

  //run(a, b, c, program);

  funcSimpl(0, program, program.size() - 1);

  return 0;
}
