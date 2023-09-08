#ifndef __OBOTCHA_LRU_CACHE_HPP__
#define __OBOTCHA_LRU_CACHE_HPP__

#include "Object.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(LruNode, T,U) {
public:
    _LruNode(T t, U u) {
        tag = t;
        mData = u;
    }

    sp<_LruNode<T, U>> next;
    sp<_LruNode<T, U>> prev;

    U mData;
    T tag;
};

DECLARE_TEMPLATE_CLASS(LruCache, T,U) {
public:
    _LruCache(size_t s) {
        mMaxSize = s;
        mCurrent = nullptr;
        mHead = nullptr;
        mCurrentSize = 0;
        mHashMap = createHashMap<T, sp<_LruNode<T, U>>>();
    }

    ~_LruCache() {
        mHashMap->clear();
        auto current = mCurrent;
        while(current != nullptr) {
            if(current->prev != nullptr) {
                current->prev->next = nullptr;
            }
            auto next = current->prev;
            current->prev = nullptr;
            current->next = nullptr;
            current = next;
        }
    }

    void put(T t, U u) {
        sp<_LruNode<T, U>> node = mHashMap->get(t);
        if (node != nullptr) {
            removeNode(node);
        } else {
            if (mCurrentSize == mMaxSize) {
                sp<_LruNode<T, U>> tail = removeTail();
                mHashMap->remove(tail->tag);
            }
        }
        node = createLruNode<T, U>(t, u);
        mHashMap->put(t, node);
        addNode(node);
    }

    U get(T t) {
        sp<_LruNode<T, U>> node = mHashMap->get(t);
        if (node != nullptr) {
            // update node
            removeNode(node);
            addNode(node);
            return node->mData;
        }

        return nullptr;
    }

    U at(size_t index) {
        sp<_LruNode<T, U>> node = mHead;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }

        return node->mData;
    }

    void remove(T t) {
        sp<_LruNode<T, U>> node = mHashMap->get(t);
        mHashMap->remove(t);

        if (node == nullptr) {
            return;
        }

        removeNode(node);
    }

    size_t size() { 
        return mHashMap->size(); 
    }

private:
    size_t mMaxSize;

    size_t mCurrentSize;

    HashMap<T, sp<_LruNode<T, U>>> mHashMap;

    sp<_LruNode<T, U>> mHead;

    sp<_LruNode<T, U>> mCurrent;

    void removeNode(sp<_LruNode<T, U>> node) {
        if (node == mHead) {
            if (node->next != nullptr) {
                mHead = node->next;
                mHead->prev = nullptr;
                node->next = nullptr;
            } else {
                mHead = nullptr;
                mCurrent = nullptr;
            }
        } else if (node == mCurrent) {
            mCurrent = mCurrent->prev;
            mCurrent->next = nullptr;
            node->prev = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->next = nullptr;
            node->prev = nullptr;
        }
        mCurrentSize--;
    }

    void addNode(sp<_LruNode<T, U>> node) {
        if (mHead == nullptr) {
            mHead = node;
            mCurrent = mHead;
        } else {
            node->next = mHead;
            mHead->prev = node;
            mHead = node;
        }
        mCurrentSize++;
    }

    sp<_LruNode<T, U>> removeTail() {
        sp<_LruNode<T, U>> tail = mCurrent;
        removeNode(mCurrent);
        return tail;
    }
};

} // namespace obotcha
#endif
