#include "AvlTree.h"
#include <iostream>

using std::cout;
using std::endl;

/// <summary>
/// 在 subTree 中获取指定值的 TreeNode.
/// </summary>
/// <param name="key">key</param>
/// <param name="subTree">子树</param>
/// <returns></returns>
TreeNode* AvlTree::find(int key, TreeNode* subTree) {
    TreeNode* p = subTree;
    while (p != nullptr) {
        if (p->key == key) {
            return p;
        }
        else if (p->key < key) {
            p = p->right;
        }
        else {
            p = p->left;
        }
    }
    return nullptr;
}
/// <summary>
/// 在 subTree 中获取含有最小 key 的 TreeNode.
/// </summary>
/// <param name="subTree">子树</param>
/// <returns></returns>
TreeNode* AvlTree::findMin(TreeNode* subTree) {
    TreeNode* p = subTree;
    while (p->left != nullptr) {
        p = p->left;
    }
    return p;
}
/// <summary>
/// 在 subTree 中获取含有最大 key 的 TreeNode.
/// </summary>
/// <param name="subTree">子树</param>
/// <returns></returns>
TreeNode* AvlTree::findMax(TreeNode* subTree) {
    TreeNode* p = subTree;
    while (p->right != nullptr) {
        p = p->right;
    }
    return p;
}
/// <summary>
/// 移植子树。使用子树 v 替代子树 u.
/// u 是 Avl 树的子树.
/// </summary>
/// <param name="u">被替代的目标子树</param>
/// <param name="v">替代子树</param>
void AvlTree::transplant(TreeNode* u, TreeNode* v) {
    if (u == nullptr) {
        return;
    }
    if (this->head == u) {
        this->head = v;
    }
    else if (u == u->p->left) {
        u->p->left = v;
    }
    else {
        u->p->right = v;
    }

    if (v) {
        if (v->p) {
            if (v->p->left == v) {
                v->p->left = nullptr;
            }
            else {
                v->p->right = nullptr;
            }
        }
        v->p = u->p;
    }
    return;
}
/// <summary>
/// AVL 树 左单旋转。
/// </summary>
/// <param name="subTree">将发生 LL 旋转的子树。</param>
/// <returns></returns>
void AvlTree::Lrotate(TreeNode* subTree) {
    if (!subTree || !subTree->right) {
        return;
    }

    TreeNode* x = subTree;
    TreeNode* y = subTree->right;

    if (y->left) {
        y->left->p = x;
    }
    x->right = y->left;

    if (x->p) {
        if (x->p->left == x) {
            x->p->left = y;
        }
        else {
            x->p->right = y;
        }
    }
    else {
        this->head = y;
    }
    y->p = x->p;

    x->p = y;
    y->left = x;
}
/// <summary>
/// AVL 树 右单旋转。
/// </summary>
/// <param name="subTree">将发生 RR 旋转的子树。</param>
/// <returns></returns>
void AvlTree::Rrotate(TreeNode* subTree) {
    if (!subTree || !subTree->left) {
        return;
    }

    TreeNode* x = subTree;
    TreeNode* y = subTree->left;

    if (y->right) {
        y->right->p = x;
    }
    x->left = y->right;

    if (x->p) {
        if (x->p->right == x) {
            x->p->right = y;
        }
        else {
            x->p->left = y;
        }
    }
    else {
        this->head = y;
    }
    y->p = x->p;

    x->p = y;
    y->right = x;
}
/// <summary>
/// AVL 树 左右双旋。
/// </summary>
/// <param name="subTree">将发生 LR 旋转的子树。</param>
/// <returns></returns>
void AvlTree::LRrotate(TreeNode* subTree) {
    if (!subTree) {
        return;
    }
    Lrotate(subTree->left);
    Rrotate(subTree);
}
/// <summary>
/// AVL 树 右左双旋。
/// </summary>
/// <param name="subTree">将发生 RL 旋转的子树。</param>
/// <returns></returns>
void AvlTree::RLrotate(TreeNode* subTree) {
    if (!subTree) {
        return;
    }
    Rrotate(subTree->right);
    Lrotate(subTree);
}
/// <summary>
/// 中序遍历子树得到的数组。
/// </summary>
/// <param name="subTree">子树</param>
/// <param name="nums">用于存放的数组容器</param>
/// <returns></returns>
vector<int> AvlTree::inorderWalk(TreeNode* subTree, vector<int>& nums) {
    if (!subTree) {
        return nums;
    }
    inorderWalk(subTree->left, nums);
    nums.push_back(subTree->key);
    inorderWalk(subTree->right, nums);
    return nums;
}
/// <summary>
/// 插入一个新结点。
/// 若存在重复关键字结点则不作为。
/// </summary>
/// <param name="_n">新结点</param>
/// <returns></returns>
TreeNode* AvlTree::insert(TreeNode* _n) {
    if (this->head == nullptr) {
        this->head = _n;
        return this->head;
    }

    TreeNode* x = nullptr;
    TreeNode* y = this->head;

    while (y) {
        x = y;
        if (_n->key < y->key) {
            y = y->left;
        }
        else if (_n->key > y->key) {
            y = y->right;
        }
        else {
            return this->head;
        }
    }

    if (_n->key < x->key) {
        x->left = _n;
    }
    else {
        x->right = _n;
    }
    _n->p = x;

    y = _n;
    int increase = 0;
    while (x != nullptr) {
        if (y == x->left) {
            increase = -1;
        }
        else if (y == x->right) {
            increase = 1;
        }
        x->bf += increase;
        if (!x->bf) {
            break;
        }


        if (x->bf == -2 && y->bf == -1) {
            x->bf = 0;
            y->bf = 0;
            Rrotate(x);
            break;
        }
        if (x->bf == 2 && y->bf == 1) {
            x->bf = 0;
            y->bf = 0;
            Lrotate(x);
            break;
        }
        if (x->bf == -2 && y->bf == 1) {
            if (y->right->bf == -1) {
                y->bf = 0;
                x->bf = 1;
            }
            else if (y->right->bf == 1) {
                y->bf = -1;
                x->bf = 0;
            }
            else {
                y->bf = 0;
                x->bf = 0;
            }
            y->right->bf = 0;
            LRrotate(x);
            y = y->p;
            break;
        }
        if (x->bf == 2 && y->bf == -1) {
            if (y->left->bf == -1) {
                y->bf = 1;
                x->bf = 0;
            }
            else if (y->left->bf == 1) {
                y->bf = 0;
                x->bf = -1;
            }
            else {
                y->bf = 0;
                x->bf = 0;
            }
            y->left->bf = 0;
            RLrotate(x);
            y = y->p;
            break;
        }
        y = x;
        x = x->p;
    }
    if (!y->p) {
        this->head = y;
    }

    return this->head;
}

