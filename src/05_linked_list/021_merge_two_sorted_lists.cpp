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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            }
            else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        tail->next = (list1 != nullptr) ? list1 : list2;

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

    std::cout << "list1 nodes: ";
    std::vector<int> vals1;
    if (std::getline(std::cin, line) && !line.empty()) {
        std::stringstream ss(line);
        int val = 0;
        while (ss >> val) vals1.push_back(val);
    }

    std::cout << "list2 nodes: ";
    std::vector<int> vals2;
    if (std::getline(std::cin, line) && !line.empty()) {
        std::stringstream ss(line);
        int val = 0;
        while (ss >> val) vals2.push_back(val);
    }

    ListNode* l1 = buildList(vals1);
    ListNode* l2 = buildList(vals2);

    ListNode* mergedHead = solution.mergeTwoLists(l1, l2);

    std::cout << "result: ";
    printList(mergedHead);

    freeList(mergedHead);

    return 0;
}