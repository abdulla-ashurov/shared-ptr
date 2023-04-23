# Implementation of std::shared_ptr and std::weak_ptr classes

## Implementation of std::shared_ptr

`std::shared_ptr` is a smart pointer that retains shared ownership of an object through a pointer. Several `shared_ptr` objects may own the same object. The object is destroyed and its memory deallocated when either of the following happens:

- the last remaining `shared_ptr` owning the object is destroyed;
- the last remaining `shared_ptr` owning the object is assigned another pointer via `operator=` or `reset()`.

All specializations of `shared_ptr` meet the requirements of `CopyConstructible`, `CopyAssignable`, and `LessThanComparable` and are contextually convertible to `bool`.

### Member functions of std::shared_ptr

- `(constructor)` - constructs new shared_ptr
  - `shared_ptr()` - default constructor
  - `shared_ptr(const T &object)` - constructor that accepts object of type `T`
  - `shared_ptr(const weak_ptr<T> &ptr)` - constructor that accepts object of type `weak_ptr<T>`
  - `shared_ptr(const shared_ptr<T> &other)` - copy constructor
- `(destructor)` - destructs the owned object if no more `shared_ptr` link to it
- `operator=` - assigns the shared_ptr

#### Observers of std::shared_ptr

- `get` - returns the stored pointer
- `operator*` - dereferences the stored pointer
- `operator->` - dereferences the stored pointer
- `operator bool` - checks if the stored pointer is not null
- `use_count` - returns the number of `shared_ptr` objects referring to the same managed object
