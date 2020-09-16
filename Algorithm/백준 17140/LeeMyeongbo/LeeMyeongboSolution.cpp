#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int A[100][100], r, c, k;

int Solve() {
	int cur_row = 3, cur_col = 3;
	vector<pair<int, int>> v;

	for (int a = 0; a <= 100; a++) {
		if (A[r][c] == k)										// ���ϴ� �ڸ��� k�� �ִٸ� �ݺ� Ƚ�� ����
			return a;
		if (cur_row >= cur_col) {								// ���� �� ũ�Ⱑ �� ũ�⺸�� ũ�ų� ���� ��� R ����
			for (int row = 0; row < cur_row; row++) {
				int freq[101] = { 0, };							// �� ���ڰ� ��Ÿ�� �� �� ���� (3�� 2�� ��Ÿ������ freq[3] = 2�� ����Ǵ� ��)
				for (int col = 0; col < cur_col; col++) {
					freq[A[row][col]]++;
					A[row][col] = 0;
				}
				for (int i = 1; i <= 100; i++)
					if (freq[i])
						v.push_back(make_pair(freq[i], i));		// �� �� �̻� ��Ÿ�� �ڿ����� (��, �ش� �ڿ���)�� ���������� ��� ����
				sort(v.begin(), v.end());
				int index = 0;
				for (auto p : v) {								// �� ���ʺ��� �ݺ��ϸ� ���� ä������
					A[row][index++] = p.second;
					if (index == 100)
						break;
					A[row][index++] = p.first;
					if (index == 100)
						break;
				}
				cur_col = max(cur_col, index);					// ���� �� ũ�� �ִ� ����
				v.clear();
			}
		}
		else {													// �� ũ�Ⱑ �� ũ�⺸�� ���� ��� C ����
			for (int col = 0; col < cur_col; col++) {
				int freq[101] = { 0, };
				for (int row = 0; row < cur_row; row++) {
					freq[A[row][col]]++;
					A[row][col] = 0;
				}
				for (int i = 1; i <= 100; i++)
					if (freq[i])
						v.push_back(make_pair(freq[i], i));
				sort(v.begin(), v.end());
				int index = 0;
				for (auto p : v) {								// �� ���ʺ��� �ݺ��ϸ� ���� ä������
					A[index++][col] = p.second;
					if (index == 100)
						break;
					A[index++][col] = p.first;
					if (index == 100)
						break;
				}
				cur_row = max(cur_row, index);					// ���� �� ũ�� �ִ� ����
				v.clear();
			}
		}
	}
	return -1;
}

int main() {
	cin >> r >> c >> k;
	r--, c--;
	for (int i = 0; i < 9; i++)
		cin >> A[i / 3][i % 3];

	cout << Solve();
	return 0;
}