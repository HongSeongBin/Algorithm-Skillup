#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#define MAX 100001;
using namespace std;

struct Node {
	int r, c, cnt;		// ���� ��, ��, ������ �� ����
};
queue<Node> q[3];		// �� �ٱ����� �����ϴ� ����� + �˼� 2�� �� 3���� ��� ������ ���ؼ� BFS�� �����ϱ� ���� ť �迭 ����
int T, h, w, weight[3][102][102], dc[] = { 1, -1, 0, 0 }, dr[] = { 0, 0, 1, -1 }, ans = MAX;
char map[105][105];

void BFS() {
	for (int human = 0; human < 3; human++) {		// �����, �˼� 1, �˼� 2 ������ �� ������ �̸������ ����� �ϴ� ���� �ּ� ���� weight�� ����
		while (!q[human].empty()) {
			Node node = q[human].front();
			q[human].pop();
			
			for (int d = 0; d < 4; d++) {
				int R = node.r + dr[d];
				int C = node.c + dc[d];
				if (R >= 0 && R < h + 2 && C >= 0 && C < w + 2 && map[R][C] != '*') {
					if (map[R][C] == '.' && weight[human][R][C] > node.cnt) {				// �� ĭ�̸� �� ���±��� ������ �� Ƚ�� �״��
						q[human].push({ R, C, node.cnt });
						weight[human][R][C] = node.cnt;
					}
					else if (map[R][C] == '#' && weight[human][R][C] > node.cnt + 1) {		// ���� �����ٸ� ������ �� Ƚ�� + 1
						q[human].push({ R, C, node.cnt + 1 });
						weight[human][R][C] = node.cnt + 1;
					}
				}
			}
		}
	}
	for (int i = 1; i < h + 1; i++) {
		for (int j = 1; j < w + 1; j++) {
			int temp = weight[0][i][j] + weight[1][i][j] + weight[2][i][j];
			if (map[i][j] == '#')				// ���� �ִ� �����̶�� �����, �˼� 1, �˼� 2 �̷��� Ƚ���� 2�� �� ��ø�ǹǷ� -2 ����� ��
				temp -= 2;
			ans = ans > temp ? temp : ans;		// �ּڰ� ����
		}
	}
}

int main() {
	cin >> T;
	for (int t = 0; t < T; t++) {				// �� �����ڸ� �κ��� '.'(��ĭ)���� �ѷ��ΰ� ����
		scanf("%d %d", &h, &w);
		for (int f = 0; f < 3; f++)
			for (int r = 0; r < h + 2; r++)
				for (int c = 0; c < w + 2; c++)
					weight[f][r][c] = MAX;

		q[0].push({ 0, 0, 0 });					// �� ó���� ����̰� �� �ٱ� (0, 0)���� �����ϴ� ������ ť�� ����
		weight[0][0][0] = 0;
		int index = 1;
		for (int i = 0; i < w + 2; i++)			// �� ���� ���� ���� '.' �߰�
			map[0][i] = '.';
		for (int i = 1; i < h + 1; i++) {		// �� ���� ���ʰ� ������ ���� '.' �߰��ϰ� ���ÿ� �˼� 2�� ��ġ ť�� ����
			map[i][0] = '.';					// ���� �� '.' �߰�
			scanf("%s", map[i] + 1);
			for (int j = 0; j < w + 1; j++) {
				if (map[i][j] == '$') {
					q[index].push({ i, j, 0 });
					weight[index++][i][j] = 0;
					map[i][j] = '.';
				}
			}
			map[i][w + 1] = '.';				// ������ �� '.' �߰�
		}
		for (int i = 0; i < w + 2; i++)			// ���� �Ʒ��� �� '.' �߰�
			map[h + 1][i] = '.';

		BFS();
		printf("%d\n", ans);
		ans = MAX;
	}
	return 0;
}