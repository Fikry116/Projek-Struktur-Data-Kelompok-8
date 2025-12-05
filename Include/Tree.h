#include <vector>
#include "Node.h"

class Tree {
private:
  TreeNode *root;
public:
  Tree();
  ~Tree();

  TreeNode *InsertRecursive(TreeNode *current, int key, int value);
  void DestroyRecursive(TreeNode *current);

  int Search(int key);
  void Insert(int key, int val);
  void Clear();
};