#ifndef __WEAK_PTR_HPP__
#define __WEAK_PTR_HPP__

// #include "shared_ptr.hpp"

template <class T>
class weak_ptr
{
public:
    weak_ptr();
    weak_ptr(const shared_ptr<T> &other);
    // weak_ptr(const weak_ptr<T> &other);

    weak_ptr &operator=(const weak_ptr<T> &other);
    weak_ptr &operator=(const shared_ptr<T> &other);

    shared_ptr<T> lock() const;

    long use_count() const;
    bool expired() const;

    ~weak_ptr();
};

#endif // __WEAK_PTR_HPP__
