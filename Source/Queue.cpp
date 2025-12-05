#include "Queue.h"

Queue::Queue() : head(nullptr), tail(nullptr) {}

void Queue::Enqueue(int value) {
    if(head == nullptr) {
        head = tail = new Node(value, nullptr);
        return;
    }
    Node *newNode = new Node(value, nullptr);
    tail->next = newNode;
    tail = newNode;
}

void Queue::Dequeue() {
 if(head == nullptr) {
    return;
 }
  Node *node_to_delete = head;
  head = head->next;
  
  if(head == nullptr) {
    tail = nullptr;
  }
  delete node_to_delete;
}

int Queue::Front() {
    if(head == nullptr) return -1;
    
    return head->val;
}

bool Queue::IsEmpty() {
    return head == nullptr;
}