#include <iostream>

template<class T>
class List {
    struct Node {
        public:
        T data;
        int next;
        int prev;
        Node(T data = T(), int next = 0, int prev = 0)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };
    int head;
    int tail;
    int size;
    Node *arr;

    int Move(int index) {
            int it = head;
            for (int i = 0; i < index; ++i) {
                it = arr[it].next;
            }
            return it;
        }

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
        Node *newArr = new Node[lst.size];
        for (int i = 0; i < lst.getSize(); ++i) {
            newArr[i] = lst.arr[i];
        }
        head = lst.begin();
        tail = lst.end();
        size = lst.getSize();
    }

    Node *begin() {
        return &arr[head];
    }

    Node *end() {
        return &arr[tail];
    }

    List<T>& operator=(const List<T> &other) {
        head = other.head;
        tail = other.tail;
        size = other.size;
        return *this;
    }
};

const int null = -1;

template<class T>
List<T>::List()// конструктор
{
    arr = nullptr;
    size = 0;
    head = null;
    tail = null;
}

template<class T>
List<T>::~List()// деструктор
{
    clear();
}

template<class T>
void List<T>::push_front(T data)// добавление элемента в начало списка
{

    Node *newArr = new Node[size + 1];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }

    newArr[size].data = data;

    if (head != 0)
    {
        newArr[size].prev = null;
        newArr[size].next = null;
        head = tail = size;
    }
    else
    {
        newArr[size].prev = null;
        newArr[size].next = head;
        newArr[head].prev = 0;
        head = size;
    }
    arr = newArr;
    delete[] newArr;
    size++;
}

template<class T>// удаление всех элементов списка
void List<T>::clear()
{
    delete[] arr;
    size = 0;
    head = null;
    tail = null;
}

template<class T>
void List<T>::pop_front()// удаление элемента из начала списка
{
    arr[arr[head].next].prev = null;
    head = Move(1);
    int it = head;
}

template<class T>
void List<T>::push_back(T data)// добавление элемента в конец списка
{
    Node *newArr = new Node[size + 1];

    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }

    newArr[size].data = data;

    if (head != 0)
    {
        newArr[size].prev = -1;
        newArr[size].next = -1;
        head = tail = size;
    }
    else
    {
        newArr[size].prev = tail;
        newArr[size].next = -1;
        newArr[tail].next = size;
        tail = size;
    }
    arr = newArr;
    size++;
}

template<class T>
T& List<T>::operator[](const int index)// перегрузка оператора []
{
    if (!IsCorrectIndex(index)) {
        throw std::out_of_range("index out of range");
    }
    return arr[Move(index)].data;
}

template<class T>
void List<T>::insert(T data, int index)// добавление элемента на любую позицию в список
{

    if (!IsCorrectIndex(index)) throw std::out_of_range("index out of range");

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
    {   Node *newArr = new T[size + 1];
        for (int i = 0; i < size + 1; i++) {
            newArr[i] = arr[i];
        }

        newArr[size].data = data;

        int elemPrev = Move(index - 1);
        int elemNext = Move(index);
        newArr[size].prev = elemPrev;
        newArr[size].next = elemNext;
        newArr[elemPrev] = size;
        newArr[elemNext] = size;
        arr = newArr;
        delete[] newArr;
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
    else if (index == size - 1) {
                arr[Move(tail - 1)].next = null;
                tail = Move(index - 1);
    }
    else {
        int next = arr[Move(index)].next;
        int prev = arr[Move(index)].prev;
        arr[Move(index - 1)].next = next;
        arr[Move(index + 1)].prev = prev;
    }

    size--;
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
