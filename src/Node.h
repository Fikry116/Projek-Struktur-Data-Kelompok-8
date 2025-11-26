#include <vector>
struct Node {
    int val;
    Node *next;

    Node(int data, Node *next = nullptr)
      : val(data), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *parent;
    std::vector<TreeNode*> child;
};