#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace container {

template <typename T>
class Vector 
{
public:
    Vector();
    Vector(size_t size);
    Vector(const Vector& other);  // copy ctor
    Vector(Vector&& other);       // move ctor
    Vector& operator=(const Vector& other);  // copy assignment operator
    Vector& operator=(Vector&& other);       // move assignment operator
    ~Vector(); // dtor

public:
    void reserve(size_t cap);
    void push_back(const T& value);
    void pop_back();
    void clear(); 
    size_t size() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& back();
    const T& back() const;
    bool empty() const;

private:
    T* m_arr;
    size_t m_size;
    size_t m_cap;
};

} // namespace container

#include "vector_impl_.hpp"

#endif // VECTOR_HPP
