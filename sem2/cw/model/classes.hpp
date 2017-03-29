// Copyright 2015 Tim Catler
#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include "./interfaces.hpp"

template <typename T> class ListItem {
 public:
    ListItem() {
        data = new T;
        prev = nullptr;
        next = nullptr;
    }

    explicit ListItem(const T &data): ListItem() { *(this->data) = data; }

    ListItem(const ListItem<T> &other): ListItem() {
        *data = *(other.data);
        prev = other.prev;
        next = other.next;
    }

    ~ListItem() {
        delete data;
    }

    ListItem<T>* &Next() {return next;}
    ListItem<T>* &Prev() {return prev;}
    T &Data() {return *(data);}

 private:
    ListItem<T>* next;
    ListItem<T>* prev;
    T* data;
};

template <class T> class List {
 public:
    List() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    List(const List &other) : List() {
        head = other.head;
        tail = other.tail;
        count = other.count;
        // TODO(timecatler): copy data?
    }

    ~List() {
        ListItem<T>* curr = head;

        while (curr != nullptr && curr->Next() != nullptr) {
            curr = curr->Next();
            delete curr->Prev();
        }
        delete curr;
    }

    List& operator=(const List&);

    unsigned Count() {return count;}
    T First() {return head->Data();}
    T Last() {return tail->Data();}

    bool Includes(const T &data) {
        ListItem<T>* curr = head;

        while (curr->Next()) {
            if (curr->Data() == data) return true;
            curr = curr->Next();
        }
    }

    void Append(const T &data) {
        if (head == nullptr && tail == nullptr) {
            head = tail = new ListItem<T>(data);
        } else {
            tail->Next() = new ListItem<T>(data);
            tail->Next()->Prev() = tail;
            tail->Next()->Next() = nullptr;
            tail = tail->Next();
        }
        count++;
    }

    void Remove(const T &data) {  // TODO(timecatler): non-unique deleting
        ListItem<T>* curr = head;

        while (curr != nullptr) {
            if (curr->Data() == data) {
                if (curr == head && curr == tail) {
                    delete curr;
                    head = tail = nullptr;
                    count--;
                    return;

                } else if (curr == head) {
                    RemoveFirst();
                    return;

                } else if (curr == tail) {
                    RemoveLast();
                    return;

                } else {
                    curr->Prev()->Next() = curr->Next();
                    curr->Next()->Prev() = curr->Prev();
                    delete curr;
                    count--;
                    return;
                }
            }
            curr = curr->Next();
        }
        return;
    }

    void RemoveLast() {
        ListItem<T>* curr = tail;
        tail = curr->Prev();
        tail->Next() = nullptr;
        delete curr;
        count--;
    }
    void RemoveFirst() {
        ListItem<T>* curr = head;
        head = curr->Next();
        head->Prev() = nullptr;
        delete curr;
        count--;
    }
    void RemoveAll() {
        while (head != nullptr) RemoveFirst();
    }

 protected:
    ListItem<T>* Begin() {
        return head;
    }
    ListItem<T>* End() {
        return tail;
    }

 private:
    ListItem<T>* head;
    ListItem<T>* tail;
    unsigned count;
};

#endif  // CLASSES_H
