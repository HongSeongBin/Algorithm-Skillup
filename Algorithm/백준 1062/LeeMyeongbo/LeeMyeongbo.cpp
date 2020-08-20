#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N, K, words[50], ans;			// words : �ܾ�� ���� ���ԵǾ� �ִ� ���ĺ� ����ġ ����
bool used[26], total[26];			// used : �Է¹��� �ܾ ���ԵǾ� �ִ� ���ĺ� üũ, total : ��ü �ܾ ���Ե� ���ĺ� üũ
string word;

void DFS(int depth, int start, int weight) {
	if (depth == K) {
		int temp = 0;
		for (int i = 0; i < N; i++) {
			if ((words[i] & weight) == words[i])
				temp++;
		}
		ans = temp > ans ? temp : ans;
		return;
	}
	for (int i = start; i < 26; i++) {
		if (total[i])
			DFS(depth + 1, i + 1, weight + (1 << i));		// �ش� �ܾ ���Ǿ��� �� DFS ����
	}
}

int main() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> word;
		for (unsigned int j = 0; j < word.size(); j++) {
			used[word[j] - 'a'] = true;			// 'a'�̸� [0]��, 'b'�� [1]��, 'c'�� [2]�� true üũ �ϴ� ��
			total[word[j] - 'a'] = true;
		}
		for (int j = 0; j < 26; j++)
			if (used[j])
				words[i] += 1 << j;				// �ش� �ܾ 'a'�� �־��ٸ� 1, 'b'�� �־��ٸ� 2 'c'�� �־��ٸ� 4... �̷��� ���ذ�
		memset(used, false, sizeof(used));		// used �ʱ�ȭ
	}
	int cnt = 0;
	for (int i = 0; i < 26; i++)
		if (total[i])
			cnt++;								// ��ü �ܾ ���� ���ĺ� ���� üũ
	if (K >= cnt)
		printf("%d", N);						// K�� �� �̻��̶�� �� �� �ʿ� ���� ��� �ܾ ���� �� �ִ� ��
	else {
		DFS(0, 0, 0);							// �װ� �ƴϸ� ���� ������� K�� ��ŭ �̾Ƽ� ���� �� �ִ� �ִ� �ܾ� �� ����
		cout << ans;
	}
	return 0;
}