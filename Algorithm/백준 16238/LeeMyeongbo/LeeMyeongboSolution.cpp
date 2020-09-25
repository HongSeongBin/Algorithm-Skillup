#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

int N, sheep[1000], ans;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", sheep + i);
	sort(sheep, sheep + N);

	int night = 0;
	for (int i = N - 1; i >= 0; i--) {		// ������������ �����ϰ� �� �����ʿ������� 1�� ���� ���ذ��� ��
		if (sheep[i] - night <= 0)
			break;
		ans += sheep[i] - night++;
	}
	printf("%d", ans);
	return 0;
}