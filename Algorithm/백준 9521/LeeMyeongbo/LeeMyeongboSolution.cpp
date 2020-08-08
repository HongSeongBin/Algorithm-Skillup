#include <iostream>
using namespace std;

int N, f[1000001], visited[1000001], cycle_start, cycle_depth;
unsigned long long K, color[1000001], ans = 1;

void DFS(int index, int depth, int cycle_num) {
	if (!visited[index]) {								// �ش� ������ �湮�� ���� ���ٸ�
		visited[index] = cycle_num;						// �� ������ ����Ŭ ��ȣ �ϴ� ����
		DFS(f[index], depth + 1, cycle_num);			// f[i]�� �������� �ٽ� Ž��
		if (cycle_start == index) {						// ����Ŭ ���� ���� �߰� ��
			int cycle_length = cycle_depth - depth;		// ���� ���� ��߰� ���� �� ���̿��� ���� ���� ó�� �߰� �� ���̸� ���� ����Ŭ ���� ����
			ans = ans * color[cycle_length] % 1000000007;
			cycle_start = cycle_depth = 0;				// ����Ŭ ���� ������ ���� �ٽ� ������� ����
		}
		else if (!cycle_start) {						// ����Ŭ ���� ������ 0�̶�� ���� ������ ����Ŭ�� �ƴ� ����
			ans = ans * (K - 1) % 1000000007;
		}
	}
	else if (visited[index] == cycle_num) {			// �湮�� ������ �̹� ���� ����Ŭ ��ȣ�� ����Ǿ� ���� ���
		cycle_start = index;						// �� ������ �ٷ� ����Ŭ ���� ����
		cycle_depth = depth;						// ����Ŭ ���� �˱� ���� ���̵� ���� ����
	}
}

unsigned long long Solve() {
	int cycle_num = 1;					// ����Ŭ ��ȣ (1���� ����)
	for (int i = 1; i <= N; i++) {
		DFS(i, 0, cycle_num);
		cycle_num++;
	}
	return ans;
}

int main() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		scanf("%d", f + i);
	color[1] = K;
	color[2] = K * (K - 1) % 1000000007;
	color[3] = K * (K - 1) * (K - 2) % 1000000007;
	for (int i = 4; i <= 1000000; i++)
		color[i] = ((K - 1) * color[i - 2] + (K - 2) * color[i - 1]) % 1000000007;		// DP ���̺� ä��
	cout << Solve();
	return 0;
}