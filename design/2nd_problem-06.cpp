#include <iostream>
using namespace std;

class Node {
public:
    //Define member variables such as value, left child, and right child
    //Implement a constructor that initializes the node with a value
    int var;
    Node* left;
    Node* right;
    Node(int var);
};
Node::Node(int var) {
    this->var = var;
    left = nullptr;
    right = nullptr;
}

class BST {
private:
    Node* root;

    void dfs(Node* node) {
        //Recursive depth-first traversal (preorder)
        if (node == nullptr) return;
        cout << node->var << ' ';
        dfs(node->left);
        dfs(node->right);
    }
    void freeTree(Node* node) {
        //Recursively delete all nodes in the tree
        if (node == nullptr) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
public:
    BST() {
        //Constructor to initialize the BST
        root = nullptr;
    }
    ~BST() {
        freeTree(root);
    }

    void insert(int val) {
        //Insert a new value into the BST
        Node* tmp = root;
        if (root == nullptr) {
            root = new Node(val);
            return;
        }
        while (true)
        {
            if (tmp->var > val)
            {
                if (tmp->left == nullptr)
                {
                    tmp->left = new Node(val);
                    break;
                }
                else
                {
                    tmp = tmp->left;
                }
            }
            else
            {
                if (tmp->right == nullptr)
                {
                    tmp->right = new Node(val);
                    break;
                }
                else
                {
                    tmp = tmp->right;
                }
            }
        }
    }

    void printDFS() {
        dfs(root);
        cout << "\n";
    }
};

int main() {
    int n;
    cin >> n;
    BST tree;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        tree.insert(val);
    }
    tree.printDFS();
    return 0;
}
