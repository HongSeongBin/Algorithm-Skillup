#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> heights;
int N, height[50][50], K_num, py, px, dx[] = { 1, 1, 1, 0, -1, -1, -1, 0 }, dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 }, h_num;
char map[50][50];
bool existing_heights[1000001], complete;

bool DFS(int cur_row, int cur_col, int right, int left, bool visited[][50]) {
	if (h_num == K_num) {
		complete = true;
		return complete;
	}
	for (int i = 0; i < 8; i++) {
		int X = cur_col + dx[i];
		int Y = cur_row + dy[i];
		if (X >= 0 && X < N && Y >= 0 && Y < N && !visited[Y][X] && height[Y][X] >= heights[left] && height[Y][X] <= heights[right]) {
			visited[Y][X] = true;
			if (map[Y][X] == 'K')
				h_num++;			// K ������ �� ������ �湮�� K ���� ����
			DFS(Y, X, right, left, visited);
		}
	}
	return complete;
}

int Solve() {
	int ans = 5000000, left = 0, right = 0;
	bool visited[50][50];
	while (right < heights.size()) {
		if (height[py][px] >= heights[left] && height[py][px] <= heights[right]) {		// P�� ���� left - right ������ ���� ���
			memset(visited, false, sizeof(visited));
			visited[py][px] = true;
			if (DFS(py, px, right, left, visited)) {	// DFS �� left - right ���� �� �� �� �ִ� ��� �� Ž���ϰ� ��� K �湮 ��
				ans = heights[right] - heights[left] < ans ? heights[right] - heights[left] : ans;
				complete = false;
				left++;			// left ���������� �� ĭ ������ ���� ����
			}
			else				// ��� K �湮������ ������ ��
				right++;		// right ���������� �� ĭ ������ ���� ����
			h_num = 0;			// �湮�� K ���� �ʱ�ȭ
		}
		else if (height[py][px] > heights[right])		// P�� ���� left - right ������ ���� ������ ������ ���
			right++;
		else if (height[py][px] < heights[left])		// P�� ���� �̹� left - right ������ �������� ���
			break;
	}
	return ans;
}

int main() {
	cin >> N;
	for(int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'P')
				py = i, px = j;				// P�� ��, �� ��ġ�� ���� py, px�� ����
			else if (map[i][j] == 'K')	
				K_num++;					// K_num�� �� K ���� ����
		}
	for(int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> height[i][j];
			existing_heights[height[i][j]] = true;
		}
	for (int i = 0; i <= 1000000; i++)
		if (existing_heights[i])
			heights.push_back(i);			// heights ���Ϳ� �Է¹��� ��(���� �� �ߺ�x) ������������ ����

	cout << Solve();
	return 0;
}