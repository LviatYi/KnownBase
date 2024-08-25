#include "Swordii31.h"

void Swordii31::update_heat(int key) {
    Swordii31Node* current = map_[key];

    if (current == heat_link_head_->next) return;
    if (lowest_heat_key_ == current->key) {
        lowest_heat_key_ = current->pre->key;
    }

    current->pre->next = current->next;
    if (current->next) {
        current->next->pre = current->pre;
    }

    current->next = heat_link_head_->next;
    current->pre = heat_link_head_;

    heat_link_head_->next->pre = current;
    heat_link_head_->next = current;
}

Swordii31::Swordii31(int capacity) : size_(capacity), lowest_heat_key_(-1), heat_link_head_(new Swordii31Node(-1, -1)) {
}

int Swordii31::get(int key) {
    if (map_.count(key)) {
        update_heat(key);
        return map_[key]->val;
    }
    return -1;
}

void Swordii31::put(int key, int value) {
    if (map_.count(key)) {
        update_heat(key);
        map_[key]->val = value;
    }
    else {
        const auto current = new Swordii31Node(key, value, heat_link_head_->next, heat_link_head_);
        if (lowest_heat_key_ == -1) {
            lowest_heat_key_ = key;
        }

        map_[key] = current;
        if (heat_link_head_->next) {
            heat_link_head_->next->pre = current;
        }
        heat_link_head_->next = current;

        if (size_ > 0) {
            --size_;
        }
        else {
            Swordii31Node* rubbish = map_[lowest_heat_key_];
            if (rubbish) {
                rubbish->pre->next = nullptr;
                map_.erase(lowest_heat_key_);
                lowest_heat_key_ = rubbish->pre->key;
                delete rubbish;
            }
        }
    }
}
