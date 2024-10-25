#ifndef __OBOTCHA_LINKED_LIST_HPP__
#define __OBOTCHA_LINKED_LIST_HPP__

#include <algorithm>
#include <functional>
#include <vector>
#include <atomic>

#include "Object.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "Inspect.hpp"

namespace obotcha {

template <typename T> class _LinkedListIterator;
template <typename T> class _LinkedList;

DECLARE_TEMPLATE_CLASS(LinkedListData, T) {
public:
    friend class _LinkedList<T>;
    friend class _LinkedListIterator<T>;

    explicit _LinkedListData(T t):data(t) {
    }

    sp<_LinkedListData<T>> next = nullptr;
    sp<_LinkedListData<T>> prev = nullptr;

private:
    T data;
};

//----------------- LinkedList ---------------------
DECLARE_TEMPLATE_CLASS(LinkedList, T) {
public:
    friend class _LinkedListIterator<T>;

    explicit _LinkedList() = default;

    size_t size() const { 
        return count; 
    }

    bool isEmpty() const { 
        return (head == nullptr); 
    }

    T first() const {
        return (head == nullptr) ? nullptr : head->data;
    }

    T last() const {
        return (tail == nullptr) ? nullptr : tail->data;
    }

    void putLast(const T &t) {
        LinkedListData<T> data = LinkedListData<T>::New(t);
        count++;

        data->prev = tail;
        tail = data;
        ((head == nullptr) ? head : data->prev->next) = data;
    }

    T at(size_t index) const {
        sp<_LinkedListData<T>> cursor = head;
        if (cursor == nullptr || index >= count) {
            return nullptr;
        }

        for (int i = 0; i != index; i++) {
            cursor = cursor->next;
        }

        return cursor->data;
    }

    void putFirst(const T &t) {
        LinkedListData<T> data = LinkedListData<T>::New(t);
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

    inline T peekFirst() {
        return (head == nullptr)?nullptr:head->data;
    }

    inline T peekLast() {
        return (head == nullptr)?nullptr:tail->data;
    }

    sp<_LinkedListIterator<T>> getIterator() const {
        return AutoClone(new _LinkedListIterator<T>(this));
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
    T removeAt(size_t index) {
        Inspect(index >= count,nullptr)

        auto iterator = this->getIterator();
        for (size_t i = 0; i < index; i++) {
            iterator->next();
        }

        T result = iterator->getValue();
        iterator->remove();
        return result;
    }

    int remove(T v) {
        auto iterator = this->getIterator();
        int index = 0;
        while (iterator->hasValue()) {
            if (iterator->getValue() == v) {
                iterator->remove();
                return index;
            }
            index++;
            iterator->next();
        }

        return -1;
    }

    ~_LinkedList() override {
        clear();
    }

private:
    LinkedListData<T> head = nullptr;
    LinkedListData<T> tail = nullptr;
    size_t count = 0;
};

//----------------- ArrayListIterator ---------------------
DECLARE_TEMPLATE_CLASS(LinkedListIterator, T) {
public:
    explicit _LinkedListIterator(_LinkedList<T> * list) {
        mList.set_pointer(list);
        current = mList->head;
    }

    explicit _LinkedListIterator(LinkedList<T> list):mList(list) {
        current = mList->head;
    }

    T getValue() { 
        return current->data; 
    }

    bool hasValue() { 
        return current != nullptr; 
    }

    bool next() {
        Inspect(current == nullptr,false)
        current = current->next;
        return (current != nullptr);
    }

    bool remove() {
        Inspect(current == nullptr,false)
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
        return t != nullptr;
    }

    T getItem() {
        Panic(mList->count == 0,
                ArrayIndexOutOfBoundsException, "no data")
        return current->data;
    }

private:
    LinkedList<T> mList;
    LinkedListData<T> current;
};

} // namespace obotcha
#endif
