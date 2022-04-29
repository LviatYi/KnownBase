#include "Solution138.h"
#include <unordered_map>

using std::unordered_map;

static unordered_map<Node*, Node*> map;

Node* Solution138::copyRandomList(Node* head) {
    if (!head) {
        return nullptr;
    }

    if (map.find(head) == map.end()) {
        Node* copyed = new Node(head->val);
        map[head] = copyed;
        copyed->next = copyRandomList(head->next);
        copyed->random = copyRandomList(head->random);
    }
    return map[head];
}