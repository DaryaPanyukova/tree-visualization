#include <iostream>

struct node_Treap {
    long long key, p;
    node_Treap* left, * right;

    node_Treap() {
        left = nullptr;
        right = nullptr;
    }
};

struct triple {
    node_Treap* left, * middle, * right;
    triple(node_Treap* a, node_Treap* b, node_Treap* c) {
        left = a;
        middle = b;
        right = c;
    }
};

node_Treap* root_Treap = nullptr;

bool FindElem(node_Treap* t, int elem) {
    if (t == nullptr) return false;
    if (t->key > elem) return FindElem(t->left, elem);
    if (t->key < elem) return FindElem(t->right, elem);
    if (t->key == elem) return true;
}

triple Split(node_Treap* treap, long long elem) {
    if (treap == nullptr) {
        triple ans(nullptr, nullptr, nullptr);
        return ans;
    }

    if (treap->key < elem) {
        triple s = Split(treap->right, elem);
        treap->right = s.left;
        s.left = treap;
        return s;
    }
    if (treap->key > elem) {
        triple s = Split(treap->left, elem);
        treap->left = s.right;
        s.right = treap;
        return s;
    }

    node_Treap* left = treap->left;
    node_Treap* right = treap->right;
    treap->left = nullptr;
    treap->right = nullptr;

    triple ans(left, treap, right);
    return ans;
}

node_Treap* Merge(node_Treap* treap_1_, node_Treap* treap_2_) {
    if (treap_1_ == nullptr) return treap_2_;
    if (treap_2_ == nullptr) return treap_1_;
    if (treap_1_->p > treap_2_->p) {
        treap_1_->right = Merge(treap_1_->right, treap_2_);
        return treap_1_;
    }

    treap_2_->left = Merge(treap_1_, treap_2_->left);
    return treap_2_;
}

void Insert(long long elem, node_Treap* &treap) {
    triple res = Split(treap, elem);
    if (res.middle != nullptr) {
        treap = Merge(Merge(res.left, res.middle), res.right);
        return;
    }
    node_Treap* new_treap = new node_Treap;
    new_treap->key = elem;
    new_treap->p = rand();
    treap = Merge(Merge(res.left, new_treap), res.right);
}

int GetHeight(node_Treap* treap) {
    if (treap == nullptr) return 0;
    return std::max(GetHeight(treap->left), GetHeight(treap->right))+1;
}

void Delete(int key, node_Treap* &t) {
    triple res = Split(t, key);
    delete res.middle;
    root_Treap = Merge(res.left, res.right);
}

void DeleteTree(node_Treap* ptr) {
    if (ptr->left != nullptr) DeleteTree(ptr->left);
    if (ptr->right != nullptr) DeleteTree(ptr->right);
    delete ptr;
}
