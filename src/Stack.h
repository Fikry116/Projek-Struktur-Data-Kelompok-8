//struct stack
struct Node {
    int val;
    Node* next;
    
};

struct Stack {
    Node* Top;

    int peek() {
        return Top->val;
    }
};

template <class T>
class Stacka {
    T val;
    Stacka<T> *head, *tail;
};