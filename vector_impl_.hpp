#ifndef VECTOR_IMPL_HPP
#define VECTOR_IMPL_HPP

namespace container {

template <typename T>
vector<T>::vector()
    : m_arr(nullptr)
    , m_size(0)
    , m_cap(0)
{
}

template <typename T>
vector<T>::vector(int size)
    : m_arr(new T [size])
    , m_size(size)
    , m_cap(size)
{
}

template <typename T>
vector<T>::vector(const vector& other)
    : m_arr(new T[other.size])
    , m_size(other.size)
    , m_cap(other.m_cap)
{
    for (int i = 0; i < other.size; ++i) {
        m_arr[i] = other.m_arr[i];
    }
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& other)
{
    if (this != & other) {
        delete[] m_arr;
        m_size = other.size;
        m_cap = other.m_cap;
        m_arr = new T[m_cap];
        for (int i = 0; i < m_size; ++i) {
            m_arr[i] = other.m_arr[i];
        }
    }
    return *this;
}

template <typename T>
vector<T>::vector(vector&& other)
    : m_arr(std::move(other.m_arr))
    , m_size(other.m_size)
    , m_cap(other.m_cap)
{
    other.m_arr = nullptr;
    other.m_size = 0;
    other.m_cap = 0;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& other)
{
    if (this != &other) {
        delete [] m_arr;
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
vector<T>::vector(std::initializer_list<T> init_list)
    : m_arr(nullptr)
    , m_size(0)
    , m_cap(0)
{
    resize(init_list.size());
    for (const T& elem : init_list) {
        push_back(elem);
    }
}

template <typename T>
vector<T>::~vector()
{
    clear();
}

template <typename T>
void vector<T>::clear()
{
    delete [] m_arr;
    m_size = 0;
    m_cap = 0;
}

template <typename T>
int vector<T>::get_size() const
{
    return m_size;
}

template <typename T>
int vector<T>::get_capacity() const
{
    return m_cap;
}

template <typename T>
void vector<T>::resize(int new_cap, const T& value)
{
    if (new_cap > m_cap) {
        T* tmp = new T [new_cap];
        for (int i = 0; i < m_size; ++i) {
            tmp[i] = m_arr[i];
        }

        for (int i = m_size; i < m_cap; ++i) {
            tmp[i] = value;
        }

        for (int i = m_size; i < new_cap; ++i) { 
            tmp[i] = value;
        }

        delete[] m_arr;
        m_arr = tmp;
        m_cap = new_cap;
    } 
}

template <typename T>
void vector<T>::push_back(const T& value)
{
    if (m_size >= m_cap) {
        int new_cap = (m_cap == 0) ? 1 : m_cap * 2;
        resize(new_cap);
    }
    m_arr[m_size++] = value;
}

template <typename T>
T& vector<T>::operator[](const int pos)
{
    if (pos >= 0 && pos < m_size) {
        return m_arr[pos];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
const T& vector<T>::operator[](const int pos) const
{
    if (pos >= 0 && pos < m_size) {
        return m_arr[pos];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
bool vector<T>::is_empty()
{
    return m_size == 0;
}

template <typename T>
void vector<T>::pop_back()
{
    if (m_size > 0) {
        --m_size;
    } else {
        throw std::runtime_error("Vector is empty. Cannot pop_back().");
    }
}

template <typename T>
void vector<T>::insert(const int pos, const T& value)
{
    if (pos >= 0 && pos <= m_size) {
        if (m_size == m_cap) {
            resize(m_cap * 2);
        }

        for (int i = m_size; i > pos; --i) {
            m_arr[i] = m_arr[i - 1];
        }
        m_arr[pos] = value;
        ++m_size;
    } else {
        throw std::out_of_range("Invalid position for insertion");
    }
}

template <typename T>
void vector<T>::insert(const int pos, const T& value, int count)
{
    if (pos >= 0 && pos <= m_size && count >= 0) {
        if (m_size + count > m_cap) {
            resize(m_size + count);
        }

        for (int i = m_size + count - 1; i >= pos + count; --i) {
            m_arr[i] = m_arr[i - count];
        }

        for (int i = pos; i < pos + count; ++i) {
            m_arr[i] = value;
        }

        m_size += count;
    } else {
        throw std::out_of_range("Invalid position or count for insertion");
    }
}

template <typename T>
void vector<T>::insert(const int pos, const vector<T>& other)
{
    if (pos >= 0 && pos <= m_size) {
        int other_size = other.m_size;

        if (m_size + other_size > m_cap) {
            resize(m_size + other_size);
        }

        for (int i = m_size + other_size - 1; i >= pos + other_size; --i) {
            m_arr[i] = m_arr[i - other_size];
        }

        for (int i = 0; i < other_size; ++i) {
            m_arr[pos + i] = other.m_arr[i];
        }

        m_size += other_size;
    } else {
        throw std::out_of_range("Invalid position for insertion");
    }
}

template <typename T>
void vector<T>::insert(const int pos, std::initializer_list<T> l)
{
    int count = l.size();
    if (pos >= 0 && pos <= m_size && count > 0) {
        if (m_size + count > m_cap) {
            resize(m_size + count);
        }

        for (int i = m_size + count - 1; i >= pos + count; --i) {
            m_arr[i] = m_arr[i - count];
        }

        auto it = l.begin();
        for (int i = pos; i < pos + count; ++i) {
            m_arr[i] = *it;
            ++it;
        }

        m_size += count;
    } else {
        throw std::out_of_range("Invalid position or initializer list for insertion");
    }
}

template <typename T>
void vector<T>::remove(const int pos)
{
    if (pos >= 0 && pos < m_size) {
        for (int i = pos; i < m_size - 1; ++i) {
            m_arr[i] = m_arr[i + 1];
        }
        --m_size;
    } else {
        throw std::out_of_range("Invalid position for remove");
    }
}

template <typename T>
void vector<T>::remove(const int pos, int count)
{
    if (pos >= 0 && pos < m_size && count > 0 && count <= m_size) {
        for (int i = pos; i < m_size - count; ++i) { 
            m_arr[i] = m_arr[i + count];  
        }
        m_size -= count;  
    } else {
        throw std::out_of_range("Invalid position or count for remove");
    }
}

template <typename T>
void vector<T>::shrink_to_fit()
{
    if (m_size < m_cap) {
        T* tmp = new T[m_size];
        for (int i = 0; i < m_size; ++i) {
            tmp[i] = m_arr[i];
        }

        delete[] m_arr;
        m_arr = tmp;
        m_cap = m_size;
    }
}

template <typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs)
{
    if (lhs.get_size() != rhs.get_size()) {
        return false;
    }

    for (int i = 0; i < lhs.get_size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }

    return true;
}

template <typename T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs)
{
    int size = std::min(lhs.get_size(), rhs.get_size());

    for (int i = 0; i < size; ++i) {
        if (lhs[i] < rhs[i]) {
            return true;
        } else if (lhs[i] > rhs[i]) {
            return false;
        }
    }

    return lhs.get_size() < rhs.get_size();
}

template <typename T>
bool operator<=(const vector<T>& lhs, const vector<T>& rhs)
{
    return !(rhs < lhs);
}

template <typename T>
bool operator>(const vector<T>& lhs, const vector<T>& rhs)
{
    return rhs < lhs;
}

template <typename T>
bool operator>=(const vector<T>& lhs, const vector<T>& rhs)
{
    return !(lhs < rhs);
}

} // namespace container

#endif // VECTOR_IMPL_HPP