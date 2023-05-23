#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include "storage.hpp"

template <class T>
class weak_ptr;

template <class T>
class shared_ptr {
private:
    Storage<T> *m_shared_storage;

    void copy(const shared_ptr<T> &other) {
        m_shared_storage = other.m_shared_storage;
        if (m_shared_storage)
            m_shared_storage->m_shared_count++;
    }

    void copy(const weak_ptr<T> &other) {
        m_shared_storage = other.m_shared_storage;
        if (!other.expired())
            m_shared_storage->m_shared_count++;
    }

    void destroy() {
        m_shared_storage->m_shared_count--;
        if (m_shared_storage->m_shared_count == 0) {
            T *obj = m_shared_storage->m_storage.begin();
            obj->~T();

            if (m_shared_storage->m_weak_count == 0)
                delete m_shared_storage;
        }
    }

public:
    shared_ptr() : m_shared_storage(nullptr) {}
    
    shared_ptr(const T &object) {
        m_shared_storage = new Storage<T>(object);
    }

    shared_ptr(const weak_ptr<T> &other) {
        copy(other);
    }
    
    shared_ptr(const shared_ptr<T> &other) {
        copy(other);
    }

    shared_ptr &operator=(const weak_ptr<T> &other) {
        shared_ptr<T> obj = other.lock();
        if (this != &obj) {
            if (m_shared_storage)
                destroy();
            copy(other);
        }

        return *this;
    }
    
    shared_ptr &operator=(const shared_ptr<T> &other) {
        if (this != &other) {
            if (m_shared_storage)
                destroy();
            copy(other);
        }

        return *this;
    }

    T &operator*() const {
        if (m_shared_storage)
            return *m_shared_storage->m_storage.begin();

        throw std::runtime_error("shared_ptr has not object for dereferencing");
    }

    T *operator->() const {
        if (m_shared_storage)
            return m_shared_storage->m_storage.begin();

        return nullptr;
    }

    operator bool() const {
        return m_shared_storage ? true : false;
    }

    T *get() const {
        if (m_shared_storage)
            return m_shared_storage->m_storage.begin();

        return nullptr;
    }

    size_t use_count() const {
        if (m_shared_storage)
            return m_shared_storage->m_shared_count;

        return 0;
    }

    ~shared_ptr() {
        if (m_shared_storage)
            destroy();
    }

    friend class weak_ptr<T>;
};

template <class T>
class weak_ptr
{
private:
    Storage<T> *m_shared_storage;

    void copy(const shared_ptr<T> &other) {
        m_shared_storage = other.m_shared_storage;
        if (m_shared_storage) {
            m_shared_storage->m_weak_count++;
        }
    }

    void copy(const weak_ptr<T> &other) {
        m_shared_storage = other.m_shared_storage;
        if (m_shared_storage)
            m_shared_storage->m_weak_count++;
    }

    void destroy() {
        m_shared_storage->m_weak_count--;
        if (m_shared_storage->m_weak_count == 1)
            delete m_shared_storage;
    }

public:
    weak_ptr() : m_shared_storage(nullptr) {}

    weak_ptr(const shared_ptr<T> &other) {
       copy(other);
    }
    
    weak_ptr(const weak_ptr<T> &other) {
        copy(other);
    }

    weak_ptr &operator=(const shared_ptr<T> &other) {
        if (m_shared_storage != other.m_shared_storage) {
            if (m_shared_storage)
                destroy();
            copy(other);
        }

        return *this;
    }

    weak_ptr &operator=(const weak_ptr<T> &other) {
        if (this != &other) {
            if (m_shared_storage)
                destroy();
            copy(other);
        }

        return *this;
    }

    shared_ptr<T> lock() const {
        shared_ptr<T> obj;
        if (!expired()) {
            obj.m_shared_storage = m_shared_storage;
            obj.m_shared_storage->m_shared_count++;
            obj.m_shared_storage->m_weak_count--;
        }

        return obj;
    }

    size_t use_count() const {
        if (m_shared_storage)
            return m_shared_storage->m_shared_count;

        return 0;
    }

    bool expired() const {
        return m_shared_storage ? false : true;
    }

    ~weak_ptr() {
        if (m_shared_storage) {
            destroy();
        }
    }

    friend class shared_ptr<T>;
};

#endif // __MEMORY_HPP__
