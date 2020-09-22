#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> v;
int T, N, first, second;

int Solve() {
	int s = v[0].second, ans = 1;
	for (int i = 1; i < N; i++) {
		if (v[i].second < s) {			// ���� ���� ������ �� ���� ����� �ִٸ� �����ϰ� ans + 1
			s = v[i].second;
			ans++;
		}
	}
	return ans;
}

int main() {
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N;
		for (int n = 0; n < N; n++) {
			cin >> first >> second;
			v.push_back(make_pair(first, second));
		}
		sort(v.begin(), v.end());		// 1�� ���� �ɻ� �������� �������� ����
		cout << Solve() << "\n";
		v.clear();
	}
	return 0;
}