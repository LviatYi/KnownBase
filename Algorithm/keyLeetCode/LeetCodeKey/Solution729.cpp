#include "Solution729.h"

Solution729::Solution729() {
}

bool Solution729::book(int start, int end) {
    auto right = calendar_.upper_bound(start);
    auto left = !calendar_.empty() && right != calendar_.begin()
                    ? --calendar_.upper_bound(start)
                    : calendar_.end();

    if (left != calendar_.end() && left->second > start) {
        return false;
    }
    if (right != calendar_.end() && right->first < end) {
        return false;
    }

    if (left != calendar_.end() && left->second == start) {
        left->second = end;
    }
    else if (right != calendar_.end() && right->first == end) {
        calendar_[start] = right->second;
        calendar_.erase(right);
    }
    else {
        calendar_[start] = end;
    }

    return true;
}

#pragma region 线段树

bool Solution729::query(int start, int end, int l, int r, int idx) {
    if (r < start || end < l) {
        return false;
    }
    /* 如果该区间已被预订，则直接返回 */
    if (lazy_.count(idx)) {
        return true;
    }
    if (start <= l && r <= end) {
        return tree_.count(idx);
    }
    int mid = (l + r) >> 1;
    return query(start, end, l, mid, 2 * idx) ||
        query(start, end, mid + 1, r, 2 * idx + 1);
}

void Solution729::update(int start, int end, int l, int r, int idx) {
    if (r < start || end < l) {
        return;
    }
    if (start <= l && r <= end) {
        tree_.emplace(idx);
        lazy_.emplace(idx);
    }
    else {
        int mid = (l + r) >> 1;
        update(start, end, l, mid, 2 * idx);
        update(start, end, mid + 1, r, 2 * idx + 1);
        tree_.emplace(idx);
        if (lazy_.count(2 * idx) && lazy_.count(2 * idx + 1)) {
            lazy_.emplace(idx);
        }
    }
}

bool Solution729::book2(int start, int end) {
    if (query(start, end - 1, 0, 7, 1)) {
        return false;
    }
    update(start, end - 1, 0, 7, 1);
    return true;
}

#pragma endregion
