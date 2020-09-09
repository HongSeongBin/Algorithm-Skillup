#include <iostream>
using namespace std;

int N, M, map[8][8], check[8][8], cctv, Min = 100;
const int dc[] = { 1, -1, 0, 0 }, dr[] = { 0, 0, 1, -1 };

void Search(int r, int c, int depth, int dir) {			// �Է¹��� dir�� ���� ���ǰ� �ش� depth�� �湮 üũ
	int R = r, C = c;
	while (C >= 0 && C < M && R >= 0 && R < N && map[R][C] != 6) {
		if (!check[R][C])
			check[R][C] = depth + 1;
		R += dr[dir], C += dc[dir];
	}
}

void Rewind(int r, int c, int depth, int dir) {			// �Է¹��� dir�� ���� ���� �� �ش� depth���� ���� ������ �ٽ� ���󺹱�
	int R = r, C = c;
	while (C >= 0 && C < M && R >= 0 && R < N && map[R][C] != 6) {
		if (check[R][C] == depth + 1) 
			check[R][C] = 0;
		R += dr[dir], C += dc[dir];
	}
}

void DFS(int depth, int start_r, int start_c) {
	if (depth == cctv) {								// ��� cctv���� ���� ���ϰ� üũ������ �簢���� ���� �ּڰ� ����
		int sagak = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (!check[i][j] && map[i][j] != 6)
					sagak++;
		Min = sagak < Min ? sagak : Min;
		return;
	}
	for (int i = start_r; i < N; i++) {
		if (i > start_r)
			start_c = 0;
		for (int j = start_c; j < M; j++) {
			if (map[i][j] == 1) {						// 1�� cctv
				for (int d = 0; d < 4; d++) {
					Search(i, j, depth, d);				// �� �������� ���ǰ� DFS
					DFS(depth + 1, i, j + 1);
					Rewind(i, j, depth, d);
				}
			}
			else if (map[i][j] == 2) {					// 2�� cctv
				for (int d = 0; d < 2; d++)				// ���� ���� ���� ���ǰ� DFS
					Search(i, j, depth, d);
				DFS(depth + 1, i, j + 1);
				for (int d = 0; d < 2; d++)
					Rewind(i, j, depth, d);
				for (int d = 2; d < 4; d++)				// �� ���� ���� ���� ���ǰ� DFS
					Search(i, j, depth, d);
				DFS(depth + 1, i, j + 1);
				for (int d = 2; d < 4; d++)
					Rewind(i, j, depth, d);
			}
			else if (map[i][j] == 3) {					// 3�� cctv
				for (int d1 = 0; d1 < 2; d1++) {		// �� �� �� ���⿡ ���ؼ�
					Search(i, j, depth, d1);
					for (int d2 = 2; d2 < 4; d2++) {	// �� �� �������� ���ǰ� DFS
						Search(i, j, depth, d2);
						DFS(depth + 1, i, j + 1);
						Rewind(i, j, depth, d2);
					}
					Rewind(i, j, depth, d1);
				}
			}
			else if (map[i][j] == 4) {					// 4�� cctv
				for (int d1 = 0; d1 < 4; d1++) {
					for (int d2 = 0; d2 < 4; d2++) {	// ������, ������, ������, ������ ������ ���ǰ� DFS
						if (d1 == d2)
							continue;
						Search(i, j, depth, d2);
					}
					DFS(depth + 1, i, j + 1);
					for (int d2 = 0; d2 < 4; d2++) {
						if (d1 == d2)
							continue;
						Rewind(i, j, depth, d2);
					}
				}
			}
			else if (map[i][j] == 5) {					// 5�� cctv
				for (int d = 0; d < 4; d++)
					Search(i, j, depth, d);				// ��� �������� ���ǰ� DFS
				DFS(depth + 1, i, j + 1);
				for (int d = 0; d < 4; d++)
					Rewind(i, j, depth, d);
			}
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] > 0 && map[i][j] < 6)
				cctv++;
		}
	DFS(0, 0, 0);
	cout << Min << endl;
	return 0;
}