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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* pA = headA;
        ListNode* pB = headB;

        while (pA != pB) {
            pA = (pA == nullptr) ? headB : pA->next;
            pB = (pB == nullptr) ? headA : pB->next;
        }

        return pA;
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

void freeSharedLists(ListNode* headA, ListNode* headB, ListNode* commonHead) {
    ListNode* curr = headA;
    while (curr != nullptr && curr != commonHead) {
        ListNode* temp = curr;
        curr = curr->next;
        delete temp;
    }

    curr = headB;
    while (curr != nullptr && curr != commonHead) {
        ListNode* temp = curr;
        curr = curr->next;
        delete temp;
    }

    curr = commonHead;
    while (curr != nullptr) {
        ListNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

int main() {
    Solution solution;
    std::string line;

    std::cout << "common nodes (shared tail): ";
    std::vector<int> commonVals;
    if (std::getline(std::cin, line) && !line.empty()) {
        std::stringstream ss(line);
        int val = 0;
        while (ss >> val) commonVals.push_back(val);
    }

    std::cout << "listA prefix: ";
    std::vector<int> aVals;
    if (std::getline(std::cin, line) && !line.empty()) {
        std::stringstream ss(line);
        int val = 0;
        while (ss >> val) aVals.push_back(val);
    }

    std::cout << "listB prefix: ";
    std::vector<int> bVals;
    if (std::getline(std::cin, line) && !line.empty()) {
        std::stringstream ss(line);
        int val = 0;
        while (ss >> val) bVals.push_back(val);
    }

    ListNode* commonHead = buildList(commonVals);
    ListNode* headA = buildList(aVals);
    ListNode* headB = buildList(bVals);

    if (headA != nullptr) {
        ListNode* currA = headA;
        while (currA->next != nullptr) currA = currA->next;
        currA->next = commonHead;
    }
    else {
        headA = commonHead;
    }

    if (headB != nullptr) {
        ListNode* currB = headB;
        while (currB->next != nullptr) currB = currB->next;
        currB->next = commonHead;
    }
    else {
        headB = commonHead;
    }

    ListNode* intersectNode = solution.getIntersectionNode(headA, headB);

    if (intersectNode != nullptr) {
        std::cout << "result: intersected at node with value " << intersectNode->val << std::endl;
    }
    else {
        std::cout << "result: no intersection" << std::endl;
    }

    freeSharedLists(headA, headB, commonHead);

    return 0;
}