#include <algorithm>

const int BLACK = 1;
const int RED = 0;

struct node_RB {
    int data, color; // 1 - черный, 0 - красный
    node_RB* left, * right;
    node_RB* parent;
};


node_RB* root_RB = nullptr;

bool FindElem(node_RB* t, int elem) {
    if (t == nullptr) return false;
    if (t->data > elem) return FindElem(t->left, elem);
    if (t->data < elem) return FindElem(t->right, elem);
    if (t->data == elem) return true;
}

node_RB* GetGrandparent(node_RB* N) {
    if (N->parent != nullptr) return N->parent->parent;
    return nullptr;
}

int GetHeight(node_RB* ptr) {
    if (ptr == nullptr) return 0;
    else return std::max(GetHeight(ptr->left), GetHeight(ptr->right))+1;
}

node_RB* GetSibling(node_RB* N) {
    if (N->parent == nullptr) return nullptr;
    if (N->parent->left == N) return N->parent->right;
    return N->parent->left;
}

node_RB* GetUncle(node_RB* N) {
    node_RB* G = GetGrandparent(N);
    if (G == nullptr) return G;
    if (G->left == N->parent) return G->right;
    return G->left;
}


void InsertionCase1(node_RB* &N) {
    node_RB* P = N->parent;
    node_RB* U = GetUncle(N);
    node_RB* G = GetGrandparent(N);
    G->color = RED;
    P->color = BLACK;
    U->color = BLACK;
}

void RotateRight(node_RB* &N) {
    node_RB* new_node = N->left;

    new_node->parent = N->parent;
    if (N->parent != NULL) {
        if (N->parent->left == N)
            N->parent->left = new_node;
        else
            N->parent->right = new_node;
    }

    N->left = new_node->right;
    if (new_node->right != NULL)
        new_node->right->parent = N;

    N->parent = new_node;
    new_node->right = N;
}


void RotateLeft(node_RB*& N) {
    node_RB* new_node = N->right;

    new_node->parent = N->parent;
    if (N->parent != NULL) {
        if (N->parent->left == N)
            N->parent->left = new_node;
        else
            N->parent->right = new_node;
    }

    N->right = new_node->left;
    if (new_node->left != NULL)
        new_node->left->parent = N;

    N->parent = new_node;
    new_node->left = N;
}

void ChangeColor(node_RB* N) {
    if (N->color == BLACK) N->color = RED;
    else N->color = BLACK;
    return;
}

void InsertionCase2(node_RB*& N) {
    node_RB* P = N->parent;
    node_RB* G = GetGrandparent(N);

    if (G->left == P && P->left == N) {
        RotateRight(G);
    } else {
        RotateLeft(G);
    }
    ChangeColor(P);
    ChangeColor(G);
    return;
}

void InsertionCase3(node_RB*& N) {
    node_RB* P = N->parent;
    node_RB* U = GetUncle(N);
    node_RB* G = GetGrandparent(N);

    if (G->left == P && P->right == N) {
        RotateLeft(P);
    } else {
        RotateRight(P);
    }
    InsertionCase2(P);
    return;
}

void ReDraw(node_RB*& N) {
    if (N->parent == nullptr) {
        N->color = BLACK;
        return;
    }

    node_RB* P = N->parent;
    if (P->color != N->color) return;

    node_RB* U = GetUncle(N);
    node_RB* G = GetGrandparent(N);

    if (U != nullptr && U->color == RED) {
        InsertionCase1(N);
        ReDraw(G);
    }

    else if (G->left == P && P->left == N ||
        G->right == P && P->right == N) {
        InsertionCase2(N);
        return;
    } else  {
        InsertionCase3(N);
        return;
    }
}

node_RB* InsertNode(int elem, node_RB* &parent, node_RB* &ptr) {
    if (ptr == nullptr) {
        node_RB* new_node = new node_RB;
        new_node->data = elem;
        new_node->left = nullptr;
        new_node->right = nullptr;
        new_node->color = RED;
        new_node->parent = parent;
        ptr = new_node;

        return ptr;
    }

    if (ptr->data == elem) return nullptr; // !!!!!!!!
    if (ptr->data < elem) {
        return InsertNode(elem, ptr, ptr->right);
    } else {
        return InsertNode(elem, ptr, ptr->left);
    }
}

void UpdateRoot(node_RB*& ptr) {
    while (ptr != nullptr && ptr->parent != nullptr)
        ptr = ptr->parent;
}

void Insert(int elem, node_RB*& parent, node_RB*& ptr) {
    node_RB* new_node = InsertNode(elem, parent, ptr);
    ReDraw(new_node);
    UpdateRoot(ptr);
    return;
}

node_RB* FindMax(node_RB* ptr)
{
    if (ptr->right == nullptr) return ptr;
    else FindMax(ptr->right);
}

