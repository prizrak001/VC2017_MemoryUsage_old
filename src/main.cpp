#include <iostream>
#include <list>

#include <memory>
#include <stdio.h>

// 
// http://stackoverflow.com/a/12529302/2314910
// 
namespace mmap_allocator_namespace
{
    template <typename T>
    class mmap_allocator : public std::allocator<T>
    {
    public:
        typedef size_t size_type;
        typedef T* pointer;
        typedef const T* const_pointer;

        template<typename _Tp1>
        struct rebind
        {
            typedef mmap_allocator<_Tp1> other;
        };

        pointer allocate(size_type n, const void *hint = 0)
        {
            fprintf(stderr, "Alloc %d bytes.\n", n * sizeof(T));
            return std::allocator<T>::allocate(n, hint);
        }

        void deallocate(pointer p, size_type n)
        {
            fprintf(stderr, "Dealloc %d bytes (%p).\n", n * sizeof(T), p);
            return std::allocator<T>::deallocate(p, n);
        }

        mmap_allocator() throw() : std::allocator<T>() { fprintf(stderr, "Hello allocator!\n"); }
        mmap_allocator(const mmap_allocator &a) throw() : std::allocator<T>(a) { }
        template <class U>
        mmap_allocator(const mmap_allocator<U> &a) throw() : std::allocator<T>(a) { }
        ~mmap_allocator() throw() { }
    };
}

class Aaa {
    public:
        int int1;
        double double1;
};

using AaaList = std::list<Aaa, mmap_allocator_namespace::mmap_allocator<Aaa>>;

AaaList aaaList;

void fillList(size_t n) {
    for (size_t i = 0; i < n; ++i) {
        aaaList.push_back(Aaa{ 3, 5.7 });
    }
}

void fillList() {
    fillList(3);
}

void clearList() {
    aaaList.clear();
}

int main() {
    for (size_t i = 0; i < 5; ++i) {
        fillList();
        clearList();
    }

    return EXIT_SUCCESS;
}

