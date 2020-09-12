// [1543] 문서 검색 : https://www.acmicpc.net/problem/1543
#include <iostream>
#include <string>
using namespace std;

string a, b;
int ans;

int main() {
	getline(cin, a);
	getline(cin, b);
	if(a.length() < b.length()) ans = 0;
	else {
	    for(int i = 0; i <= a.length()-b.length();) {
    		if(a[i] != b[0]) { i++; continue; }
    		if(a.substr(i, b.length()) == b) { ans++; i += b.length(); }
    		else i++;
    	}
	}
	cout << ans;
	return 0;
}