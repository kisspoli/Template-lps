#pragma once
#include <iostream>
#include <string>
#include <sstream>

template <typename X>
class DoublyLinkedList //����� ��� ���������������� ������
{
    struct Node { //��������� ��� ������ ����
        X data; 
        Node* next;
        Node* prev;
        Node(X _data, Node* _next, Node* _prev) :data(_data), next(_next), prev(_prev){ //�����������
            if (next)
                next->prev = this;
            if (prev)
                prev->next = this;
        }
    };
    Node* first;
    Node* last;
    int size;
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void AddToBegin(X _data);
    void AddToEnd(X _data);
    void Print(std::ostream& stream) const;
    void Read(std::istream& stream);
    void Clear();
    void Reverse();
    int FindIndex(X _data);
    bool IsSymmetric();
    int getSize() const;
    int UniqueValuesCount();
    class Iterator { //����� ��� ����������� �� ������
        Node* currentNode;
    public:
        Iterator() :currentNode(nullptr) {};
        Iterator(Node* p) : currentNode(p) {};
        Iterator& operator++() { currentNode = currentNode->next; return *this; } //������� � ���������� �������� ++i 
        Iterator& operator++(int) { currentNode = currentNode->next; return *this; } //������� � ���������� �������� i++ 
        Iterator& operator=(const Iterator& it) { currentNode = it.currentNode; return *this; } //������������
        bool operator==(const Iterator& it) const { return currentNode == it.currentNode; } //���������
        bool operator!=(const Iterator& it) const { return currentNode != it.currentNode; } //���������
        X& operator*() { return currentNode->data; } //�������������
    };
    Iterator& begin() const { return *(new Iterator(first)); } //�������� �� ������
    Iterator& end() const { return *(new Iterator(last->next)); } //�������� �� �����
    friend std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<X>& list); //�������� ������
    friend std::istream& operator>>(std::istream& in, DoublyLinkedList<X>& list); //�������� �����
};

template<typename X>
DoublyLinkedList<X>::DoublyLinkedList() { //�����������
    first = last = nullptr;
    size = 0;
}

template<typename X>
DoublyLinkedList<X>::~DoublyLinkedList() { //����������
    Clear();
    delete first;
    delete last;
}

template<typename X>
void DoublyLinkedList<X>::AddToBegin(X _data) { //���������� �������� � ������ ������
    Node* newNode = new Node(_data, first, nullptr);
    if (size == 0)
        this->last = newNode;
    else
        this->first->prev = newNode;
    this->first = newNode;
    ++size;
}

template<typename X>
void DoublyLinkedList<X>::AddToEnd(X _data) { //���������� �������� � ����� ������
    Node* newNode = new Node(_data, nullptr, last);
    if (size == 0)
        this->first = newNode;
    else
        this->last->next = newNode;
    this->last = newNode;
    ++size;
}

template<typename X>
void DoublyLinkedList<X>::Print(std::ostream& stream) const { //����� ���� ���������
    operator<<<X>(stream, *this);
}

template<typename X>
void DoublyLinkedList<X>::Read(std::istream& stream) { //������ �� ������
    operator>><X>(stream, *this);
}

template <typename X>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<X>& list) { //�������� ������
    if (list.getSize() != 0) {
        for (typename DoublyLinkedList<X>::Iterator it = list.begin(); it != list.end(); it++) {
            out << *it << " ";
        }
    }
    return out;
}

template <typename X>
std::istream& operator>>(std::istream& in, DoublyLinkedList<X>& list) //�������� �����
{
    list.Clear();
    std::string input;
    std::stringstream ss;
    while (!in.eof()) {
        std::getline(in, input);
        ss = std::stringstream(input);
        X value;
        while (!ss.eof() && ss >> value)
            list.AddToEnd(value);
    }
    return in;
}

template<typename X>
void DoublyLinkedList<X>::Clear() { //������� ������
    Node* p = this->first;
    while (p != nullptr) {
        p = p->next;
        delete this->first;
        this->first = p;
    }
    this->last = nullptr;
    this->size = 0;
}

template<typename X>
int DoublyLinkedList<X>::FindIndex(X _data) { //����� �������
    int index = 0;
    Node* p = this->first;
    bool found = false;
    while (p != nullptr) {
        if (p->data == _data) {
            return index;
        }
        index++;
        p = p->next;
    }
    return -1;
}

template<typename X>
bool DoublyLinkedList<X>::IsSymmetric(){ //�������� �������� �� ������ ������������
    bool result = true;
    int count = (size % 2 == 0) ? size / 2 : size / 2 + 1;
    Node* i = this->first, *j = this->last;
    while (count > 0 && result) {
        if (i->data != j->data)
            result = false;
        i = i->next;
        j = j->prev;
        count--;
    }
    return result;
}

template<typename X>
int DoublyLinkedList<X>::getSize() const {
    return size;
}

template<typename X>
int DoublyLinkedList<X>::UniqueValuesCount() { //����� ���������� ���������� ���������
    DoublyLinkedList<X> unique_values;
    Node* p = this->first;
    while (p != nullptr) {
        if (unique_values.FindIndex(p->data) == -1)
            unique_values.AddToEnd(p->data);
        p = p->next;
    }
    return unique_values.size;
}


template<typename X>
void DoublyLinkedList<X>::Reverse() { //��������� ������� ��������� �� ��������
    Node* p = nullptr;
    Node* q = this->first;
    while (q != nullptr) {
        p = q->prev;
        q->prev = q->next;
        q->next = p;
        q = q->prev;
    }
    std::swap(this->first, this->last);
}