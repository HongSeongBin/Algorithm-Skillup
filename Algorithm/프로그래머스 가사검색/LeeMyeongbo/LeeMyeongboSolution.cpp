#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

vector<string> words, queries;
string str;

struct Trie {
    Trie* nextNode[26];             // �ڽ� ��� ����Ű�� �����͵��� �迭
    vector<pair<int, int>> list;    // �ܾ� ���̿� ���� ���� ���� ���� (�� �ܾ��� ����, ����)
    int depth;                      // Ʈ���̿����� �� ����� ����

    Trie(int depth) {
        fill(nextNode, nextNode + 26, nullptr);
        this->depth = depth;
    }

    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (nextNode[i]) {
                delete nextNode[i];
                nextNode[i] = nullptr;
            }
    }

    void insert(string word) {
        int index = 0;
        Trie* node = this;

        while (index < word.size()) {
            bool isadded = false;
            int nextkey = word[index++] - 'a';                  // 'a'��� 0�� index, 'b'��� 1�� index... �̷������� ����
            if (!node->nextNode[nextkey])
                node->nextNode[nextkey] = new Trie(index);      // �� ����� �ش� index�� �ڽ� ��尡 ���ٸ� ����
            for (int i = 0; i < node->list.size(); i++) {
                if (node->list[i].first == word.size()) {       // �̹� ���� ������ �ܾ list ���Ϳ� ����Ǿ� �ִٸ�
                    node->list[i].second++;                     // 2��° ���� ������ ����
                    isadded = true;
                    break;
                }
            }
            if (!isadded)                                       // ���� ������ �ܾ ���� ��� list ���Ϳ� ������ ���� ����
                node->list.push_back(make_pair(word.size(), 1));
            node = node->nextNode[nextkey];
        }
    }
};

int search(Trie* t, string query) {
    while (query[t->depth] != '?' && t)                // �� Trie�� root�κ��� ?�� �����ų� nullptr�� ���� ������ �˸´� �ڽ� ��带 ã�� ������
        t = t->nextNode[query[t->depth] - 'a'];
    if (t) {
        for (int i = 0; i < t->list.size(); i++)
            if (t->list[i].first == query.size())      // ?�� ���� ������ list ���� ���� ������ ���ʷ� ���켭 first�� query ���̿� ������ ���� ���� 
                return t->list[i].second;
    }
    return 0;
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    Trie* trie = new Trie(0);                           // �ܾ� ����� Trie
    Trie* rtrie = new Trie(0);                          // �Ųٷ� ������ �ܾ� ����� Trie

    for (auto w : words) {
        trie->insert(w);
        reverse(w.begin(), w.end());
        rtrie->insert(w);
    }

    for (auto query : queries) {
        int ans;
        if (query[query.size() - 1] == '?')                      // ���̾ ?�� ��� trie���� �ܾ� �˻�
            ans = search(trie, query);
        else {                                                   // ���ξ ?�� ��� rtrie���� �ܾ� �˻�
            reverse(query.begin(), query.end());
            ans = search(rtrie, query);
        }
        answer.push_back(ans);
    }

    delete trie;
    delete rtrie;
    return answer;
}