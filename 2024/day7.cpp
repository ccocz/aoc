#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

long long ans = 0;

bool ok(long long n, vector<long long>& v, long long now, int i) {
    if (now > n) {
        return false;
    }

    if (i == v.size()) {
        return n == now;
    }

    bool oki = ok(n, v, now + v[i], i + 1);
    if (i != 0) {
        oki |= ok(n, v, 1LL * now * v[i], i + 1);

        long long sal = v[i];
        long long mul = 1;

        while (sal) {
            mul *= 10;
            sal /= 10;
        }

        oki |= ok(n, v, mul * now + v[i], i + 1);
    }

    return oki;
}

void solve(long long n, vector<long long> v) {
    ans += ok(n, v, 0, 0) * n;
}

int main() {
    string s;

    while (getline(cin, s)) {
        istringstream c(s);

        long long n;
        c >> n;

        char t;
        c >> t;

        vector<long long> nums;
        long long num;
        while (c >> num) {
            nums.push_back(num);
        }

        solve(n, nums);
    }

    cout << "ansa: " << ans << endl;
    return 0;
}
