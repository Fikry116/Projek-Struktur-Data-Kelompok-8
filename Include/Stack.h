//struct stack
#include "Node.h"
class Stack {
private:
  Node* top;
public:
  Stack();

  bool IsEmpty();
  void Push(int value);
  void Pop();
  void Clear();
  int Top();
};
