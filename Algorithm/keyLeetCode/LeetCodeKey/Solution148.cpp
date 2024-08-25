#include "Solution148.h"

#pragma region 自顶向下 归并

ListNode* Solution148::sortList(ListNode* head) {
    return sortList(head, nullptr);
}

ListNode* Solution148::sortList(ListNode* head, ListNode* tail) {
    if (head == nullptr) {
        return head;
    }
    if (head->next == tail) {
        head->next = nullptr;
        return head;
    }
    ListNode *slow = head, *fast = head;
    while (fast != tail) {
        slow = slow->next;
        fast = fast->next;
        if (fast != tail) {
            fast = fast->next;
        }
    }
    ListNode* mid = slow;
    return merge(sortList(head, mid), sortList(mid, tail));
}

ListNode* Solution148::merge(ListNode* head1, ListNode* head2) {
    ListNode* dummyHead = new ListNode(0);
    ListNode *temp = dummyHead, *temp1 = head1, *temp2 = head2;
    while (temp1 != nullptr && temp2 != nullptr) {
        if (temp1->val <= temp2->val) {
            temp->next = temp1;
            temp1 = temp1->next;
        }
        else {
            temp->next = temp2;
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    if (temp1 != nullptr) {
        temp->next = temp1;
    }
    else if (temp2 != nullptr) {
        temp->next = temp2;
    }
    return dummyHead->next;
}

#pragma endregion

#pragma region 自底向上 归并

ListNode* Solution148::sortList2(ListNode* head) {
    if (head == nullptr) {
        return head;
    }
    int length = 0;
    ListNode* node = head;
    while (node != nullptr) {
        length++;
        node = node->next;
    }
    ListNode* dummyHead = new ListNode(0, head);
    for (int subLength = 1; subLength < length; subLength <<= 1) {
        ListNode *prev = dummyHead, *curr = dummyHead->next;
        while (curr != nullptr) {
            ListNode* head1 = curr;
            for (int i = 1; i < subLength && curr->next != nullptr; i++) {
                curr = curr->next;
            }
            ListNode* head2 = curr->next;
            curr->next = nullptr;
            curr = head2;
            for (int i = 1; i < subLength && curr != nullptr && curr->next != nullptr; i++) {
                curr = curr->next;
            }
            ListNode* next = nullptr;
            if (curr != nullptr) {
                next = curr->next;
                curr->next = nullptr;
            }
            ListNode* merged = merge(head1, head2);
            prev->next = merged;
            while (prev->next != nullptr) {
                prev = prev->next;
            }
            curr = next;
        }
    }
    return dummyHead->next;
}

#pragma endregion
