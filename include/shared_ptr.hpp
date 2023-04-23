#ifndef __UNIQUE_PTR_HPP__
#define __UNIQUE_PTR_HPP__

#include "aligned_storage.hpp"

template <class T> 
class shared_ptr {
private:
    size_t m_counter;
    aligned_storage<T, 1> m_object;

public:
    // constructors
    shared_ptr();
    shared_ptr(const T object);
    shared_ptr(const shared_ptr<T> &other);

    // operators
    shared_ptr& operator=(const shared_ptr<T> &other);
    T& operator*() const;
    T* operator->() const;
    operator bool() const;

    // getters
    T* get() const;
    long use_count() const;

    // destructor
    ~shared_ptr();
};

#endif // __UNIQUE_PTR_HPP__
