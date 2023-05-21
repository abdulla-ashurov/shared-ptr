#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include "aligned_storage.hpp"

template <class T>
class shared_ptr;

template <class T>
class Storage
{
private:
    AlignedStorage<T> m_storage;
    size_t m_shared_count = 0;
    size_t m_weak_count = 0;

public:
    Storage(const T object)
    {
        new (m_storage.begin()) T(object);
        m_shared_count++;
    }

    friend class shared_ptr<T>;
};

#endif // __STORAGE_HPP__