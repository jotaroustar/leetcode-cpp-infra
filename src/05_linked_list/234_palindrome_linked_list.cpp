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
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* head2 = reverseList(slow->next);
        ListNode* p1 = head;
        ListNode* p2 = head2;

        bool result = true;
        while (result && p2 != nullptr) {
            if (p1->val != p2->val) {
                result = false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        slow->next = reverseList(head2);
        return result;
    }

private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        return prev;
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

    ListNode* head = buildList(values);
    bool ans = solution.isPalindrome(head);

    std::cout << "result: " << (ans ? "true" : "false") << std::endl;

    freeList(head);

    return 0;
}