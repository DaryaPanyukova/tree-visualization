#include <algorithm>

struct node_AVL {
    int data;
    int height;
    node_AVL* left, * right;
};

node_AVL* root_AVL = nullptr;

bool FindElem(node_AVL* t, int elem) {
    if (t==nullptr) return false;
    if (t->data > elem) return FindElem(t->left, elem);
    if (t->data < elem) return FindElem(t->right, elem);
    if (t->data == elem) return true;
}

int GetHeight(node_AVL* ptr) {
    if (ptr == nullptr) return 0;
    else return ptr->height;
}

void UpdateHeight(node_AVL* ptr) {
    if (ptr == nullptr) return;
    ptr->height = std::max(GetHeight(ptr->right), GetHeight(ptr->left)) + 1;
}

void SimpleLeftRotation(node_AVL* &ptr) {
    node_AVL* new_node = ptr->right;

    ptr->height = GetHeight(ptr->left) + 1;
    UpdateHeight(new_node);
    ptr->right = new_node->left;
    new_node->left = ptr;
    ptr = new_node;
}

void SimpleRightRotation(node_AVL*& ptr) {
    node_AVL* new_node = ptr->left;

    ptr->height = GetHeight(ptr->right) + 1;

    UpdateHeight(new_node);
    ptr->left = new_node->right;
    new_node->right = ptr;
    ptr = new_node;
}


void DoubleLeftRotation(node_AVL*& ptr) {
    node_AVL* q = ptr->right;
    node_AVL* z = q->left;
    ptr->right = z->left;
    q->left = z->right;
    z->left = ptr;
    z->right = q;

    UpdateHeight(q);
    UpdateHeight(ptr);
    UpdateHeight(z);

    ptr = z;
}

void DoubleRightRotation(node_AVL*& ptr) {
    node_AVL* q = ptr->left;
    node_AVL* z = q->right;
    ptr->left = z->right;
    q->right = z->left;
    z->right = ptr;
    z->left = q;

    UpdateHeight(q);
    UpdateHeight(ptr);
    UpdateHeight(z);

    ptr = z;
}

node_AVL* Balance(node_AVL* &ptr) {
    int height_L = GetHeight(ptr->left),
        height_R = GetHeight(ptr->right);
    UpdateHeight(ptr);

    if (height_R - height_L > 1) {
        if (ptr->right == nullptr) {
            SimpleLeftRotation(ptr);
            return ptr;
        }
        int height_l = GetHeight(ptr->right->left),
            height_r = GetHeight(ptr->right->right);
        if (height_r > height_l) {
            SimpleLeftRotation(ptr);
        } else {
            DoubleLeftRotation(ptr);
        }
    } else if (height_L - height_R > 1) {
        if (ptr->left == nullptr) {
            SimpleRightRotation(ptr);
            return ptr;
        }
        int height_l = GetHeight(ptr->left->left),
            height_r = GetHeight(ptr->left->right);
        if (height_r < height_l) {
            SimpleRightRotation(ptr);
        } else {
            DoubleRightRotation(ptr);
        }
    }
    return ptr;
}

void Insert(int elem, node_AVL*& ptr) {
    if (ptr == nullptr) {
        node_AVL* new_node = new node_AVL;
        new_node->data = elem;
        new_node->height = 1;
        new_node->left = nullptr;
        new_node->right = nullptr;
        ptr = new_node;
        return;
    }

    if (ptr->data == elem) return; // !!!!!!!!
    if (ptr->data < elem) {
        Insert(elem, ptr->right);
    } else {
        Insert(elem, ptr->left);
    }
    Balance(ptr);
}


node_AVL* FindMin(node_AVL* ptr)
{
    if (ptr->left == nullptr) return ptr;
    else FindMin(ptr->left);
}

node_AVL* DeleteMin(node_AVL*& ptr) {
    if (ptr->left == nullptr)
        return ptr->right;
    ptr->left = DeleteMin(ptr->left);
    return Balance(ptr);
}

node_AVL* Delete(int elem, node_AVL*& ptr) {
    if (ptr == nullptr) return nullptr; // !!!!!!!!
    else if (elem < ptr->data) {
        ptr->left = Delete(elem, ptr->left);
    } else if (elem > ptr->data) {
        ptr->right = Delete(elem, ptr->right);
    } else {
        if (ptr->right == nullptr) {
            if (ptr == root_AVL) {
                if (ptr->left == nullptr) {
                    root_AVL = nullptr;
                    delete ptr;
                    return nullptr;
                } else {
                    root_AVL = ptr->left;
                    delete ptr;
                    return root_AVL;
                }
            } else {
                delete ptr;
                return nullptr;
            }
        }
        node_AVL* del = FindMin(ptr->right);
        del->right = DeleteMin(ptr->right);
        del->left = ptr->left;

        if (ptr == root_AVL) {
            delete ptr;
            root_AVL = del;
        } else {
            delete ptr;
        }
        return Balance(del);
    }
    Balance(ptr);
}

void DeleteTree(node_AVL* ptr) {
    if (ptr->left != nullptr) DeleteTree(ptr->left);
    if (ptr->right != nullptr) DeleteTree(ptr->right);
    delete ptr;
}
