#include <iostream>
using namespace std;

int K, order[100][2];
char saw[4][9];

void rotate(int rotating_saw, int dir) {
	if (dir == 1) {											// �ð� ���� ȸ��
		int temp = saw[rotating_saw][7];
		for (int i = 6; i >= 0; i--)
			saw[rotating_saw][i + 1] = saw[rotating_saw][i];
		saw[rotating_saw][0] = temp;
	}
	else if (dir == -1) {									// �ݽð� ���� ȸ��
		int temp = saw[rotating_saw][0];
		for (int i = 0; i < 7; i++)
			saw[rotating_saw][i] = saw[rotating_saw][i + 1];
		saw[rotating_saw][7] = temp;
	}
}

int Solve() {
	int ans = 0;
	for (int i = 0; i < K; i++) {
		int rotating_saw = order[i][0] - 1;				// ������ ���
		int saw_list[4] = { 0, };						// ������ ��Ϲ������� ���� ����� �迭
		int dir = order[i][1];
		saw_list[rotating_saw] = dir;

		for (int j = rotating_saw - 1; j >= 0; j--) {	// ���� ������ ����� ���ʵ� ���� ���캽
			if (saw[j][2] != saw[j + 1][6]) {			// �ٸ� ���̶�� ���� * -1 �ؼ� ����
				dir *= -1;
				saw_list[j] = dir;
			}
			else break;
		}
		dir = order[i][1];
		for (int j = rotating_saw + 1; j < 4; j++) {	// ������ ���캽
			if (saw[j][6] != saw[j - 1][2]) {
				dir *= -1;
				saw_list[j] = dir;
			}
			else break;
		}
		for (int i = 0; i < 4; i++)						// 4�� ��� ���ʷ� ����� ������ ����
			rotate(i, saw_list[i]);
	}
	for (int i = 0; i < 4; i++)
		if (saw[i][0] == '1')
			ans += 1 << i;
	return ans;
}

int main() {
	for (int i = 0; i < 4; i++)
		cin >> saw[i];
	cin >> K;
	for (int i = 0; i < K; i++)
		cin >> order[i][0] >> order[i][1];
	cout << Solve();
	return 0;
}