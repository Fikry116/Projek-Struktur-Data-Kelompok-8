//struct queue 
#include "Node.h"

class Queue {
private:
  Node *head, *tail;
  
public:
  Queue();

  bool IsEmpty();
  void Enqueue(int value);
  void Dequeue();
  void Clear();
  int Front();
};