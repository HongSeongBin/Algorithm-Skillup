#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

// ���� BFS�� �̿��� Ǯ��
struct Node {
	int y, x;
};
int N, M, island_num[2000][2000], tot = 1;
const int dx[] = { 1, -1, 0, 0, 1, -1, -1, 1 }, dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };	// �� �� �� �� ���� ���� ���� ���� ��
char map[2000][2001];
bool visited[2000][2000], searched_island[4000001];			// �ٴٸ� ���� �ʺ� Ž���ϸ� ã�� ���� searched_island�� üũ

void indexing() {							// ���鸶�� ��ȣ �ο�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (island_num[i][j] > 0 || map[i][j] == '.')		// �̹� ��ȣ�� �Ű�ų� �ٴٶ�� skip
				continue;
			queue<Node> q;
			q.push({ i, j });
			island_num[i][j] = tot;

			while (!q.empty()) {
				Node node = q.front();
				q.pop();

				for (int d = 0; d < 4; d++) {
					int X = node.x + dx[d];
					int Y = node.y + dy[d];
					if (X >= 0 && X < M && Y >= 0 && Y < N && !island_num[Y][X] && map[Y][X] == '#') {
						q.push({ Y, X });
						island_num[Y][X] = tot;
					}
				}
			}
			tot++;
		}
	}
}

void search() {
	queue<Node> q;
	q.push({ 0, 0 });
	visited[0][0] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		for (int d = 0; d < 8; d++) {					// 8�������� ���캽
			int X = node.x + dx[d];
			int Y = node.y + dy[d];
			if (X >= 0 && X < M && Y >= 0 && Y < N && !visited[Y][X]) {
				if (map[Y][X] == '.') {
					if (d < 4)							// ó�� �� �� �� �� �̷��� ���� ���� ��ó �ٴ� ������ ť�� ����
						q.push({ Y, X });
					else if (d >= 4 && map[Y][node.x] == '#' && map[node.y][X] == '#') {	// �밢�� ���� Ž�� �� ������ ���� �ִ� ��� ���
						if (island_num[Y][node.x] != island_num[node.y][X]) {				// ���� ���� ���� ���� �ƴϸ� ���� �ٴٷ�
							q.push({ Y, X });
							searched_island[island_num[Y][node.x]] = searched_island[island_num[node.y][X]] = true;
						}
					}
					else								// ������ ���� 1�� �����̸� �״�� ����
						q.push({ Y, X });
				}
				else
					searched_island[island_num[Y][X]] = true;
				visited[Y][X] = true;
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%s", map[i]);
	indexing();
	search();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == '.')
				printf(".");
			else {
				if (searched_island[island_num[i][j]])
					printf("O");
				else
					printf("X");
			}
		}
		printf("\n");
	}
	return 0;
}