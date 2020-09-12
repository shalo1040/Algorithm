// [1764] 듣보잡 : https://www.acmicpc.net/problem/1764
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<string> ans;

int main() {
	cin >> N >> M;
	set<string> s;
	string str;
	for(int i = 0; i < N; i++) {
		cin >> str;
		s.insert(str);
	}
	for(int i = 0; i < M; i++) {
		cin >> str;
		if(s.find(str) != s.end())
			ans.push_back(str);
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for(int i = 0; i < ans.size(); i++)
		cout << ans[i] << endl;
	return 0;
}