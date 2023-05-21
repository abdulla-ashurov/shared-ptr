# Implementation of std::shared_ptr and std::weak_ptr classes

[![Test](https://github.com/abdulla-ashurov/deque/actions/workflows/test.yml/badge.svg?branch=main)](https://github.com/abdulla-ashurov/deque/actions/workflows/test.yml)

## Implementation of std::shared_ptr

`std::shared_ptr` is a smart pointer that retains shared ownership of an object through a pointer. Several `shared_ptr` objects may own the same object. The object is destroyed and its memory deallocated when either of the following happens:

- the last remaining `shared_ptr` owning the object is destroyed;
- the last remaining `shared_ptr` owning the object is assigned another pointer via `operator=` or `reset()`.

All specializations of `shared_ptr` meet the requirements of `CopyConstructible`, `CopyAssignable`, and `LessThanComparable` and are contextually convertible to `bool`.

### Member functions of std::shared_ptr

- `(constructor)` - constructs new shared_ptr
  - `shared_ptr()` - default constructor
  - `shared_ptr(const T object)` - constructor that accepts object of type `T`
  - `shared_ptr(const weak_ptr<T> &ptr)` - constructor that accepts object of type `weak_ptr<T>`
  - `shared_ptr(const shared_ptr<T> &other)` - copy constructor
- `(destructor)` - destructs the owned object if no more `shared_ptr` link to it
- `operator=` - assigns the shared_ptr
  - `shared_ptr& operator=(const weak_ptr<T> &other)` - operator assignment that accepts object of type `weak_ptr<T>`
  - `shared_ptr& operator=(const shared_ptr<T> &other)` - operator assignment that accepts object of type `shared_ptr<T>`

#### Observers of std::shared_ptr

- `get` - returns the stored pointer
- `operator*` - dereferences the stored pointer
- `operator->` - dereferences the stored pointer
- `operator bool` - checks if the stored pointer is not null
- `use_count` - returns the number of `shared_ptr` objects referring to the same managed object

## Implementation of std::weak_ptr

`std::weak_ptr` is a smart pointer that holds a non-owning (`"weak"`) reference to an object that is managed by `std::shared_ptr`. It must be converted to `std::shared_ptr` in order to access the referenced object.

`std::weak_ptr` models temporary ownership: when an object needs to be accessed only if it exists, and it may be deleted at any time by someone else, std::weak_ptr is used to track the object, and it is converted to `std::shared_ptr` to assume temporary ownership. If the original `std::shared_ptr` is destroyed at this time, the object's lifetime is extended until the temporary `std::shared_ptr` is destroyed as well.

Another use for `std::weak_ptr` is to break reference cycles formed by objects managed by `std::shared_ptr`. If such cycle is orphaned (i.e., there are no outside shared pointers into the cycle), the `shared_ptr` reference counts cannot reach zero and the memory is leaked. To prevent this, one of the pointers in the cycle can be made `weak`.

### Member functions of std::weak_ptr

- `(constructor)` - create a new weak_ptr
  - `weak_ptr()` - default constructor
  - `weak_ptr(const shared_ptr<T> &ptr)` - constructor that accepts object of type `shared_ptr<T>`
  - `weak_ptr(const weak_ptr<T> &other)` - copy constructor
- `(destructor)` - destroys weak_ptr
- `operator=` - assigns the weak_ptr
  - `weak_ptr(const shared_ptr<T> &other)` - operator assignment that accepts object of type `shared_ptr<T>`
  - `weak_ptr<T>& operator=(const weak_ptr &other)` - operator assignment that accepts object of type `weak_ptr<T>`

#### Observers of std::weak_ptr

- `use_count` - returns the number of `shared_ptr` objects referring to the same managed object
- `expired` - checks whether the referenced object was already deleted
- `lock` - creates a `shared_ptr` that manages the referenced object
