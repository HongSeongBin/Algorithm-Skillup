#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool visited[8];
int user_size, banned_size, answer;
vector<int> visited_strings;            // ã�� ���ڿ����� index�� ��Ʈ ����(���� ����Ʈ)�� ���� ����Ͽ� ����

void DFS(int depth, vector<string>& user_id, vector<string>& banned_id) {
    if (depth == banned_size) {         // �ҷ� ����ڵ��� id�� ��ġ�Ǵ� ����ڵ��� id�� ��� ã���� ���
        int n = 0;
        for (int i = 0; i < 8; i++)
            if (visited[i])
                n += 1 << i;
        for (int num : visited_strings)
            if (num == n)               // �̹� �ش� ����ڵ��� ã�Ƴ� ���� ���� ��� �ٷ� ����
                return;
        answer++;
        visited_strings.push_back(n);   // �׷��� �ʴٸ� answer 1 ������Ű�� ����� ��Ʈ ���갪�� ����
        return;
    }

    for (int i = 0; i < user_size; i++) {
        bool matched = true;
        if (!visited[i] && user_id[i].length() == banned_id[depth].length()) {
            int length = user_id[i].length();
            for (int j = 0; j < length; j++) {          // �� ���ھ� ���� ���� ��ġ�� �� Ȯ��
                if (banned_id[depth][j] == '*')
                    continue;
                if (banned_id[depth][j] != user_id[i][j]) {
                    matched = false;
                    break;
                }
            }
            if (matched) {                              // ��ġ�ϴٸ� �� ���� �ҷ� ����� id ������ �� üũ
                visited[i] = true;
                DFS(depth + 1, user_id, banned_id);
                visited[i] = false;
            }
        }
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    user_size = user_id.size();
    banned_size = banned_id.size();
    DFS(0, user_id, banned_id);
    return answer;
}