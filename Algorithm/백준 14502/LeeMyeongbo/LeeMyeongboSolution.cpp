#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
	int y, x;
};
int N, M, map[8][8], ans = -1, dx[] = { 1, -1, 0, 0 }, dy[] = { 0, 0, 1, -1 };

int BFS() {
	int temp = 0;
	queue<Node> q;
	bool visited[8][8];									// ���̷��� �湮 üũ
	memset(visited, false, sizeof(visited));
	for(int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 2) {						// �ʱ� ���̷��� ��ġ ť�� ����
				q.push({ i, j });
				visited[i][j] = true;
			}
		}
	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		for (int d = 0; d < 4; d++) {
			int X = node.x + dx[d];
			int Y = node.y + dy[d];
			if (X >= 0 && X < M && Y >= 0 && Y < N && !visited[Y][X] && !map[Y][X]) {	// ���̷��� �湮���� ���� �� + ��ĭ �̸� ���̷��� ����
				visited[Y][X] = true;
				q.push({ Y, X });
			}
		}
	}
	for(int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (!map[i][j] && !visited[i][j])			// ��ĭ�̸鼭 ���̷��� ������ ���� �� ���� ��Ʒ��� ����
				temp++;
	return temp;
}

void DFS(int depth, int start_row, int start_col) {		// �� ĭ �߿��� 3���� ���� ������� �̾Ƽ� ������ ����
	if (depth == 3) {									// �� ĭ 3�� ��� ������ ��������� ���̷��� �۶߸�
		int num = BFS();
		ans = ans < num ? num : ans;					// �ִ� ����
		return;
	}
	for (int i = start_row; i < N; i++) {
		if (i > start_row)
			start_col = 0;
		for (int j = start_col; j < M; j++) {
			if (!map[i][j]) {
				map[i][j] = 1;							// ��ĭ�� ������
				DFS(depth + 1, i, j + 1);
				map[i][j] = 0;							// ������ ���� ��ĭ ���󺹱�
			}
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	DFS(0, 0, 0);
	cout << ans;
	return 0;
}