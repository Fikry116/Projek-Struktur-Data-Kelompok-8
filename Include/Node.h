#pragma once
struct Node {
    int val;
    Node *next;

    Node(int data, Node *next = nullptr)
      : val(data), next(next) {}
};

struct TreeNode {
  int Key;
  int Value;
  TreeNode *parent, *left, *right;

  TreeNode(int key, int value, TreeNode *prnt, TreeNode *l = nullptr, TreeNode *r = nullptr);

};