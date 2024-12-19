#include <iostream>
#include <map>
#include <vector>

using namespace std;

int digi_count(long long x) {
  int res = 0;
  while (x) {
    res++;
    x /= 10;
  }

  return res;
}

pair<long long, long long> get_me(long long n) {
  int x = digi_count(n) / 2;

  long long fr = 0, sc = 0;

  vector<int> digits;
  while (n) {
    digits.push_back(n % 10);
    n /= 10;
  }

  reverse(digits.begin(), digits.end());

  long long mal = 1;

  for (int i = x - 1; i >= 0; i--) {
    fr += mal * digits[i];
    mal *= 10;
  }

  mal = 1;

  for (int i = digits.size() - 1; i >= x; i--) {
    sc += mal * digits[i];
    mal *= 10;
  }

  return make_pair(fr, sc);
}

map<pair<long long, int>, long long> mal;

long long cnt(long long n, int m) {
  if (m == 0) {
    return 1;
  }

  if (mal.find(make_pair(n, m)) != mal.end()) {
    return mal[make_pair(n, m)];
  }

  long long x = n;

  if (!x) {
    return mal[make_pair(n, m)] = cnt(1, m - 1);
  } else if (digi_count(x) % 2 == 0) {
    auto sal = get_me(x);
    return mal[make_pair(n, m)] = cnt(sal.first, m - 1) + cnt(sal.second, m - 1);
  } else {
    return mal[make_pair(n, m)] = cnt(x * 2024, m - 1);
  }

}

int main() {
  vector<long long> v(8);

  long long ans = 0;

  for (long long& x : v) {
    cin >> x;

    ans += cnt(x, 75);
  }

  cout << ans << endl;

  return 0;
}