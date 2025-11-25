//struct stack
struct Node {
    int val;
    Node* next;
    
};

struct Stack {
    Node* Top;
    
};template <class T>
class Stacka {
    T val;
    Stacka<T> *head, *tail;
};