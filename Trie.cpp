#include <bits/stdc++.h> 
using namespace std;

struct Node {
    Node* links[26];
    bool flag = false;

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    void setEnd() {
        flag = true;
    }

    bool isEnd() {
        return flag;
    }
};

class Trie {
private:
    Node* root;
public:
    Trie() {
        root = new Node();
    }

    void insert(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
        }
        node->setEnd();
    }

    bool checkifprefixexists(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (node->containsKey(word[i])) {
                node = node->get(word[i]);
                if (!node->isEnd()) {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }
};

string completeString(int n, vector<string>& a) {
    Trie trie;
    for (auto& it : a) {
        trie.insert(it);
    }
    string ans = "";
    for (auto& it : a) {
        if (trie.checkifprefixexists(it)) {
            if (it.size() > ans.size() || (it.size() == ans.size() && it < ans)) {
                ans = it;
            }
        }
    }
    if (ans == "") {
        return "None";
    }
    return ans;
}