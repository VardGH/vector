#ifndef VECTOR_IMPL_HPP
#define VECTOR_IMPL_HPP

namespace container{

template <typename T>
Vector<T>::Vector() 
    : m_arr(nullptr)
    , m_size(0)
    , m_cap(0) 
{
}

template <typename T>
Vector<T>::Vector(size_t size) 
    : m_arr(new T[size])
    , m_size(size)
    , m_cap(size) 
{
}

template <typename T>
Vector<T>::Vector(const Vector& other) 
    : m_arr(new T[other.m_size])
    , m_size(other.m_size)
    , m_cap(other.m_size) 
{
    for (size_t i = 0; i < m_size; ++i) {
        m_arr[i] = other.m_arr[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other) 
    : m_arr(std::move(other.m_arr))
    , m_size(other.m_size)
    , m_cap(other.m_cap) 
{
    other.m_arr = nullptr;
    other.m_size = 0;
    other.m_cap = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) 
{
    if (this != &other) {
        delete[] m_arr;
        m_size = other.m_size;
        m_cap = other.m_cap;
        m_arr = new T[m_size];
        for (size_t i = 0; i < m_size; ++i) {
            m_arr[i] = other.m_arr[i];
        }
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) 
{
    if (this != &other) {
        delete[] m_arr;
        m_arr = other.m_arr;
        m_size = other.m_size;
        m_cap = other.m_cap;

        other.m_arr = nullptr;
        other.m_size = 0;
        other.m_cap = 0;
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector() 
{
    delete[] m_arr;
}

template <typename T>
void Vector<T>::reserve(size_t new_cap) 
{
    if (new_cap > m_cap) {
        T* new_arr = new T[new_cap];
        for (size_t i = 0; i < m_size; ++i) {
            new_arr[i] = std::move(m_arr[i]);
        }
        delete[] m_arr;
        m_arr = new_arr;
        m_cap = new_cap;
    }
}

template <typename T>
void Vector<T>::push_back(const T& value) 
{
    if (m_size >= m_cap) {
        size_t new_cap = (m_cap == 0) ? 1 : m_cap * 2;
        reserve(new_cap);
    }
    m_arr[m_size++] = value;
}

template <typename T>
void Vector<T>::pop_back() 
{
    if (m_size > 0) {
        --m_size;
    } else {
        throw std::runtime_error("Vector is empty. Cannot pop_back().");
    }
}

template <typename T>
size_t Vector<T>::size() const 
{
    return m_size;
}

template <typename T>
T& Vector<T>::operator[](size_t index) 
{
    return m_arr[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const 
{
    return m_arr[index];
}

template <typename T>
void Vector<T>::clear() 
{
    m_size = 0;
}
    
template <typename T>
T& Vector<T>::back()
{
    return m_arr[m_size - 1];
}

template <typename T>
const T& Vector<T>::back() const
{
    return m_arr[m_size - 1];
}

template <typename T>
bool Vector<T>::empty() const
{
    return !(this->size());
}
    
} // namespace container

#endif // VECTOR_IMPL_HPP
