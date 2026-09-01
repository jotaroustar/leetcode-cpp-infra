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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || left == right) {
            return head;
        }

        ListNode dummy(0, head);
        ListNode* prev = &dummy;

        for (int i = 0; i < left - 1; ++i) {
            prev = prev->next;
        }

        ListNode* curr = prev->next;

        for (int i = 0; i < right - left; ++i) {
            ListNode* nextNode = curr->next;
            curr->next = nextNode->next;
            nextNode->next = prev->next;
            prev->next = nextNode;
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

    std::cout << "left: ";
    int left = 1;
    if (!(std::cin >> left)) return 0;

    std::cout << "right: ";
    int right = 1;
    if (!(std::cin >> right)) return 0;

    ListNode* head = buildList(values);
    ListNode* newHead = solution.reverseBetween(head, left, right);

    std::cout << "result: ";
    printList(newHead);

    freeList(newHead);

    return 0;
}