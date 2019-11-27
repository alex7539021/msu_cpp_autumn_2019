#pragma once

#include <iterator>
#include <algorithm>

template <class T>
class Allocator {
public:
    using val_type = T;
    using ptr = T *;
    using size_type = size_t;

    ptr allocate(size_type count) {
        if (count > max_size()) {
            throw std::invalid_argument("size must not exceed max size");
        }
        return static_cast<ptr>(::operator new(count *sizeof(val_type)));
    }

    void deallocate(ptr p, size_type count) {
        ::operator delete(p);
    }

    template <class... Args>
    void construct(ptr p, Args&&... args) {
        ::new (p) T(std::forward<Args>(args)...);
    }

    void destroy(ptr p) {
        p->~T();
    }

    size_type max_size() const noexcept {
        return (static_cast<size_type>(0) - static_cast<size_type>(1)) / sizeof(T);
    }
};


template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
private:
    T *ptr_;

public:
    using ref = T &;
    typedef std::random_access_iterator_tag iterator_category;

    explicit Iterator(T *p) : 
        ptr_(p) {
    }

    bool operator==(const Iterator<T> &other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T> &other) const {
        return !(*this == other);
    }

    ref operator*() const {
        return *ptr_;
    }

    Iterator &operator++() {
        ptr_++;
        return *this;
    }

    Iterator &operator--() {
        ptr_--;
        return *this;
    }
};

template <class T, class Alloc = std::allocator<T>>
class Vector {
public:
    using iterator = Iterator<T>;
    using size_type = size_t;
    using val_type = T;
    using ref = val_type &;
    using const_ref = const val_type &;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using pointer =  typename Alloc::pointer;

    explicit Vector(size_type count = 0) {
        data = alloc_.allocate(count);
        alloc = used = count;
        for (size_type i = 0; i < used; ++i) {
            alloc_.construct(data + i);
        }
    }

    Vector(size_type count, const val_type &defaultVal) {
        data = alloc_.allocate(count);
        alloc = used = count;
        for (size_type i = 0; i < used; ++i) {
            alloc_.construct(data + i, defaultVal);
        }
    }

    iterator begin() noexcept {
        return iterator(data);
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    Iterator<T> end() noexcept {
        return iterator(data + used);
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    size_type capacity() const noexcept {
        return alloc;
    }

    size_type size() const noexcept {
        return used;
    }

    bool empty() const noexcept {
        return used == 0;
    }

    void resize(size_type new_size, const val_type& defaultVal = val_type()) {
        if (used > new_size) {
            for (size_type i = new_size; i < used; ++i) {
                alloc_.destroy(data + i);
            }
        } else {
            if (alloc < new_size) {
                reserve(new_size);
            }

            for (size_type i = used; i < new_size; ++i) {
                alloc_.construct(data + i, defaultVal);
            }
        }
        used = new_size;
    }

    void reserve(size_type count) {
        if (alloc != count) {
            auto tmp = alloc_.allocate(count);

            if (used > count) {
                used = count;
            }
            for (size_type i = 0; i < used; ++i) {
                alloc_.construct(tmp + i, data[i]);
                alloc_.destroy(data + i);
            }
            alloc_.deallocate(data, alloc);

            data = tmp;
            alloc = count;
        }
    }

    void clear() noexcept {
        while (used > 0) {
            alloc_.destroy(data + used);
            used--;
        }
    }

    ref operator[](size_type i) {
        return data[i];
    }

    const_ref operator[](size_type i) const {
        return data[i];
    }

    void push_back(const val_type &val) {
        if (used >= alloc) {
            reserve(2 * alloc + 1);
        }
        data[used] = val;
        used++;
    }

    void push_back(val_type &&val) {
        if (used >= alloc) {
            reserve(2 * alloc + 1);
        }
        data[used] = std::move(val);
        used++;
    }

    void pop_back() {
        used--;
        alloc_.destroy(data + used);
    }

    ~Vector() {
        clear();
        alloc_.deallocate(data, alloc);
    }

private:
    pointer data = nullptr;
    size_type used = 0, alloc = 0;
    Alloc alloc_;
};