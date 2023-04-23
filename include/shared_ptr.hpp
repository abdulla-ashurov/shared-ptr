#ifndef __UNIQUE_PTR_HPP__
#define __UNIQUE_PTR_HPP__

#include "aligned_storage.hpp"
#include "weak_ptr.hpp"

template <class T> 
class shared_ptr {
public:
    shared_ptr();
    shared_ptr(const T object);
    shared_ptr(const weak_ptr<T> &ptr);
    shared_ptr(const shared_ptr<T> &other);

    shared_ptr& operator=(const weak_ptr<T> &other);
    shared_ptr& operator=(const shared_ptr<T> &other);
    T& operator*() const;
    T* operator->() const;
    operator bool() const;

    T* get() const;
    long use_count() const;

    ~shared_ptr();
};

#endif // __UNIQUE_PTR_HPP__
