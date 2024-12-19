#include <iostream>
#include <sstream>

using namespace std;

void add(long long& sum, string sal) {
	istringstream is(sal);
	
	int a, b;
	char c;
		
	if (is >> a >> c >> b) {
		if (c == ',') {
			char d;
			is >> d;
			
			if (d == ')') {
				sum += a * b;
			}
		}
	}
}

int main() {
	string s;
	
	string mal = "";
	
	while (getline(cin, s)) {
		mal += s;
	}
	
	long long sum = 0;	
	bool dont = false;
	size_t i = 0;
	
	while (i < mal.length()) {
		if (mal.substr(i, 4) == "mul(") {
			if (!dont) add(sum, mal.substr(i + 4));
			i += 4;
		} else if (mal.substr(i, 7) == "don't()") {
			dont = true;
			i += 7;
		} else if (mal.substr(i, 4) == "do()") {
			dont = false;
			i += 4;
		} else {
			i++;
		}
	}
	
	cout << sum << endl;
	return 0;
}
