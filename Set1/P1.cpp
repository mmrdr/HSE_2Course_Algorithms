#include <stdexcept>
#include<unordered_set>
#include "list.h"

List::List() : _size(0), head(nullptr), tail(nullptr) {}


List::List(const List& other) {
    _size = other._size;
    head = new Node(other.head-> value);
    Node* current = other.head-> next;
    Node* prev = head;
    tail = head;
    while(current) {
        tail = new Node(current->value);
        tail->prev = prev;
        prev->next = tail;
        current = current->next;
        prev = tail;
    }
}

List::List(std::vector<int> array) : _size(0), head(nullptr), tail(nullptr) {
    for (auto vl : array) {
        push_back(vl);
    }
}

List::~List() {
    while(_size != 0) {
        pop_back();
    }
}

int List::front() {
    if (_size == 0) {
        throw std::runtime_error("Can't take front() in empty list");
    }
    return head -> value;
}


int List::back() {
    if (_size == 0) {
        throw std::runtime_error("Can't take back() in empty list");
    }
    return tail -> value;
}

void List::push_back(int data) {
    Node* node = new Node(data);
    if (tail == nullptr) {
        head = node;
        tail = node;
    } else {
        tail -> next = node;
        node -> prev = tail;
        tail = node;
    }
    ++_size;
}

void List::push_front(int data) {
    Node* node = new Node(data);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        node -> next = head;
        head -> prev = node;
        head = node;
    }
    ++_size;
}

void List::insert(Node* prev, int data) {
    if (prev == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }

    int i = 1;
    Node* current = head;
    while(current != prev) {
        current = current -> next;
        ++i;
    }

    Node* node = new Node(data);
    if (current -> next == nullptr) {
        current -> next = node;
        node -> prev = current;
    } else {
        Node* temp = current->next;
        current -> next = node;
        node -> prev = current;
        temp -> prev = node;
        node -> next = temp;
    }
    ++_size;
}

void List::pop_front() {
    if (empty()) {
        throw std::runtime_error("Deleting in empty list");
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    --_size;
}

void List::pop_back() {
    if (empty()) {
        throw std::runtime_error("Deleting from an empty list");
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    --_size;
}

void List::erase(Node* pos) {
    if (pos == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }
    if (pos == head) {
        pop_front();
    } else if (pos == tail) {
        pop_back();
    } else {
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        delete pos;
        _size--;
    }
}

void List::clear() {
    while(_size != 0) {
        pop_back();
    }
}

void List::reverse() {
    if (head == nullptr) {
        return;
    }
    Node* current = head;
    Node* temp = nullptr;
    while (current) {
        temp = current->prev;current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    temp = head;
    head = tail;
    tail = temp;
}

void List::remove_duplicates() {
    if (empty()) {
        return;
    }
    std::unordered_set<int> set;
    Node* current = head;
    while (current) {
        if (set.find(current->value) != set.end()) {
            Node* dnode = current;
            if (dnode->prev != nullptr) {
                dnode->prev->next = dnode->next;
            }
            if (dnode->next != nullptr) {
                dnode->next->prev = dnode->prev;
            }
            if (dnode == head) {
                head = dnode->next;
            }
            if (dnode == tail) {
                tail = dnode->prev;
            }
            current = current -> next;
            delete dnode;
            --_size;
        } else {
            set.insert(current->value);
            current = current -> next;
        }
    }
}

void List::replace(int el, int newV) {
    Node* current = head;
    while (current) {
        if (current->value == el) {
            current->value = newV;
        }
        current = current->next;
    }
}

void List::merge(const List& other) {
    Node* current = other.head;
    while(current){
        push_back(current->value);
        current = current -> next;
    }
}

bool List::check_cycle() const {
    Node* hare = head;
    Node* tortoise = head;
    while(hare && hare->next) {
        hare = hare -> next -> next;
        tortoise = tortoise -> next;
        if (hare == tortoise) {
            return true;
        }
    }
    return false;
}

size_t List::size() const {
    return _size;
}

bool List::empty() const{
    return _size == 0;
}

void List::copy(const List& other) {
    clear();
    merge(other);
}
