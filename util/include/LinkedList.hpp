#ifndef __OBOTCHA_LINKED_LIST_HPP__
#define __OBOTCHA_LINKED_LIST_HPP__

#include <vector>
#include <algorithm>
#include <functional>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "MethodNotSupportException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "MethodNotSupportException.hpp"

namespace obotcha {
    
template<typename T>
class _LinkedListIterator;

template<typename T>
class _LinkedList;

DECLARE_CLASS(LinkedListData,1) {
public:
    friend class _LinkedList<T>;
    friend class _LinkedListIterator<T>;

    _LinkedListData(T t) {
        data = t;
        next = nullptr;
        prev = nullptr;
    }

    sp<_LinkedListData<T>> next;
    sp<_LinkedListData<T>> prev;

private:
    T data;

};

//----------------- LinkedList ---------------------
DECLARE_CLASS(LinkedList,1) {
public:
    friend class _LinkedListIterator<T>;

    _LinkedList(){
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return (head == nullptr);
    }

    void enQueueLast(const T &t) {
        LinkedListData<T> data = createLinkedListData<T>(t);
        count++;
        if(head == nullptr) {
            head = data;
            tail = head;
            return;
        }

        tail->next = data;
        data->prev = tail;
        tail = data;
    }

    T at(int index) {
        sp<_LinkedListData<T>> cursor = head;
        if(cursor == nullptr || index >= count) {
            return nullptr;
        }

        for(int i = 0;i != index;i++) {
            cursor = cursor->next;
        }

        return cursor->data;
    }

    void enQueueFirst(const T &t) {
        LinkedListData<T> data = createLinkedListData<T>(t);
        count++;
        if(head == nullptr) {
            head = data;
            tail = head;
            return;
        }

        data->next = head;
        head->prev = data;
        head = data;
    }

    T deQueueLast() {
        if(head == nullptr) {
            return nullptr;
        }

        T data = tail->data;
        count--;
        if(head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        return data;
    }

    T deQueueFirst() {
        if(head == nullptr) {
            return nullptr;
        }
        
        T data = head->data;
        count--;
        if(head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        return data;
    }

    //add foreach lambda
    using foreachCallback = std::function<int(T)>;
    inline void foreach(foreachCallback callback) {
        LinkedListData<T> current = head;
        while(current != nullptr) {
            if(callback(current->data) < 0) {
                break;
            }
            current = current->next;
        }
    }
    
    sp<_LinkedListIterator<T>> getIterator() {
        return new _LinkedListIterator<T>(this);
    }

    void clear() {
        LinkedListData<T> current = head;
        while(head != nullptr) {
            if(head->next != nullptr) {
                head->next->prev = nullptr;
            }
            head->next = nullptr;
            head = nullptr;
            head = current->next;
        }
    }

private:
    LinkedListData<T> head;
    LinkedListData<T> tail;
    int count;
};

//----------------- ArrayListIterator ---------------------
DECLARE_CLASS(LinkedListIterator,1) {
public:
    _LinkedListIterator(_LinkedList<T> *list) {
        mList.set_pointer(list);
        current = mList->head; 
    }

    _LinkedListIterator(LinkedList<T> list) {
        mList = list;
        current = mList->head;
    }

    T getValue() {
        return current->data;
    }

    bool hasValue() {
        return current != nullptr;
    }

    bool next() {
        if(current == nullptr) {
            return false;
        }

        current = current->next;
        return (current != nullptr);
    }

    bool remove() {
        if(current == nullptr) {
            return false;
        }

        LinkedListData<T> t = current->next;

        if(current == mList->head) {
            mList->deQueueFirst();
        } else if(current == mList->tail) {
            mList->deQueueLast();
        } else {
            current->next->prev = current->prev;
            current->prev->next = current->next;
            mList->count--;
        }

        current = t;

        if(t == nullptr) {
            return false;
        }

        return true;
    }
    
private:
    LinkedList<T> mList;
    LinkedListData<T> current;
};

}
#endif
