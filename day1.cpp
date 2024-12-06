#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    
    vector<int> a, b;
    pair<int, int> p;
    
    map<int, int> sal;
    
    while (cin >> p.first >> p.second) {
        a.push_back(p.first);
        b.push_back(p.second);
        
        if (sal.find(p.second) == sal.end()) {
            sal[p.second] = 1;
        } else {
            sal[p.second]++;
        }
    
    }
    
    //sort(a.begin(), a.end());
    //sort(b.begin(), b.end());
    
    long long ans = 0;
    
    for (int i = 0; i < a.size(); i++) {
        ans += a[i] * sal[a[i]];
    }
    
    cout << ans << endl;

    return 0;
}
