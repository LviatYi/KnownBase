#include "Swordii28.h"

#pragma region 递归

Node* Swordii28::subFlatten(Node* head) {
    if (!head) {
        return nullptr;
    }
    Node* p_next = head->next;
    Node* p_child = head->child;
    Node* next_ret = subFlatten(head->next);
    Node* child_ret = subFlatten(head->child);

    if (next_ret && child_ret) {
        head->child = nullptr;
        head->next = p_child;
        p_child->prev = head;
        child_ret->next = p_next;
        p_next->prev = child_ret;
        return next_ret;
    }
    if (child_ret) {
        head->child = nullptr;
        head->next = p_child;
        p_child->prev = head;
        return child_ret;
    }
    if (next_ret) {
        return next_ret;
    }
    return head;
}

Node* Swordii28::flatten(Node* head) {
    subFlatten(head);
    return head;
}

#pragma endregion

#pragma region 非递归
Node* Swordii28::flatten2(Node* head) {
    if (!head) {
        return nullptr;
    }

    Node* p = head;

    for (; p != nullptr; p = p->next) {
        if (!p->child) {
            continue;
        }

        Node* child = p->child;
        Node* next = p->next;

        p->child = nullptr;
        p->next = child;
        child->prev = p;

        Node* last = child;
        while (last->next) {
            last = last->next;
        }

        last->next = next;
        if (next) {
            next->prev = last;
        }
    }

    return head;
}

#pragma endregion
