#ifndef __ALIGNED_STORAGE__
#define __ALIGNED_STORAGE__

template <class T>
class AlignedStorage
{
private:
    uint8_t storage[sizeof(T) + alignof(T)];

public:
    T *begin()
    {
        uintptr_t padding = (uintptr_t)((void *)(storage)) % alignof(T);
        if (padding != 0)
            return (T *)(storage + alignof(T) - padding);

        return (T *)(storage);
    }
};

#endif // __ALIGNED_STORAGE_HPP__
