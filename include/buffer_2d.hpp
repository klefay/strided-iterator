#pragma once

#include "strided_iterator.hpp"

#include <iterator>
#include <stdexcept>
#include <vector>

namespace my {

template <typename T>
class buffer_2d {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using horizontal_iterator = typename std::vector<T>::iterator;
    using const_horizontal_iterator = typename std::vector<T>::const_iterator;
    using reverse_horizontal_iterator = std::reverse_iterator<horizontal_iterator>;
    using const_reverse_horizontal_iterator = std::reverse_iterator<const_horizontal_iterator>;
    using vertical_iterator = strided_iterator<pointer>;
    using const_vertical_iterator = strided_iterator<const_pointer>;
    using reverse_vertical_iterator = std::reverse_iterator<vertical_iterator>;
    using const_reverse_vertical_iterator = std::reverse_iterator<const_vertical_iterator>;

    buffer_2d(size_type num_rows, size_type num_cols)
        : _num_rows { num_rows }
        , _num_cols { num_cols }
        , _buffer(num_rows * num_cols)
    {
    }

    reference at(size_type row, size_type col)
    {
        check_row(row);
        check_col(col);
        return _buffer.at(row * _num_cols + col);
    }
    const_reference at(size_type row, size_type col) const
    {
        check_row(row);
        check_col(col);
        return _buffer.at(row * _num_cols + col);
    }

    size_type cols() const { return _num_cols; }
    size_type rows() const { return _num_rows; }

    iterator begin() { return _buffer.begin(); };
    const_iterator begin() const { return _buffer.begin(); };
    const_iterator cbegin() const { return _buffer.cbegin(); };
    reverse_iterator rbegin() { return _buffer.rbegin(); };
    const_reverse_iterator rbegin() const { return _buffer.rbegin(); };
    const_reverse_iterator crbegin() const { return _buffer.crbegin(); };
    iterator end() { return _buffer.end(); };
    const_iterator end() const { return _buffer.end(); };
    const_iterator cend() const { return _buffer.cend(); };
    reverse_iterator rend() { return _buffer.rend(); };
    const_reverse_iterator rend() const { return _buffer.rend(); };
    const_reverse_iterator crend() const { return _buffer.crend(); };

    horizontal_iterator row_begin(size_type row_index) { return row_begin<horizontal_iterator>(_buffer.data(), row_index); }
    const_horizontal_iterator row_begin(size_type row_index) const { return row_begin<const_horizontal_iterator>(_buffer.data(), row_index); }
    const_horizontal_iterator row_cbegin(size_type row_index) const { return row_begin<const_horizontal_iterator>(_buffer.data(), row_index); }
    reverse_horizontal_iterator row_rbegin(size_type row_index) { return reverse_horizontal_iterator { row_end(row_index) }; }
    const_reverse_horizontal_iterator row_rbegin(size_type row_index) const { return const_reverse_horizontal_iterator { row_cend(row_index) }; }
    const_reverse_horizontal_iterator row_crbegin(size_type row_index) const { return const_reverse_horizontal_iterator { row_cend(row_index) }; }
    horizontal_iterator row_end(size_type row_index) { return row_end<horizontal_iterator>(_buffer.data(), row_index); }
    const_horizontal_iterator row_end(size_type row_index) const { return row_end<const_horizontal_iterator>(_buffer.data(), row_index); }
    const_horizontal_iterator row_cend(size_type row_index) const { return row_end<const_horizontal_iterator>(_buffer.data(), row_index); }
    reverse_horizontal_iterator row_rend(size_type row_index) { return reverse_horizontal_iterator { row_begin(row_index) }; }
    const_reverse_horizontal_iterator row_rend(size_type row_index) const { return const_reverse_horizontal_iterator { row_cbegin(row_index) }; }
    const_reverse_horizontal_iterator row_crend(size_type row_index) const { return const_reverse_horizontal_iterator { row_cbegin(row_index) }; }

    vertical_iterator col_begin(size_type col_index) { return col_begin<vertical_iterator>(_buffer.data(), col_index); }
    const_vertical_iterator col_begin(size_type col_index) const { return col_begin<const_vertical_iterator>(_buffer.data(), col_index); }
    const_vertical_iterator col_cbegin(size_type col_index) const { return col_begin<const_vertical_iterator>(_buffer.data(), col_index); }
    reverse_vertical_iterator col_rbegin(size_type col_index) { return reverse_vertical_iterator { col_end(col_index) }; }
    const_reverse_vertical_iterator col_rbegin(size_type col_index) const { return const_reverse_vertical_iterator { col_cend(col_index) }; }
    const_reverse_vertical_iterator col_crbegin(size_type col_index) const { return const_reverse_vertical_iterator { col_cend(col_index) }; }
    vertical_iterator col_end(size_type col_index) { return col_end<vertical_iterator>(_buffer.data(), col_index); }
    const_vertical_iterator col_end(size_type col_index) const { return col_end<const_vertical_iterator>(_buffer.data(), col_index); }
    const_vertical_iterator col_cend(size_type col_index) const { return col_end<const_vertical_iterator>(_buffer.data(), col_index); }
    reverse_vertical_iterator col_rend(size_type col_index) { return reverse_vertical_iterator { col_begin(col_index) }; }
    const_reverse_vertical_iterator col_rend(size_type col_index) const { return const_reverse_vertical_iterator { col_cbegin(col_index) }; }
    const_reverse_vertical_iterator col_crend(size_type col_index) const { return const_reverse_vertical_iterator { col_cbegin(col_index) }; }

private:
    size_type _num_rows;
    size_type _num_cols;
    std::vector<T> _buffer;

    void check_row(size_type row) const
    {
        if (row >= _num_rows) {
            throw std::out_of_range("row index out of range");
        }
    }
    void check_col(size_type col) const
    {
        if (col >= _num_cols) {
            throw std::out_of_range("column index out of range");
        }
    }

    template <typename Iterator>
    Iterator row_begin(typename Iterator::pointer begin, size_type row_index) const
    {
        check_row(row_index);
        return Iterator { begin + _num_cols * row_index };
    }

    template <typename Iterator>
    Iterator row_end(typename Iterator::pointer begin, size_type row_index) const
    {
        check_row(row_index);
        return Iterator { begin + _num_cols * (row_index + 1) };
    }

    template <typename Iterator>
    Iterator col_begin(typename Iterator::pointer begin, size_type col_index) const
    {
        check_col(col_index);
        return Iterator { begin + col_index, static_cast<typename Iterator::difference_type>(_num_cols) };
    }

    template <typename Iterator>
    Iterator col_end(typename Iterator::pointer begin, size_type col_index) const
    {
        check_col(col_index);
        return Iterator { begin + col_index + _num_rows * _num_cols, static_cast<typename Iterator::difference_type>(_num_cols) };
    }
};

}
