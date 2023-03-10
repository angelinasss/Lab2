#include <iostream>

template<class T>
struct Node {
    public:
    T data;
    Node* next;
    Node* prev;
    Node(T data = T(), Node *next = nullptr, Node *prev = nullptr)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

template<class T>
class List {
    Node<T>* head;
    Node<T>* tail;
    int size;

    bool IsCorrectIndex(int index) {
        return (index <= size) && (index >= 0);
    }

public:
    List();
    ~List();

    void pop_front();

    void push_back(T data);

    void clear();

    T& operator[](const int index);

    void push_front(T data);

    void insert(T data, int index);

    void removeAt(int index);

    void pop_back();

    int getSize();

    void changeSize();

    List(const List& lst) {
        head = lst.begin;
        tail = lst.end;
        size = lst.count;
    }

    Node<T>* begin() {
        return this->head;
    }

    Node<T>* end() {
        return this->tail;
    }

    List<T>& operator=(const List<T> &other) {
        head = other.head;
        tail = other.tail;
        size = other.size;
        return *this;
    }
};

template<class T>
List<T>::List()// конструктор
{
    size = 0;
    head = nullptr;
    tail = nullptr;
}

template<class T>
List<T>::~List()// деструктор
{
    clear();
}

template<class T>
void List<T>::push_front(T data)// добавление элемента в начало списка
{

    Node<T> *temp = new Node<T>(data);

    if (head != nullptr)
    {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
    else
    {
        head = tail = temp;
    }

    size++;
}

template<class T>// удаление всех элементов списка
void List<T>::clear()
{
    while (head)
    {
        pop_front();
    }
}

template<class T>
void List<T>::pop_front()// удаление элемента из начала списка
{
    Node<T> *current = this->head;
    Node<T> *newHead = current->next;
    head = newHead;
    newHead->prev = nullptr;
    delete current;
    size--;
}

template<class T>
void List<T>::push_back(T data)// добавление элемента в конец списка
{
    Node<T> *temp = new Node<T>(data);

    if (head != NULL)
    {
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
    else
    {
        head = tail = temp;
    }

    size++;
}

template<class T>
T& List<T>::operator[](const int index)// перегрузка оператора []
{
    int counter = 0;

    Node<T> *current = this->head;

    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->next;
        counter++;
    }
}

template<class T>
void List<T>::insert(T data, int index)// добавление элемента на любую позицию в список
{

    if (!IsCorrectIndex(index)) return;

    if (index == 0)
    {
        push_front(data);
        return;
    }
    if (index == size) {
        push_back(data);
        return;
    }
    else
    {
        Node<T> *previous = this->head;

        for (int i = 0; i < index - 1; i++)
        {
            previous = previous->next;
        }

        Node<T> *pnext = this->head;

        for (int i = 0; i < index; i++)
        {
            pnext = pnext->next;
        }

        Node<T> *newNode = new Node<T>(data, pnext, previous);

        previous->next = newNode;
        pnext->prev = newNode;

        size++;
    }
}

template<class T>
void List<T>::removeAt(int index)// удаление элемента с любой позиции списка
{
    if (!size || (index < 0 && index >= size))
        return;
    if (index == 0)
    {
        pop_front();
    }
    else
    {
        Node<T> *previous = this->head;
        if(index == size - 1) previous = this->tail->prev;
        else {
        for (int i = 0; i < index - 1; i++)
        {
            previous = previous->next;
        }
        }


        Node<T> *toDelete = previous->next;

        if(index == size - 1) {
            tail = previous;

            previous->next = nullptr;
        }

        else {
        Node<T> *next = toDelete->next;
        next->prev = previous;
        previous->next = next;
        }

        delete toDelete;

        size--;
    }
}

template<class T>
void List<T>::pop_back()// удаление элемента с конца списка
{
    removeAt(size - 1);
}

template<class T>
int List<T>::getSize() {
    return size;
}

template<class T>
void List<T>::changeSize()// удаление элемента с конца списка
{
    size++;
}
