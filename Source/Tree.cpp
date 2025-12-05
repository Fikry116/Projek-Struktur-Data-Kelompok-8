#include "Tree.h"

TreeNode::TreeNode(int key, int value, TreeNode *prnt, TreeNode *l, TreeNode *r) 
  : Key(key), Value(value), parent(prnt), left(l), right(r) {}

Tree::Tree() : root(nullptr) {}
Tree::~Tree() {Clear();}

void Tree::Insert(int key, int val) {
    root = InsertRecursive(root, key, val);

}

TreeNode *Tree::InsertRecursive(TreeNode *current, int key, int value) {
    if(current == nullptr) {
        current = new TreeNode(key, value, current, nullptr, nullptr);
        return current;
    } 
    if(current->Key > key) {
        return InsertRecursive(current->left, key, value);
    } else {
        return InsertRecursive(current->right, key, value);
    }
}

int Tree::Search(int key) {
    TreeNode *current = root;
    while (current) {
        if (key == current->Key) {
            return current->Key;
        } else if (key < current->Key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return -1;
}

void Tree::DestroyRecursive(TreeNode *node) {
    if(node) {
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
    }
}

void Tree::Clear() {
    DestroyRecursive(root);
    root = nullptr;
}