/// <summary>
/// 获取指定值的 TreeNode.
/// </summary>
/// <param name="key">key 值</param>
/// <returns></returns>
TreeNode* AvlTree::find(int key) {
    return find(key, this->head);
}
/// <summary>
/// 在 subTree 中获取含有最小 key 的 TreeNode.
/// </summary>
/// <param name="subTree">子树</param>
/// <returns></returns>
TreeNode* AvlTree::findMin() {
    return this->findMin(this->head);
}
/// <summary>
/// 在 subTree 中获取含有最大 key 的 TreeNode.
/// </summary>
/// <param name="subTree">子树</param>
/// <returns></returns>
TreeNode* AvlTree::findMax() {
    return this->findMax(this->head);
}

/// <summary>
/// 插入新结点。
/// 若存在重复关键字结点则不作为。
/// </summary>
/// <param name="_key">key</param>
/// <returns></returns>
AvlTree& AvlTree::insert(int _key) {
    this->insert(new TreeNode(_key));
    return *this;
}
/// <summary>
/// 插入多个新结点。
/// 若存在重复关键字结点则不作为。
/// </summary>
/// <param name="keys">keys</param>
/// <returns></returns>
AvlTree& AvlTree::insert(vector<int> keys) {
    for (int n : keys) {
        this->insert(n);
    }
    return *this;
}
/// <summary>
/// 删除已存在的结点。
/// 若无目标结点则不作为。
/// </summary>
/// <param name="_key">key</param>
/// <returns></returns>
AvlTree& AvlTree::drop(int _key) {
    TreeNode* d = this->find(_key);
    if (!d) {
        return *this;
    }

    TreeNode* x = nullptr;
    TreeNode* y = nullptr;
    if (!d->left) {
        x = d->p;
        if (x) {
            if (d == x->left) {
                x->bf++;
            }
            else {
                x->bf--;
            }
        }
        transplant(d, d->right);
    }
    else if (!d->right) {
        x = d->p;
        if (x) {
            if (d == x->left) {
                x->bf++;
            }
            else {
                x->bf--;
            }
        }
        transplant(d, d->left);
    }
    else {
        TreeNode* r = findMin(d->right);

        if (d->right == r) {
            transplant(d, r);
            r->left = d->left;
            if (d->left) {
                d->left->p = r;
            }
            r->bf = d->bf - 1;
            x = r;
        }
        else {
            r->bf = d->bf;
            x = r->p;
            x->bf++;
            if (r->right) {
                r->right->p = r->p;
            }
            r->p->left = r->right;
            r->right = nullptr;
            r->p = nullptr;

            if (d->left) {
                d->left->p = r;
            }
            r->left = d->left;

            if (d->right) {
                d->right->p = r;
            }
            r->right = d->right;

            if (d->p) {
                if (d->p->left == d) {
                    d->p->left = r;
                }
                else {
                    d->p->right = r;
                }
            }
            else {
                this->head = r;
            }
            r->p = d->p;
        }
    }

    while (x != nullptr) {
        if (x->bf == 2) {
            if (x->right->bf == -1) {
                if (x->right->left->bf == -1) {
                    x->right->bf = 1;
                    x->bf = 0;
                }
                else if (x->right->left->bf == 1) {
                    x->right->bf = 0;
                    x->bf = -1;
                }
                else {
                    x->right->bf = 0;
                    x->bf = 0;
                }
                x->right->left->bf = 0;
                RLrotate(x);
                x = x->p;
            }
            else {
                x->bf = x->right->bf == 1 ? 0 : 1;
                x->right->bf = x->right->bf == 1 ? 0 : -1;
                Lrotate(x);
                x = x->p;
            }
        }
        else if (x->bf == -2) {
            if (x->left->bf == 1) {
                if (x->left->right->bf == -1) {
                    x->left->bf = 0;
                    x->bf = 1;
                }
                else if (x->left->right->bf == 1) {
                    x->left->bf = -1;
                    x->bf = 0;
                }
                else {
                    x->left->bf = 0;
                    x->bf = 0;
                }
                x->left->right->bf = 0;
                LRrotate(x);
                x = x->p;
            }
            else {
                x->bf = x->left->bf == 1 ? 0 : -1;
                x->left->bf = x->left->bf == 1 ? 0 : 1;
                Rrotate(x);
                x = x->p;
            }

        }

        if (x->bf == 0 && x->p) {
            if (x == x->p->left) {
                x->p->bf++;
            }
            else {
                x->p->bf--;
            }
        }
        else {
            break;
        }
        y = x;
        x = x->p;
    }

    delete d;
    return *this;
}

/// <summary>
/// 中序遍历子树得到的数组。
/// </summary>
/// <returns></returns>
vector<int> AvlTree::inorderWalk() {
    vector<int> nums;
    inorderWalk(this->head, nums);
    return nums;
}
/// <summary>
/// 输出数组。
/// </summary>
/// <param name="nums"></param>
void AvlTree::show(const vector<int>& nums) {
    for (int n : nums) {
        cout << n << " ";
    }
    cout << endl;
}