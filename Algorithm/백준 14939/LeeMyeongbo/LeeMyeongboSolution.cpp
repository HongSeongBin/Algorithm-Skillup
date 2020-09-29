#include <iostream>
#include <cstring>
using namespace std;

char c;
int chk[10][10], ans = -1;
const int dc[] = { 1, -1, 0, 0 }, dr[] = { 0, 0, 1, -1 };

void DFS(int num, int cur_num, int start) {			// �� ���ٿ��� num���� ����ġ ������ ���� 2��° ~ 10��° �� ���ʷ� ����
	if (num == cur_num) {
		int tmp_ans = num;							// �� ���ٿ��� ��ư ���� Ƚ�� �⺻������ �����ؾ� ��!
		int tmp_chk[10][10];
		memcpy(tmp_chk, chk, sizeof(tmp_chk));		// �ӽ� �迭���� �� ���� ������ ���� ���� (���� �迭 ���� ����)

		for (int i = 1; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (!tmp_chk[i - 1][j])
					continue;
				tmp_chk[i][j] = (tmp_chk[i][j] + 1) % 2;
				tmp_ans++;
				for (int d = 0; d < 4; d++) {
					int R = i + dr[d];
					int C = j + dc[d];
					if (R >= 0 && R < 10 && C >= 0 && C < 10)
						tmp_chk[R][C] = (tmp_chk[R][C] + 1) % 2;
				}
			}
		}
		for (int i = 0; i < 100; i++)
			if (tmp_chk[i / 10][i % 10])			// ���߿� �ϳ��� ���� �� �ִٸ� ����!
				return;
		if (ans == -1)
			ans = tmp_ans;
		ans = ans > tmp_ans ? tmp_ans : ans;		// �ǵ帰 ����ġ ���� �ּڰ� ����
		return;
	}
	for (int c = start; c < 10; c++) {
		chk[0][c] = (chk[0][c] + 1) % 2;					// �� ���ٿ� �ش� ����ġ ��
		for (int d = 0; d < 4; d++) {						// �� ����ġ �ֺ� ����ġ ��
			int R = dr[d];
			int C = c + dc[d];
			if (R >= 0 && R < 10 && C >= 0 && C < 10)
				chk[R][C] = (chk[R][C] + 1) % 2;
		}
		DFS(num, cur_num + 1, c + 1);
		chk[0][c] = (chk[0][c] + 1) % 2;					// �� ����ġ ���� ��
		for (int d = 0; d < 4; d++) {						// �ֺ��� �ٽ� ���󺹱�
			int R = dr[d];
			int C = c + dc[d];
			if (R >= 0 && R < 10 && C >= 0 && C < 10)
				chk[R][C] = (chk[R][C] + 1) % 2;
		}
	}
}

int Solve() {
	for (int i = 0; i <= 10; i++) {
		DFS(i, 0, 0);
	}
	return ans;
}

int main() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			cin >> c;
			if (c == '#')
				chk[i][j] = 0;
			else
				chk[i][j] = 1;
		}
	
	cout << Solve();
	return 0;
}