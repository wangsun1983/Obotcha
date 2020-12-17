#ifndef __OBOTCHA_LRU_CACHE_HPP__
#define __OBOTCHA_LRU_CACHE_HPP__

#include <map>
#include <algorithm>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "Mutex.hpp"

#include "ArrayList.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_CLASS(LruNode,2) {
public:
    _LruNode(T t,U u) {
        tag = t;
        mData = u;
    }

    sp<_LruNode<T,U>> next;
    sp<_LruNode<T,U>> prev;

    U mData;
    T tag;
};

DECLARE_CLASS(LruCache,2) {
public:
    _LruCache(int s) {
        mMaxSize = s;
        mCurrent = nullptr;
        mHead = nullptr;
        mCurrentSize = 0;

        mHashMap = createHashMap<T,sp<_LruNode<T,U>>>();
    }

    void put(T t,U u) {
        sp<_LruNode<T,U>> node = mHashMap->get(t);
        if(node != nullptr) {
            removeNode(node);
        } else {
            if(mCurrentSize == mMaxSize) {
                sp<_LruNode<T,U>> tail = removeTail();
                mHashMap->remove(tail->tag);
            }
        }
        node = createLruNode<T,U>(t,u);
        mHashMap->put(t,node);
        addNode(node);
    }

    U get(T t) {
        sp<_LruNode<T,U>> node = mHashMap->get(t);
        if(node != nullptr) {
            //update node
            removeNode(node);
            addNode(node);
            return node->mData;
        }

        return nullptr;
    }

    U at(int index) {
        sp<_LruNode<T,U>> node = mHead;
        for(int i = 0;i < index;i++) {
            node = node->next;
        }

        return node->mData;
    }

    void remove(T t) {
        sp<_LruNode<T,U>> node = mHashMap->get(t);
        mHashMap->remove(t);

        if(node == nullptr) {
            return;
        }

        removeNode(node);
    }
    
    int size() {
        return mHashMap->size();
    }

private:

    int mMaxSize;

    int mCurrentSize;

    HashMap<T,sp<_LruNode<T,U>>> mHashMap;

    sp<_LruNode<T,U>> mHead;

    sp<_LruNode<T,U>> mCurrent;

    void removeNode(sp<_LruNode<T,U>> node) {
        if(node == mHead) {
            if(node->next != nullptr) {
                mHead = node->next;
                mHead->prev = nullptr;
                node->next = nullptr;
            } else {
                mHead = nullptr;
                mCurrent = nullptr;
            }
        } else if(node == mCurrent) {
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

    void addNode(sp<_LruNode<T,U>> node) {
        if(mHead == nullptr) {
            mHead = node;
            mCurrent = mHead;
        } else {
            node->next = mHead;
            mHead->prev = node;
            mHead = node;
        }
        mCurrentSize++;
    }

    sp<_LruNode<T,U>> removeTail() {
        sp<_LruNode<T,U>> tail = mCurrent;
        removeNode(mCurrent);
        return tail;
    }

};

}
#endif
