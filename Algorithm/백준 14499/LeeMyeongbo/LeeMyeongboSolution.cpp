#include <iostream>
using namespace std;

int N, M, x, y, K, map[20][20], cube[6], order[1000];	// �ֻ��� ����, �Ʒ���, �����ʸ�, ���ʸ�, �ո�, �޸� ��

void moveEast() {		// ����->�����ʸ�, �����ʸ�->�Ʒ���, �Ʒ���->���ʸ�, ���ʸ�->����
	if (y + 1 < M) {
		y++;
		int temp = cube[0];
		cube[0] = cube[3];
		cube[3] = cube[1];
		cube[1] = cube[2];
		cube[2] = temp;
		if (!map[x][y])
			map[x][y] = cube[1];
		else {
			cube[1] = map[x][y];
			map[x][y] = 0;
		}
		printf("%d\n", cube[0]);
	}
}

void moveWest() {		// ����->���ʸ�, ���ʸ�->�Ʒ���, �Ʒ���->�����ʸ�, �����ʸ�->����
	if (y - 1 >= 0) {
		y--;
		int temp = cube[0];
		cube[0] = cube[2];
		cube[2] = cube[1];
		cube[1] = cube[3];
		cube[3] = temp;
		if (!map[x][y])
			map[x][y] = cube[1];
		else {
			cube[1] = map[x][y];
			map[x][y] = 0;
		}
		printf("%d\n", cube[0]);
	}
}

void moveNorth() {		// ����->�޸�, �޸�->�Ʒ���, �Ʒ���->�ո�, �ո�->����
	if (x - 1 >= 0) {
		x--;
		int temp = cube[0];
		cube[0] = cube[4];
		cube[4] = cube[1];
		cube[1] = cube[5];
		cube[5] = temp;
		if (!map[x][y])
			map[x][y] = cube[1];
		else {
			cube[1] = map[x][y];
			map[x][y] = 0;
		}
		printf("%d\n", cube[0]);
	}
}

void moveSouth() {		// ����->�ո�, �ո�->�Ʒ���, �Ʒ���->�޸�, �޸�->����
	if (x + 1 < N) {
		x++;
		int temp = cube[0];
		cube[0] = cube[5];
		cube[5] = cube[1];
		cube[1] = cube[4];
		cube[4] = temp;
		if (!map[x][y])
			map[x][y] = cube[1];
		else {
			cube[1] = map[x][y];
			map[x][y] = 0;
		}
		printf("%d\n", cube[0]);
	}
}

void Solve() {
	for (int i = 0; i < K; i++) {
		switch (order[i]) {
		case 1:
			moveEast();
			break;
		case 2:
			moveWest();
			break;
		case 3:
			moveNorth();
			break;
		default:
			moveSouth();
			break;
		}
	}
}

int main() {
	cin >> N >> M >> x >> y >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	for (int i = 0; i < K; i++)
		cin >> order[i];
	Solve();
	return 0;
}