#include <iostream>

struct node_Splay {
    int data;
    // int height; // координаты
    node_Splay* parent;
    node_Splay* left, * right;
};

node_Splay* root_Splay = nullptr;

bool FindElem(node_Splay* t, int elem) {
    if (t == nullptr) return false;
    if (t->data > elem) return FindElem(t->left, elem);
    if (t->data < elem) return FindElem(t->right, elem);
    if (t->data == elem) return true;
}

node_Splay* Zig(node_Splay* x) {
    node_Splay* y = x->parent;
    root_Splay = x;
    x->parent = nullptr;
    y->parent = x;

    if (y->left == x) {
        y->left = x->right;
        if (y->left != nullptr) {
            y->left->parent = y;
        }
        x->right = y;
    } else {
        y->right = x->left;
        if (x->left != nullptr) {
            x->left->parent = y;
        }
        x->left = y;
    }
    return x;
}

node_Splay* ZigZig(node_Splay* x) {
    node_Splay* y = x->parent;
    node_Splay* z = y->parent;
    if (z == root_Splay) {
        root_Splay = x;
    }
    x->parent = z->parent;
    if (x->parent != nullptr) {
        if (x->parent->left == z) {
            x->parent->left = x;
        } else {
            x->parent->right = x;
        }
    }
    if (y->left == x) {
        y->left = x->right;
        if (y->left != nullptr) {
            y->left->parent = y;
        }
        x->right = y;
        y->parent = x;
        z->left = y->right;
        if (z->left != nullptr) {
            z->left->parent = z;
        }
        y->right = z;
        z->parent = y;
    } else {
        y->right = x->left;
        if (y->right != nullptr) {
            y->right->parent = y;
        }
        x->left = y;
        y->parent = x;
        z->right = y->left;
        if (z->right != nullptr) {
            z->right->parent = z;
        }
        y->left = z;
        z->parent = y;
    }
    return x;
}

node_Splay* ZigZag(node_Splay* x) {
    node_Splay* y = x->parent;
    node_Splay* z = y->parent;

    if (root_Splay == z) {
        root_Splay = x;
    }
    x->parent = z->parent;
    if (x ->parent != nullptr) {
        if (x -> parent ->left == z) {
            x -> parent ->left = x;
        } else {
            x -> parent ->right = x;
        }
    }
    z->parent = x;
    y->parent = x;

    if (y->right == x && z->left == y) {
        z->left = x->right;
        if (z->left != nullptr) {
            z->left->parent = z;
        }
        x->right = z;
        y->right = x->left;
        x->left = y;
        if (y->right != nullptr) {
            y->right->parent = y;
        }
    } else {
        z->right = x->left;
        if (z->right != nullptr) {
            z->right->parent = z;
        }
        x->left = z;
        y->left = x->right;
        x->right = y;
        if (y->left != nullptr) {
            y->left->parent = y;
        }
    }
    return x;
}

node_Splay* Splay(node_Splay* x) {
    if (x->parent == nullptr) return nullptr;
    node_Splay* y = x->parent;
    if (y->parent == nullptr) {
        Zig(x);
        return x;
    }
    node_Splay* z = y->parent;
    if (y->left == x && z->left == y ||
        y->right == x && z->right == y) {
        x = ZigZig(x);
        x = Splay(x);
        return x;
    } else {
        x = ZigZag(x);
        Splay(x);
        return x;
    }
}

void Insert(node_Splay*& ptr, node_Splay* &prev, int elem) {
    if (ptr == nullptr) {
        node_Splay* new_node = new node_Splay;
        new_node -> data = elem;
        new_node -> left = nullptr;
        new_node->right = nullptr;
        new_node->parent = prev;
        ptr = new_node;
        Splay(ptr);
    }
    else {
        if (ptr->data == elem) return;
        if (ptr->data < elem) {
            Insert(ptr->right, ptr, elem);
        } else {
            Insert(ptr->left, ptr, elem);
        }
    }
}

int GetHeight(node_Splay* ptr) {
    if (ptr == nullptr) return 0;
    else return std::max(GetHeight(ptr->left), GetHeight(ptr->right))+1;
}

void DeleteTree(node_Splay* ptr) {
    if (ptr->left != nullptr) DeleteTree(ptr->left);
    if (ptr->right != nullptr) DeleteTree(ptr->right);
    delete ptr;
}

node_Splay* FindMax(node_Splay* ptr) {
    while (ptr!= nullptr && ptr->right != nullptr) {
        ptr = ptr->right;
    }
    return ptr;
}

node_Splay* Merge(node_Splay* left_tree, node_Splay* right_tree) {
    node_Splay* tmp = FindMax(left_tree);
    if (tmp == nullptr) return right_tree;
    Splay(tmp);
    tmp->right = right_tree;
    right_tree->parent = tmp;
    return tmp;
}

void Delete(node_Splay* ptr, int elem) {
    if (ptr == nullptr) return;
    if (ptr->data == elem) {
        Splay(ptr);
        node_Splay* left = ptr->left;
        node_Splay* right = ptr->right;
        if (ptr->left != nullptr) {
            ptr->left->parent = nullptr;
        }
        if (ptr->right != nullptr) {
            ptr->right->parent = nullptr;
        }
        delete ptr;
        root_Splay = Merge(left, right);
    } else if (ptr->data > elem) {
       Delete(ptr->left, elem);
    } else {
        Delete(ptr->right, elem);
    }
}
