#include "Sword41.h"
#include<queue>
#include<vector>
#include<algorithm>

using std::priority_queue;
using std::vector;
using std::less;
using std::greater;

#pragma region 双向链表
static ListNode* head;
static ListNode* median;

Sword41::Sword41() {
    head = new ListNode(0);
    median = head;
}

void Sword41::addNum(int num) {
    ListNode* pInsertPre = median;
    ListNode* pInsert = median->next;

    if (num > median->val) {
        while (pInsert && pInsert->val < num) {
            pInsertPre = pInsert;
            pInsert = pInsert->next;
        }
    }
    else {
        while (pInsertPre != head && pInsertPre->val >= num) {
            pInsert = pInsertPre;
            pInsertPre = pInsertPre->pre;
        }
    }



    pInsertPre->next = new ListNode(num, pInsert, pInsertPre);
    if (pInsert) {
        pInsert->pre = pInsertPre->next;
    }
    this->count()++;

    if (median == head || median->val < pInsertPre->next->val && this->count() % 2) {
        median = median->next;

    }
    else if (median->val >= pInsertPre->next->val && !(this->count() % 2)) {
        median = median->pre;
    }
}

double Sword41::findMedian() {
    if (!this->count()) {
        return 0.0;
    }

    if (this->count() % 2) {
        return median->val;
    }
    else {
        return (median->val + median->next->val) / 2.0;
    }
}

int& Sword41::count() {
    return head->val;
}
#pragma endregion

/** initialize your data structure here. */
static priority_queue<int, vector<int>, less<int>> smallerHalf;
static priority_queue<int, vector<int>, greater<int>> biggerHalf;

void Sword41::addNum2(int num) {
    if (smallerHalf.empty() || num <= smallerHalf.top())
        smallerHalf.push(num);
    else
        biggerHalf.push(num);
    while (smallerHalf.size() < biggerHalf.size()) {
        smallerHalf.push(biggerHalf.top());
        biggerHalf.pop();
    }
    while (smallerHalf.size() > biggerHalf.size() + 1) {
        biggerHalf.push(smallerHalf.top());
        smallerHalf.pop();
    }
}

double Sword41::findMedian2() {
    auto size = smallerHalf.size() + biggerHalf.size();
    if (size % 2)
        return smallerHalf.top();
    double ans = smallerHalf.top() + biggerHalf.top();
    return ans / 2;
}