#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) {
        this->data = data;
        color = RED;  // New nodes are initially red
        left = right = parent = nullptr;
    }
};

class RedBlackTree {
private:
    Node *root;

    // Helper functions for insertion
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixViolation(Node *&);

public:
    RedBlackTree() { root = nullptr; }
    void insert(int);
    void inorderTraversal();
    void inorderHelper(Node *);
};
    
void RedBlackTree::rotateLeft(Node *&ptr) {
    Node *rightChild = ptr->right;
    ptr->right = rightChild->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    rightChild->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = rightChild;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = rightChild;
    else
        ptr->parent->right = rightChild;

    rightChild->left = ptr;
    ptr->parent = rightChild;
}

void RedBlackTree::rotateRight(Node *&ptr) {
    Node *leftChild = ptr->left;
    ptr->left = leftChild->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;    

    leftChild->parent = ptr->parent;    

    if (ptr->parent == nullptr)
        root = leftChild;
    else if (ptr == ptr->parent->right)

        ptr->parent->right = leftChild;
    else
        ptr->parent->left = leftChild;

    leftChild->right = ptr;    
    ptr->parent = leftChild;
}

void RedBlackTree::insert(int data) {
    Node *newNode = new Node(data);
    if (root == nullptr) {
        newNode->color = BLACK;
        root = newNode;
    } else {
        Node *temp = root;
        Node *parent = nullptr;

        while (temp != nullptr) {
            parent = temp;
            if (newNode->data < temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }

        newNode->parent = parent;
        if (newNode->data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        fixViolation(newNode);  // Fix Red-Black properties
    }
}


void RedBlackTree::fixViolation(Node *&newNode) {
    while (newNode->parent && newNode->parent->color == RED) {
        Node *grandparent = newNode->parent->parent;

        if (newNode->parent == grandparent->left) {  // Parent is left child
            Node *uncle = grandparent->right;

            if (uncle && uncle->color == RED) {  // Case 1: Uncle is red
                grandparent->color = RED;
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == newNode->parent->right) {  // Case 2: Triangle
                    newNode = newNode->parent;
                    rotateLeft(newNode);
                }
                // Case 3: Line
                newNode->parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(grandparent);
            }
        } else {  // Parent is right child (mirror cases)
            Node *uncle = grandparent->left;

            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    rotateRight(newNode);
                }
                newNode->parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(grandparent);
            }
        }
    }
    root->color = BLACK;  // Root must always be black
}


void RedBlackTree::inorderHelper(Node *root) {
    if (root == nullptr)
        return;

    inorderHelper(root->left);
    cout << root->data << " (" << (root->color == RED ? "RED" : "BLACK") << ") ";
    inorderHelper(root->right);
}

void RedBlackTree::inorderTraversal() {
    inorderHelper(root);
    cout << endl;
}


int main() {
    RedBlackTree rbt;
    
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);
    rbt.insert(35);
    rbt.insert(5);
    rbt.insert(40);
    
    cout << "Inorder Traversal of Red-Black Tree:\n";
    rbt.inorderTraversal();

    return 0;
}
