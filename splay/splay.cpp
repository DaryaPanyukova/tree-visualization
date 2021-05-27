#include <iostream>
#include <vector>
#include <queue>

using namespace std;


struct node_Splay {
    int data;
    // int height; // координаты
    node_Splay* parent;
    node_Splay* left, * right;
};

node_Splay* root_Splay = nullptr;
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
        x->right = y;
        y->left = x->right;
        if (y->left != nullptr) {
            y->left->parent = y;
        }
    }
    return x;
}

void Splay(node_Splay* x) {
    if (x->parent == nullptr) return;
    node_Splay* y = x->parent;
    if (y->parent == nullptr) {
        Zig(x);
        return;
    } 
    node_Splay* z = y->parent;
    if (y->left == x && z->left == y ||
        y->right == x && z->right == y) {
        x = ZigZig(x);
        Splay(x);
        return;
    } else {
        x = ZigZag(x);
        Splay(x);
        return;
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

int main()
{
    int input;
    std::cin >> input;
    while (input != 0) {
        Insert(root_Splay, root_Splay, input);
        std::cin >> input;
    }
    std::cout << "S";
}