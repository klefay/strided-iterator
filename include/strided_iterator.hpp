#pragma once

namespace my {

template <typename Iterator>
struct strided_iterator {
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using reference = typename std::iterator_traits<Iterator>::reference;

    strided_iterator() = default;
    strided_iterator(pointer ptr, difference_type stride)
        : _ptr(ptr)
        , _stride(stride)
    {
    }
    strided_iterator(difference_type ptr, difference_type stride)
        : _ptr(ptr)
        , _stride(stride)
    {
    }
    operator pointer() const { return _ptr; }
    // Forward iterator requirements
    reference operator*() const { return *_ptr; }
    pointer operator->() const { return _ptr; }
    strided_iterator& operator++()
    {
        _ptr += _stride;
        return *this;
    }
    strided_iterator operator++(int)
    {
        const auto temp = strided_iterator(_ptr, _stride);
        _ptr += _stride;
        return temp;
    }
    // Bidirectional iterator requirements
    strided_iterator& operator--()
    {
        _ptr -= _stride;
        return *this;
    }
    strided_iterator operator--(int)
    {
        const auto temp = strided_iterator(_ptr, _stride);
        _ptr -= _stride;
        return temp;
    }
    // Random access iterator requirements
    reference operator[](difference_type n) const { return _ptr[n * _stride]; }
    strided_iterator& operator+=(difference_type n)
    {
        _ptr += n * _stride;
        return *this;
    }
    strided_iterator operator+(difference_type n) const { return { _ptr + n * _stride, _stride }; }
    strided_iterator& operator-=(difference_type n)
    {
        _ptr -= n * _stride;
        return *this;
    }
    strided_iterator operator-(difference_type n) const { return { _ptr + n * _stride, _stride }; }
    // Comparison functions
    friend bool operator==(const strided_iterator& lhs, const strided_iterator& rhs) { return lhs._ptr == rhs._ptr; }
    friend bool operator!=(const strided_iterator& lhs, const strided_iterator& rhs) { return lhs._ptr != rhs._ptr; }
    friend bool operator<(const strided_iterator& lhs, const strided_iterator& rhs) { return lhs._ptr < rhs._ptr; }
    friend bool operator>(const strided_iterator& lhs, const strided_iterator& rhs) { return lhs._ptr > rhs._ptr; }
    friend bool operator<=(const strided_iterator& lhs, const strided_iterator& rhs) { return lhs._ptr <= rhs._ptr; }
    friend bool operator>=(const strided_iterator& lhs, const strided_iterator& rhs) { return lhs._ptr >= rhs._ptr; }
    // Distance function
    difference_type operator-(const pointer& rhs) const { return (_ptr - rhs) / _stride; }

private:
    pointer _ptr;
    difference_type _stride;
};

}
