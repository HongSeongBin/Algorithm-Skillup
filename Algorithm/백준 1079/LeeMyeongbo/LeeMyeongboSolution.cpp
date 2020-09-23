#include <iostream>
using namespace std;

int N, n, maphia, guilty[16], R[16][16], ans;
bool dead[16];		// ���� ��� üũ

void DFS(int tmp) {
	if (dead[maphia]) {							// ���Ǿư� �׾��ٸ� ���� ���� Ƚ�� �ִ� �����ϰ� ����
		ans = ans < tmp ? tmp : ans;
		return;
	}
	/*
	bool all_kill = true;
	for (int i = 0; i < N; i++) {
		if (!dead[i] && i != maphia) {			// ���� ���� �ù��� �����ִٸ�
			all_kill = false;
			break;
		}
	}
	if (all_kill) {								// �ù��� ��� �׾��ٸ� ���� �� ���� Ƚ�� �ִ� �����ϰ� ����
		ans = ans < tmp ? tmp : ans;
		return;
	}
	*/
	if (n % 2 == 0) {							// ���� �� ���Ǿư� ���� ��� �� �� ����
		for (int i = 0; i < N; i++) {
			if (!dead[i] && i != maphia) {
				dead[i] = true;
				for (int j = 0; j < N; j++)
					guilty[j] += R[i][j];
				n--;
				DFS(tmp + 1);					// �㿡�� ���� �� �� �� ���� Ƚ�� +1
				for (int j = 0; j < N; j++)
					guilty[j] -= R[i][j];
				n++;
				dead[i] = false;
			}
		}
	}
	else {										// ���� �� ���� ���� ���� ���� �ù� ����
		int guilt = -1;
		int kill;
		for (int i = 0; i < N; i++) {
			if (!dead[i] && guilt < guilty[i]) {	// ��� �����鼭 ���� ������ ���� ���� ��� ã��
				kill = i;
				guilt = guilty[i];
			}
		}
		dead[kill] = true;
		n--;
		DFS(tmp);								// ������ �� �� �� �� ���� Ƚ�� +1 ����
		n++;
		dead[kill] = false;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> guilty[i];
	for (int i = 0; i < N * N; i++)
		cin >> R[i / N][i % N];
	cin >> maphia;

	n = N;
	DFS(0);
	cout << ans;
	return 0;
}