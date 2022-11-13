#ifndef __OBOTCHA_LINKED_LIST_HPP__
#define __OBOTCHA_LINKED_LIST_HPP__

#include <algorithm>
#include <functional>
#include <vector>

#include "Object.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "ContainerValue.hpp"

namespace obotcha {

template <typename T> class _LinkedListIterator;

template <typename T> class _LinkedList;

DECLARE_TEMPLATE_CLASS(LinkedListData, T) {
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
DECLARE_TEMPLATE_CLASS(LinkedList, T) {
public:
    friend class _LinkedListIterator<T>;

    _LinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    int size() { return count; }

    bool isEmpty() { return (head == nullptr); }

    T first() {
        return (head == nullptr) ? ContainerValue<T>(nullptr).get()
                                 : head->data;
    }

    T last() {
        return (tail == nullptr) ? ContainerValue<T>(nullptr).get()
                                 : tail->data;
    }

    void putLast(const T &t) {
        LinkedListData<T> data = createLinkedListData<T>(t);
        count++;

        data->prev = tail;
        tail = data;
        ((head == nullptr) ? head : data->prev->next) = data;
    }

    T at(int index) {
        sp<_LinkedListData<T>> cursor = head;
        if (cursor == nullptr || index >= count) {
            return ContainerValue<T>(nullptr).get();
        }

        for (int i = 0; i != index; i++) {
            cursor = cursor->next;
        }

        return cursor->data;
    }

    void putFirst(const T &t) {
        LinkedListData<T> data = createLinkedListData<T>(t);
        count++;

        data->next = head;
        head = data;
        ((tail == nullptr) ? tail : data->next->prev) = data;
    }

    T takeLast() {
        T data;
        if (count != 0) {
            data = tail->data;
            tail = tail->prev;
            ((tail == nullptr) ? head : tail->next) = nullptr;
            count--;
        }
        return data;
    }

    T takeFirst() {
        T data;
        if (count != 0) {
            data = head->data;
            head = head->next;
            ((head == nullptr) ? tail : head->prev) = nullptr;
            count--;
        }

        return data;
    }

    sp<_LinkedListIterator<T>> getIterator() {
        return new _LinkedListIterator<T>(this);
    }

    void clear() {
        while (head != nullptr) {
            auto next = head->next;
            head->next = nullptr;
            head->prev = nullptr;
            head = next;
        }
        tail = nullptr;
        count = 0;
    }

    // add remove/removeAt
    T removeAt(int index) {
        if (index >= count || index < 0) {
            return ContainerValue<T>(nullptr).get();
        }

        auto iterator = this->getIterator();
        for (int i = 0; i < index; i++) {
            iterator->next();
        }

        T result = iterator->getValue();
        iterator->remove();
        //count--;
        return result;
    }

    int remove(T v) {
        auto iterator = this->getIterator();
        int index = 0;
        while (iterator->hasValue()) {
            if (iterator->getValue() == v) {
                iterator->remove();
                //count--;
                return index;
            }
            index++;
            iterator->next();
        }

        return -1;
    }

    ~_LinkedList() {
        clear();
    }

private:
    LinkedListData<T> head;
    LinkedListData<T> tail;
    int count;
};

//----------------- ArrayListIterator ---------------------
DECLARE_TEMPLATE_CLASS(LinkedListIterator, T) {
public:
    _LinkedListIterator(_LinkedList<T> * list) {
        mList.set_pointer(list);
        current = mList->head;
    }

    _LinkedListIterator(LinkedList<T> list) {
        mList = list;
        current = mList->head;
    }

    T getValue() { return current->data; }

    bool hasValue() { return current != nullptr; }

    bool next() {
        if (current == nullptr) {
            return false;
        }

        current = current->next;
        return (current != nullptr);
    }

    bool remove() {
        if (current == nullptr) {
            return false;
        }

        LinkedListData<T> t = current->next;

        if (current == mList->head) {
            mList->takeFirst();
        } else if (current == mList->tail) {
            mList->takeLast();
        } else {
            current->next->prev = current->prev;
            current->prev->next = current->next;
            mList->count--;
        }

        current = t;

        if (t == nullptr) {
            return false;
        }

        return true;
    }

    T getItem() {
        if(mList->count == 0) {
            Trigger(ArrayIndexOutOfBoundsException, "no data");
        }
        return current->data;
    }

private:
    LinkedList<T> mList;
    LinkedListData<T> current;
};

} // namespace obotcha
#endif
