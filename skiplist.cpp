#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
class SkipList {
    private:
        struct SkipNode
        {
            int key_;
            vector<SkipNode*> forward_;
            SkipNode(int key, int level):key_(key), forward_(level, nullptr){}
        };
        int Randomlevel() {
            int level = 1;
            while (rand() % 2) {
                level++;
            }
            return level > level_ ? level_ : level;
        }
        size_t level_;
        SkipNode* head_;
    public:
        // 1. 构造函数
        SkipList(size_t level = 4):level_(level) {
            head_ = new SkipNode(-1, level);
        }
        // 2. 查询
        bool search(int key) {
            SkipNode* head = head_;
            for (int i = level_ - 1; i >= 0; i--) {
                while (head->forward_[i] != nullptr && head->forward_[i]->key_ < key) {
                    head = head->forward_[i];
                }
                if (head->forward_[i] != nullptr && head->forward_[i]->key_ == key) {
                    return true;
                }
            }
            return false;
        }
        // 3. 添加
        void add(int key) {
            size_t level = Randomlevel();
            SkipNode* node = new SkipNode(key, level);
            SkipNode* head = head_;
            for (int i = level_ - 1; i >= 0; i--) {
                while (head->forward_[i] != nullptr && head->forward_[i]->key_ < key) {
                    head = head->forward_[i];
                }
                if (level > i) {
                    node->forward_[i] = head->forward_[i];
                    head->forward_[i] = node;
                }
            }
        }
        // 4. 删除
        bool erase(int key) {
            SkipNode* head = head_;
            SkipNode* node = nullptr;
            for (int i = level_ - 1; i >= 0; i--) {
                while (head->forward_[i] != nullptr && head->forward_[i]->key_ < key) {
                    head = head->forward_[i];
                }
                if (head->forward_[i] != nullptr && head->forward_[i]->key_ == key) {
                    node = head->forward_[i];
                    head->forward_[i] = node->forward_[i];
                }
            }
            if (node == nullptr) {
                return false;
            }
            else {
                delete node;
                node = nullptr;
                return true;
            }
            return false;
        }
        // 5. 打印
        void printSkipList() {
            for (int i = level_ - 1; i >= 0; i--) {
                SkipNode* head = head_;
                while (head->forward_[i] != nullptr) {
                    if (head->forward_.size() > i) {
                        cout << head->forward_[0]->key_ << "\t";
                    }
                    else {
                        cout << "\t";
                    }
                    head = head->forward_[0];
                }
                cout << endl;
            }
        }
};

int main() {
    SkipList skip_list;
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        skip_list.add(rand() % 100);
    }
    skip_list.printSkipList();
    return 0;
}