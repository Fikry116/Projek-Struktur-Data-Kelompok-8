#include "Stack.h"
//   void Push(int value);
//   void Pop();
//   void Top();
//   void Clear();

Stack::Stack() : top(nullptr) {}
void Stack::Clear() {
    while(top) {
        Pop();
    }
}

void Stack::Push(int value) {
    if(top == nullptr) {
        top = new Node(value, nullptr);
        return;
    }
    Node *newNode = new Node(value, top);
    top = newNode;
}

void Stack::Pop() {
    if(top == nullptr) {
        return;
    }
    Node *node_to_delete = top;
    top = top->next;
    delete node_to_delete;
}

int Stack::Top() {
    if(top == nullptr) {
        return -1;
    }
    return top->val;
}

bool Stack::IsEmpty() {
    return top == nullptr;
}