node_RB* FindElem(int elem, node_RB* ptr) {
    if (ptr == nullptr) return nullptr; // !!!!
    if (ptr->data < elem) {
        return FindElem(elem, ptr->right);
    } else if (ptr->data > elem) {
        return FindElem(elem, ptr->left);
    } else {
        return ptr;
    }
}

void DeleteModification(node_RB* &N) {
    if (N->parent == nullptr) return; // случай 1
    node_RB* P = N->parent;
    node_RB* S = GetSibling(N);

    if (P->color == BLACK && S->color == BLACK &&
        (S->left == nullptr || S->left->color == BLACK) &&
        (S->right == nullptr || S->right->color == BLACK)) { // случай 2
        S->color = RED;
        DeleteModification(P);
    } else if (P->color == RED &&
        (S->left == nullptr || S->left->color == BLACK) &&
        (S->right == nullptr || S->right->color == BLACK)) { // случай 3
        ChangeColor(S);
        ChangeColor(P);
        return;
    } else if (S->color == BLACK && S == P->right &&
        S->right != nullptr && S->right->color == RED) { // случай 4.1
        S->color = P->color;
        P->color = BLACK;
        S->right->color = BLACK;
        RotateLeft(P);
        return;
    } else if (S->color == BLACK && S == P->left &&
            S->left != nullptr && S->left->color == RED) { // случай 4.2
        S->color = P->color;
        P->color = BLACK;
        S->left->color = BLACK;
        RotateRight(P);
        return;
    } else if (S->color == BLACK && S == P->right && N->color == BLACK
        && (S->right == nullptr || S->right->color == BLACK) &&
        S->left != nullptr && S->left->color == RED) { // случай 5.1
        ChangeColor(S);
        ChangeColor(S->left);
        RotateRight(S);
        DeleteModification(N);
    } else if (S->color == BLACK && S == P->left && N->color == BLACK
        && (S->left == nullptr || S->left->color == BLACK) &&
        S->right != nullptr && S->right->color == RED) { // случай 5.2
        ChangeColor(S);
        ChangeColor(S->right);
        RotateLeft(S);
        DeleteModification(N);
    } else if (S->color == RED) {
        ChangeColor(P);
        ChangeColor(S);
        if (N == P->left) { // 6.1
            RotateLeft(P);
        } else { // 6.2
            RotateRight(P);
        }
        DeleteModification(N);
    }
}

void Delete(int elem, node_RB*& ptr) {
    node_RB* ptr_elem = FindElem(elem, ptr); // если ptr_elem - nullptr, то такого элемента нет+может что-то сломаться
    node_RB* ptr_delete;
    if (ptr_elem->left == nullptr) {
        ptr_delete = ptr_elem;
    } else {
        ptr_delete = FindMax(ptr_elem->left);
    }
    ptr_elem->data = ptr_delete->data;



    if (ptr_delete != ptr_elem) {
        ptr_elem->data = ptr_delete->data;
    }

    if (ptr_delete->right) {
        if (ptr_delete == ptr) {
            ptr = ptr_delete->right;
            ptr_delete->right->parent = nullptr;
        } else {
            if (ptr_delete->parent->left == ptr_delete) {
                ptr_delete->parent->left = ptr_delete->right;
            } else {
                ptr_delete->parent->right = ptr_delete->right;
            }
            ptr_delete->right->parent = ptr_delete->parent;
        }
        delete ptr_delete;
        ptr->color = BLACK;
    } else if (ptr_delete->left) {
        if (ptr_delete == ptr) {
            ptr = ptr_delete->left;
            ptr_delete->left->parent = nullptr;
        } else {
            if (ptr_delete->parent->left == ptr_delete) {
                ptr_delete->parent->left = ptr_delete->left;
            } else {
                ptr_delete->parent->right = ptr_delete->left;
            }
            ptr_delete->left->parent = ptr_delete->parent;
        }
        delete ptr_delete;
        ptr->color = BLACK;
    } else {
        if (ptr_delete->color == RED) {
            if (ptr_delete->parent) {
                if (ptr_delete->parent->left == ptr_delete) ptr_delete->parent->left = nullptr;
                else ptr_delete->parent->right = nullptr;
            }
            delete ptr_delete;
        } else {

            DeleteModification(ptr_delete);
            if (ptr_delete->parent) {
                if (ptr_delete->parent->left == ptr_delete) {
                    ptr_delete->parent->left = nullptr;
                } else {
                    ptr_delete->parent->right = nullptr;
                }
            }
            if (ptr_delete == ptr) ptr=nullptr;
            delete ptr_delete;
        }
    }
    UpdateRoot(ptr);
}

void DeleteTree(node_RB* ptr) {
    if (ptr->left != nullptr) DeleteTree(ptr->left);
    if (ptr->right != nullptr) DeleteTree(ptr->right);
    delete ptr;
}


