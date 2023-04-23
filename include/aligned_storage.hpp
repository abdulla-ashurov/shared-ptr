#ifndef __ALIGNED_STORAGE__
#define __ALIGNED_STORAGE__

template <class T, size_t Size>
class aligned_storage
{
private:
    uint8_t storage[Size * sizeof(T) + alignof(T)];

public:
    T* begin()
    {
        uintptr_t padding = static_cast<uintptr_t>(static_cast<void*>(storage)) % alignof(T);
        if (padding != 0)
            return (T*)(storage + alignof(T) - padding);

        return (T*)(storage);
    }
};

#endif
