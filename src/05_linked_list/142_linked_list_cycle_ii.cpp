#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                ListNode* index1 = head;
                ListNode* index2 = slow;

                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }

                return index1;
            }
        }

        return nullptr;
    }
};

ListNode* buildListWithCycle(const std::vector<int>& values, int pos) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* curr = head;
    ListNode* cycleEntry = (pos == 0) ? head : nullptr;

    for (size_t i = 1; i < values.size(); ++i) {
        curr->next = new ListNode(values[i]);
        curr = curr->next;
        if (static_cast<int>(i) == pos) {
            cycleEntry = curr;
        }
    }

    if (pos >= 0 && cycleEntry != nullptr) {
        curr->next = cycleEntry;
    }

    return head;
}

void freeCyclicList(ListNode* head, int length) {
    ListNode* curr = head;
    for (int i = 0; i < length && curr != nullptr; ++i) {
        ListNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

int main() {
    Solution solution;
    std::string line;

    std::cout << "head nodes: ";
    if (!std::getline(std::cin, line) || line.empty()) return 0;

    std::stringstream ss(line);
    std::vector<int> values;
    int val = 0;
    while (ss >> val) {
        values.push_back(val);
    }

    std::cout << "pos: ";
    int pos = -1;
    if (!(std::cin >> pos)) return 0;

    ListNode* head = buildListWithCycle(values, pos);
    ListNode* entryNode = solution.detectCycle(head);

    if (entryNode != nullptr) {
        std::cout << "结果: 尾部连接到索引为 " << pos
            << " 的节点，值为 " << entryNode->val << std::endl;
    }
    else {
        std::cout << "结果: 无环" << std::endl;
    }

    freeCyclicList(head, static_cast<int>(values.size()));

    return 0;
}