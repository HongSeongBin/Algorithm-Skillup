#include <iostream>
#include <cmath>
#include <queue>
#define MAX 1000000000								// ���ͽ�Ʈ�� �ʱ� �ִ�
using namespace std;

struct Node {
	int y, x, time;
};
queue<Node> q;
int N, M, T, D, height[25][25], visited[25][25], r_visited[25][25];		// visited : (0, 0)���� �� �������� �ɸ��� �ð��� �ּڰ� ����
const int dx[] = { 1, -1, 0, 0 }, dy[] = { 0, 0, 1, -1 };				// r_visited : �� �������� (0, 0)���� ���ƿ� �� �ɸ��� �ð��� �ּڰ� ����
char map[25][26];

void Start() {							// (0, 0)���� ����Ͽ� �� �������� ���� �� �ɸ��� �ð��� �ּڰ� ����
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = MAX;
	q.push({ 0, 0, 0 });
	visited[0][0] = 0;
	
	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int X = node.x + dx[i];
			int Y = node.y + dy[i];
			if (X >= 0 && X < M && Y >= 0 && Y < N && abs(height[node.y][node.x] - height[Y][X]) <= T) {
				int time_spent = node.time;
				if (height[Y][X] > height[node.y][node.x])		// ������ ���� ���̰� ���� ��ġ�� ���̺��� ���� ���
					time_spent += (height[Y][X] - height[node.y][node.x]) * (height[Y][X] - height[node.y][node.x]);
				else
					time_spent += 1;
				if (time_spent < visited[Y][X]) {
					q.push({ Y, X, time_spent });
					visited[Y][X] = time_spent;
				}
			}
		}
	}
}

int go_Back() {						// �ٽ� (0, 0)�������� �����Ͽ� ������ ����� ����
	int h = -1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			r_visited[i][j] = MAX;
	q.push({ 0, 0, 0 });
	r_visited[0][0] = 0;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int X = node.x + dx[i];
			int Y = node.y + dy[i];
			if (X >= 0 && X < M && Y >= 0 && Y < N && abs(height[node.y][node.x] - height[Y][X]) <= T) {
				int time_spent = node.time;
				if (height[Y][X] < height[node.y][node.x])		// ������ ���� ���̰� ���� ��ġ���� ���� ��� (���ƿ� ���� ������ ����ؾ� ��)
					time_spent += (height[Y][X] - height[node.y][node.x]) * (height[Y][X] - height[node.y][node.x]);
				else
					time_spent += 1;
				if (time_spent < r_visited[Y][X]) {
					q.push({ Y, X, time_spent });
					r_visited[Y][X] = time_spent;
				}
			}
		}
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (visited[i][j] + r_visited[i][j] <= D)
				h = h < height[i][j] ? height[i][j] : h;
	return h;
}

int main() {
	cin >> N >> M >> T >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] <= 'Z')
				height[i][j] = map[i][j] - 'A';
			else if (map[i][j] <= 'z')
				height[i][j] = map[i][j] - 'a' + 26;
		}
	}
	Start();
	cout << go_Back();
	return 0;
}