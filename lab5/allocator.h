#pragma once
#include <memory>
#include <vector>

template <class T>
class Allocator 
{
public:
    static constexpr int size = 100;
    std::vector<T> data;
    int ost;

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = int;

    Allocator() 
    {
        data.resize(size);
        ost = size;
    }

    ~Allocator() = default;

    pointer allocate(int n) 
    {
        if (n > ost) 
        {
            throw std::bad_alloc();
        }

        ost -= n;

        return &data[ost];
    }

    void deallocate(pointer p, int n)
    {
        ost += n;
    }

    template <class... Args>
    void construct(pointer p, Args&&... args) 
    {
        new (p) T(std::forward<Args>(args)...);
    }

    void destroy(pointer p)
    {
        std::destroy_at(p); // аналогично p -> ~T(), но современный
    }

    template <class U>
    struct rebind 
    {
        using other = Allocator<U>;
    };
};

template <class T, class U>
constexpr bool operator==(const Allocator<T>& lhs, const Allocator<U>& rhs) 
{
    return true;
}

template <class T, class U>
constexpr bool operator!=(const Allocator<T>& lhs, const Allocator<U>& rhs)
{
    return false;
}
