#include <iostream>
#include <algorithm>
using namespace std;

int N, M, mem[101], cost[101], dp[101][10001], ans = 1000000;

int Knapsack() {
	for (int app = 1; app <= N; app++) {		// 1��° �ۺ��� i��° �۱��� �� �� ���� ��
		for (int c = 0; c <= 10000; c++) {		// ������ �� �ִ� ��� 0���� ����
			if (c < cost[app])					// ���� app��°�� ���� ����� ���� ������ �� �ִ� ���(c)���� ���� ���
				dp[app][c] = dp[app - 1][c];	// app - 1��°���� ����� �� �ִ� �޸𸮸� ����
			else {
				dp[app][c] = max(dp[app - 1][c - cost[app]] + mem[app], dp[app - 1][c]);	// app��° �� ����� ���� ���� �ʾ��� �� �� �� ū �޸� ����
				if (dp[app][c] >= M)			// ���� ����� �޸� ���� M �̻��̶��
					ans = min(ans, c);			// ��� �ּڰ� ����
			}
		}
	}
	return ans;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		cin >> mem[i];
	for (int i = 1; i <= N; i++)
		cin >> cost[i];
	cout << Knapsack();
	return 0;
}