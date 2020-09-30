#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

vector<int> solution(vector<string> gems) {
    set<string> jew;
    map<string, int> tmp;               // key : ���� �̸�(string), value : ����(int)
    vector<pair<int, int>> possible;    // ���� �� �� �ִ� (���� ��ȣ, �� ��ȣ) ���
    vector<int> answer;
    int left = 0, right = 0;

    for (string g : gems)
        jew.insert(g);
    int size = jew.size();              // ��ü ������ �� ���� �ִ��� ��Ƹ�

    while (left <= right && right < (int)gems.size()) {
        if (tmp.size() < size) {                                // map�� ��� ������ ������ ���� ������ ���
            if (tmp.count(gems[right]))                         // right �ڸ��� ������ ���� ������ ��� ������ ����
                tmp[gems[right]]++;
            else
                tmp.insert(make_pair(gems[right], 1));          // �ݴ�� ���� ���� ������ ��� map�� �ش� ������ ����
            right++;                                            // right ���������� �� ĭ �̵�
        }
        else {                                                  // �ݴ�� ��� ���� ������ ���
            possible.push_back(make_pair(left, right - 1));     // ���� ��ȣ(left)�� �� ��ȣ(right - 1)�� ¦��� ����
            tmp[gems[left]]--;                                  // left �ڸ��� ���� ���� 1 ����
            if (!tmp[gems[left]])
                tmp.erase(gems[left]);                          // ������ 0�� �Ǹ� map���� ����
            left++;                                             // left ���������� �� ĭ �̵�
        }
    }
    while (left < right && tmp.size() == size) {                // right�� ������ index�� �Ѿ�� ���� �Ϸᰡ ���� �ʾ��� ���� ���� -> left �Űܰ��� ���� ó��
        possible.push_back(make_pair(left, right - 1));
        tmp[gems[left]]--;
        if (!tmp[gems[left]])
            tmp.erase(gems[left]);
        left++;
    }

    sort(possible.begin(), possible.end());                     // ���� ��ȣ �������� ����
    left = possible[0].first, right = possible[0].second;
    for (auto i : possible) {
        if (i.second - i.first < right - left)
            right = i.second, left = i.first;                   // ������ ���� ª�� ���� ��ȣ, �� ��ȣ�� ����
    }

    answer.push_back(left + 1);
    answer.push_back(right + 1);
    return answer;
}