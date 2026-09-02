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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0, head);
        ListNode* curr = &dummy;

        while (curr->next != nullptr) {
            if (curr->next->val == val) {
                ListNode* target = curr->next;
                curr->next = target->next;
                delete target;
            }
            else {
                curr = curr->next;
            }
        }

        return dummy.next;
    }
};

ListNode* buildList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* curr = head;
    for (size_t i = 1; i < values.size(); ++i) {
        curr->next = new ListNode(values[i]);
        curr = curr->next;
    }
    return head;
}

void printList(const ListNode* head) {
    const ListNode* curr = head;
    while (curr != nullptr) {
        std::cout << curr->val << (curr->next ? " -> " : "");
        curr = curr->next;
    }
    std::cout << std::endl;
}

void freeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
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

    std::cout << "val: ";
    int targetVal = 0;
    if (!(std::cin >> targetVal)) return 0;

    ListNode* head = buildList(values);
    ListNode* newHead = solution.removeElements(head, targetVal);

    std::cout << "result: ";
    printList(newHead);

    freeList(newHead);

    return 0;
}