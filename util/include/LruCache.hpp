#ifndef __OBOTCHA_LRU_CACHE_HPP__
#define __OBOTCHA_LRU_CACHE_HPP__

#include "Object.hpp"
#include "HashMap.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

template <typename T, typename U> class _LruCacheIterator;

DECLARE_TEMPLATE_CLASS(LruNode,T,U) {
public:
    friend class _LruCacheIterator<T,U>;
    _LruNode(T t, U u) {
        tag = t;
        data = u;
    }

    sp<_LruNode<T, U>> next;
    sp<_LruNode<T, U>> prev;

    U data;
    T tag;
};

DECLARE_TEMPLATE_CLASS(LruCache, T,U) {
public:
    friend class _LruCacheIterator<T,U>;
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
            node->data = u;
        } else {
            if (mCurrentSize == mMaxSize) {
                sp<_LruNode<T, U>> tail = removeTail();
                mHashMap->remove(tail->tag);
            }
            node = createLruNode<T, U>(t, u);
            mHashMap->put(t, node);
        }
        addNode(node);
    }

    U get(T t) {
        sp<_LruNode<T, U>> node = mHashMap->get(t);
        if (node != nullptr) {
            removeNode(node);
            addNode(node);
            return node->data;
        }

        return nullptr;
    }

    U at(size_t index) {
        Panic(index >= mHashMap->size(),
              ArrayIndexOutOfBoundsException,"index is too large")

        sp<_LruNode<T, U>> node = mHead;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }

        return node->data;
    }

    U remove(T t) {
        sp<_LruNode<T, U>> node = mHashMap->get(t);
        mHashMap->remove(t);

        if(node != nullptr) {
            removeNode(node);
        }

        return node->data;
    }

    size_t size() { 
        return mHashMap->size(); 
    }

    sp<_LruCacheIterator<T,U>> getIterator() {
        return AutoClone(new _LruCacheIterator<T, U>(AutoClone(this)));
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

DECLARE_TEMPLATE_CLASS(LruCacheIterator, T,U) {
public:
    explicit _LruCacheIterator(LruCache<T,U> cache):mCache(cache) {
        mSize = mCache->size();
        mCurrent = mCache->mHead;
    }

    T getKey() {
        Panic(mSize == 0,
            ArrayIndexOutOfBoundsException, "no data")
        return mCurrent->tag;
    }

    U getValue() {
        Panic(mSize == 0,
            ArrayIndexOutOfBoundsException, "no data")
        return mCurrent->data;
    }

    bool hasValue() { 
        return mSize != 0; 
    }

    bool next() {
        if(mSize >= 1) {
            mSize--;
            mCurrent = mCurrent->next;
            return true;
        }
        return false;
    }

    bool remove() {
        Inspect(mSize < 1,false)
        auto r = mCurrent;
        mCurrent = mCurrent->next;
        mCache->remove(r->tag);
        mSize--;
        return ture;
    }

    Pair<T,U> getItem() {
        return (mSize >= 1)?createPair<T,U>(mCurrent->tag,mCurrent->data):nullptr;
    }

private:
    LruCache<T,U> mCache;
    LruNode<T,U> mCurrent;
    size_t mSize;
};


} // namespace obotcha
#endif
