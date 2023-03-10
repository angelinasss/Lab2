template<class T>
class stack {
private:

    struct Node {
        Node* next;
        T data;
    };

    int size1;
    Node* top1;

public:
    stack() {
        size1 = 0;
        Node* top = new Node();
        top->next = nullptr;
    }

    ~stack() {
        Node* tmp = top1;
        for (int i = 0; i < size1; ++i) {
            Node* buf = tmp->next;
            delete tmp;
            tmp = buf;
        }
    }

    void push(const T newElement) {

        Node* newEl = new Node();
        newEl->data = newElement;
        if (size1 > 0) {
            newEl->next = top1;
           top1 = newEl;
        }

        else {
            newEl->next = nullptr;
            top1 = newEl;
        }
        size1++;
    }

    T& top() {
        return top1->data;
    }

    void pop() {

        if (size1 > 0) {
            Node* tmp = top1->next;
            if (top1)
            delete top1;
            top1 = tmp;
            size1--;
        }

    }

    int size() {
        return size1;
    }

};
