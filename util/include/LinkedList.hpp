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
#include "ContainerValue.hpp"

namespace obotcha {
    
template<typename T>
class _LinkedListIterator;

template<typename T>
class _LinkedList;

DECLARE_TEMPLATE_CLASS(LinkedListData,1) {
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
DECLARE_TEMPLATE_CLASS(LinkedList,1) {
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

    T first() {
        return (head == nullptr)?ContainerValue<T>(nullptr).get():head->data;
    }

    T last() {
        return (tail == nullptr)?ContainerValue<T>(nullptr).get():tail->data;
    }

    void putLast(const T &t) {
        LinkedListData<T> data = createLinkedListData<T>(t);
        count++;
        
        data->prev = tail;
        tail = data;
        ((head==nullptr)?head:data->prev->next) = data;
    }

    T at(int index) {
        sp<_LinkedListData<T>> cursor = head;
        if(cursor == nullptr || index >= count) {
            return ContainerValue<T>(nullptr).get();
        }

        for(int i = 0;i != index;i++) {
            cursor = cursor->next;
        }

        return cursor->data;
    }

    void putFirst(const T &t) {
        LinkedListData<T> data = createLinkedListData<T>(t);
        count++;
        
        data->next = head;
        head = data;
        ((tail==nullptr)?tail:data->next->prev) = data;
    }

    T takeLast() {
        T data;
        if(count != 0) {
            data = tail->data;
            tail = tail->prev;
            ((tail == nullptr)?head:tail->next) = nullptr;
            count--;
        }
        return data;
    }

    T takeFirst() {
        T data;
        if(count != 0) {
            data = head->data;
            head = head->next;
            ((head == nullptr)?tail:head->prev) = nullptr;
            count--;
        }

        return data;
    }

    //add foreach lambda
    using foreachCallback = std::function<int(T)>;
    inline void foreach(foreachCallback callback) {
        LinkedListData<T> current = head;
        while(current != nullptr) {
            if(callback(current->data) == Global::Break) {
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
        count = 0;
    }

    //add remove/removeAt
    T removeAt(int index) {
        if(index >= count || index < 0) {
            return ContainerValue<T>(nullptr).get();
        }
        
        auto iterator = this->getIterator();
        for(int i = 0;i<index;i++) {
            iterator->next();
        }
        
        T result = iterator->getValue();
        iterator->remove();
        return result;
    }

    int remove(T v) {
        auto iterator = this->getIterator();
        int index = 0;
        while(iterator->hasValue()) {
            if(iterator->getValue() == v) {
                iterator->remove();
                return index;
            }
            index++;
            iterator->next();
        }

        return -1;
    }

private:
    LinkedListData<T> head;
    LinkedListData<T> tail;
    int count;
};

//----------------- ArrayListIterator ---------------------
DECLARE_TEMPLATE_CLASS(LinkedListIterator,1) {
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
            mList->takeFirst();
        } else if(current == mList->tail) {
            mList->takeLast();
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
