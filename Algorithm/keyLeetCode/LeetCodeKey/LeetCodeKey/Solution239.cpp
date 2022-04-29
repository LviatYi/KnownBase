#include "Solution239.h"
#include<algorithm>

using std::priority_queue;
using std::pair;

#pragma region 优先队列
struct less {
    bool operator()(pair<int, int> lhs, pair<int, int> rhs) {
        return lhs.first <= rhs.first;
    }
};

vector<int> Solution239::maxSlidingWindow(vector<int>& nums, int k) {
    if (!nums.size()) {
        return {};
    }
    vector<int>ans(nums.size() - k + 1);
    priority_queue < pair<int, int>, vector<pair<int, int>>, less> window;

    for (int i = 0; i < k; i++) {
        window.push({ nums.at(i) ,i });
    }
    ans.at(0) = window.top().first;

    for (int j = k; j < nums.size(); j++) {
        while (!window.empty() && window.top().second <= j - k) {
            window.pop();
        }

        window.push({ nums[j],j });
        ans.at(j - k + 1) = window.top().first;
    }

    return ans;
}
#pragma endregion
#pragma region 单调队列
vector<int> Solution239::maxSlidingWindow2(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> q;
    for (int i = 0; i < k; ++i) {
        while (!q.empty() && nums[i] >= nums[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
    }

    vector<int> ans = { nums[q.front()] };
    for (int i = k; i < n; ++i) {
        while (!q.empty() && nums[i] >= nums[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
        while (q.front() <= i - k) {
            q.pop_front();
        }
        ans.push_back(nums[q.front()]);
    }
    return ans;
}
#pragma endregion