#include <iostream>
#include <queue>
#define MAX 500001
using namespace std;

struct Node {
	int cur, time;
};
queue<Node> q;
int n, k, visited[2][MAX], ans = MAX;					// visited[0][n] : ¦�� �� �ּ� �ð�, visited[1][n] : Ȧ�� �� �ּ� �ð�
														// ���� ��� ������ �ּ� N�ʸ��� �����ߴٰ� �ϸ� (N + 2)��, (N + 4)��, ... ���� ��湮 ����!
void BFS() {
	for (int i = 0; i < MAX; i++) {
		visited[0][i] = visited[1][i] = MAX;
	}
	q.push({ n, 0 });
	visited[0][n] = 0;
	int cur_time = 0, weight = 1;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();
		if (node.time != cur_time) {					// ���� �ð� ���� �����̰� �� �� �ִ� ��� �̵��� �Ϸ����� ��� ���� �̵� �� ���� �ð� ����
			k += weight++;
			cur_time++;
		}
		if (k < MAX) {
			if (visited[0][k] <= cur_time && cur_time % 2 == 0) {		// ���� �ð��� ¦���̰� �ش� �������� ���µ� �ɸ��� �ּ� ¦�� �ð��� ���� �ð� ������ ���
				ans = cur_time;
				return;
			}
			else if (visited[1][k] <= cur_time && cur_time % 2 != 0) {	// ���� �ð��� Ȧ���̰� �ش� �������� ���µ� �ɸ��� �ּ� Ȧ�� �ð��� ���� �ð� ������ ���
				ans = cur_time;
				return;
			}
		}
		else if (k >= MAX)												// ���� ��ġ�� 500000�� �Ѿ�� �Ǹ� �ٷ� ����
			return;
		if (node.cur - 1 >= 0) {										// -1 �̵� ������ ��
			if ((node.time + 1) % 2 == 0 && visited[0][node.cur - 1] > node.time + 1) {			// �ּ� ¦�� �ð� ���� �� ť ����, �湮 üũ
				q.push({ node.cur - 1, node.time + 1 });
				visited[0][node.cur - 1] = node.time + 1;
			}
			else if ((node.time + 1) % 2 != 0 && visited[1][node.cur - 1] > node.time + 1) {	// �ּ� Ȧ�� �ð� ���� �� ť ����, �湮 üũ
				q.push({ node.cur - 1, node.time + 1 });
				visited[1][node.cur - 1] = node.time + 1;
			}
		}
		if (node.cur + 1 < MAX) {										// +1 �̵� ������ ��
			if ((node.time + 1) % 2 == 0 && visited[0][node.cur + 1] > node.time + 1) {
				q.push({ node.cur + 1, node.time + 1 });
				visited[0][node.cur + 1] = node.time + 1;
			}
			else if ((node.time + 1) % 2 != 0 && visited[1][node.cur + 1] > node.time + 1) {
				q.push({ node.cur + 1, node.time + 1 });
				visited[1][node.cur + 1] = node.time + 1;
			}
		}
		if (node.cur * 2 < MAX) {										// *2 �̵� ������ ��
			if ((node.time + 1) % 2 == 0 && visited[0][node.cur * 2] > node.time + 1) {
				q.push({ node.cur * 2, node.time + 1 });
				visited[0][node.cur * 2] = node.time + 1;
			}
			else if ((node.time + 1) % 2 != 0 && visited[1][node.cur * 2] > node.time + 1) {
				q.push({ node.cur * 2, node.time + 1 });
				visited[1][node.cur * 2] = node.time + 1;
			}
		}
	}
}

int main() {
	cin >> n >> k;
	BFS();
	if (ans == MAX)
		cout << -1;
	else
		cout << ans;
	return 0;
}