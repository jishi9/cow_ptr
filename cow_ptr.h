#include <iostream>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;

template<typename T>
class cow_ptr {
  private:
    shared_ptr<T> pointee_;

  public:
    cow_ptr() {}

    cow_ptr(T* pointee) : cow_ptr(pointee, true) {}

    cow_ptr(T* raw_pointer, bool takeOwnership) {
        if (takeOwnership) {
            pointee_ = shared_ptr<T>(raw_pointer);
        } else {
            // share_ptr's aliasing constructor
            pointee_ = shared_ptr<T>(shared_ptr<T>(), raw_pointer);
        }
    }

    cow_ptr(const cow_ptr<T>& that) : pointee_(that.pointee_) {}

    const T& operator*() const {
        return *pointee_;
    }

    const T* operator->() const {
        return &(**this);
    }

    T& operator*() {
        // If pointee_ is established to be unique, then we can rely on this fact
        // not changing
        if (!pointee_.unique()) {
            pointee_ = shared_ptr<T>(new T(*pointee_));
        }
        return *pointee_;
    }

    T* operator->() {
        return &(**this);
    }
};
