#include <vector>
#include "Node.h"

class Tree {
private:
  TreeNode *root;
  TreeNode *InsertRecursive(TreeNode *current, int key, int value);
  void DestroyRecursive(TreeNode *current);

public:
  Tree();
  ~Tree();
  
  int Search(int key);
  void Insert(int key, int val);
  void Clear();
};