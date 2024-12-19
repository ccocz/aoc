#include <iostream>
#include <map>
#include <sstream>

using namespace std;

void solve(long long a1, long long b1, long long c1, long long a2, long long b2, long long c2, long long& ans) {
    long long det = a1 * b2 - a2 * b1;

    if (det == 0) {
        return;
    }

    long long x_num = c1 * b2 - c2 * b1;
    long long y_num = a1 * c2 - a2 * c1;

    if (x_num % det == 0 && y_num % det == 0) {
        long long x = x_num / det;
        long long y = y_num / det;
        ans += x * 3 + y;
    }
}

int main() {
  string buta, butb, priz, empt;

  long long ans = 0;

  while (true) {
    if (!getline(cin, buta)) {
      break;
    }

    getline(cin, butb);
    getline(cin, priz);
    getline(cin, empt);

    long long butax = -1, butay = -1;
    long long butbx = -1, butby = -1;
    long long prizex = -1, prizey = -1;

    for (int i = 0; i < buta.length(); i++) {
      if (buta[i] == '+') {
        long long k = i + 1, num = 0;

        while (k < buta.length() && buta[k] != ',') {
          num *= 10;
          num += buta[k] - '0';
          k++;
        }

        if (butax == -1) butax = num;
        else butay = num;
      }
    }

    for (int i = 0; i < butb.length(); i++) {
      if (butb[i] == '+') {
        long long k = i + 1, num = 0;

        while (k < butb.length() && butb[k] != ',') {
          num *= 10;
          num += butb[k] - '0';
          k++;
        }

        if (butbx == -1) butbx = num;
        else butby = num;
      }
    }

    for (int i = 0; i < priz.length(); i++) {
      if (priz[i] == '=') {
        long long int k = i + 1, num = 0;

        while (k < priz.length() && priz[k] != ',') {
          num *= 10;
          num += priz[k] - '0';
          k++;
        }

        if (prizex == -1) prizex = num;
        else prizey = num;
      }
    }

    prizex += 10000000000000;
    prizey += 10000000000000;

    solve(butax, butbx, prizex, butay, butby, prizey, ans);
  }

  cout << "ans: " << ans << endl;

  return 0;
}