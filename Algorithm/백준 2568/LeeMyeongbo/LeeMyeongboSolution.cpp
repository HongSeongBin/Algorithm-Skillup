#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, a, b, B[100001], chk[100001];		// chk : LIS������ B[i]�� index + 1 ����
bool is_connected[100001];
vector<pair<int, int>> wire;
vector<int> LIS;

void Solve() {
	LIS.push_back(B[0]);
	chk[0] = 1;
	for (int i = 1; i < N; i++) {
		int left = 0;							// left : �� ó�� index
		int right = LIS.size() - 1;				// right : �� ������ index
		while (left <= right) {					// �̺� Ž������ B[i]�� �� ������ ��ġ Ž��
			int middle = (left + right) / 2;
			if (LIS[middle] > B[i])
				right = middle - 1;
			else
				left = middle + 1;
		}
		if (left == LIS.size())
			LIS.push_back(B[i]);				// LIS�� ������ ���Һ��� B[i]�� ũ�ٸ� �߰� (��������� LIS�� ������������ ����)
		else
			LIS[left] = B[i];					// �װ� �ƴϸ� �ش� �ڸ��� B[i]�� �ٲ�
		chk[i] = left + 1;
	}

	int size = LIS.size();						// LIS�� ���� = ���� ���� �κ� ������ ����
	printf("%d\n", N - size);
	for (int i = N - 1; i >= 0; i--) {			// �� �����ʿ������� ���ʷ� LIS�� �ش��ϴ� index�� true�� ó��
		if (chk[i] == size) {
			size--;
			is_connected[i] = true;
		}
	}
	for (int i = 0; i < N; i++) {
		if (!is_connected[i])
			printf("%d\n", wire[i].first);		// LIS�� �ش����� �ʴ� index�� A ��ġ �������� ���
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
		wire.push_back(make_pair(a, b));
	}
	sort(wire.begin(), wire.end());			// ���� ������ A ���� ������������ ������ ����
	for (int i = 0; i < N; i++)
		B[i] = wire[i].second;				// ���ĵ� �������� ������ B ��ġ ����
	Solve();
	return 0;
}