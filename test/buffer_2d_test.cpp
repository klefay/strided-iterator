#include <catch2/catch.hpp>

#include <buffer_2d.hpp>

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace {
auto equal_zero = [](const auto& elem) { return elem == 0; };
void print_buffer(const my::buffer_2d<int>& buffer, const std::string& label = "Buffer")
{
    const size_t rows = buffer.rows();
    const size_t cols = buffer.cols();

    std::cout << label << ":" << std::endl;
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            std::cout << std::setw(2) << buffer.at(r, c) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
}

TEST_CASE("Buffer", "[buffer_2d]")
{
    constexpr size_t width = 8u;
    constexpr size_t height = 5u;
    my::buffer_2d<int> buffer { width, height };
    const auto rows = buffer.rows();
    const auto cols = buffer.cols();
    REQUIRE(rows == width);
    REQUIRE(cols == height);

    SECTION("Buffer should have accessible as a 1D array")
    {
        CHECK(std::all_of(buffer.begin(), buffer.end(), equal_zero));
        CHECK(std::all_of(buffer.cbegin(), buffer.cend(), equal_zero));
        print_buffer(buffer, "After construction");

        std::iota(buffer.begin(), buffer.end(), 1);
        CHECK(std::none_of(buffer.cbegin(), buffer.cend(), equal_zero));
        CHECK(std::is_sorted(buffer.cbegin(), buffer.cend()));
        print_buffer(buffer, "After iota in order");

        std::iota(buffer.rbegin(), buffer.rend(), 1);
        CHECK(std::is_sorted(buffer.rbegin(), buffer.rend()));
        CHECK(not std::is_sorted(buffer.cbegin(), buffer.cend()));
        print_buffer(buffer, "After iota out of order");

        std::reverse(buffer.begin(), buffer.end());
        CHECK(std::is_sorted(buffer.cbegin(), buffer.cend()));
        CHECK(not std::is_sorted(buffer.rbegin(), buffer.rend()));
        CHECK(not std::is_sorted(buffer.crbegin(), buffer.crend()));
        print_buffer(buffer, "After reverse");
    }

    SECTION("Buffer should allow row processing")
    {
        for (size_t row_index = 0; row_index < rows; row_index++) {
            CHECK(std::all_of(buffer.row_begin(row_index), buffer.row_end(row_index), equal_zero));
            CHECK(std::all_of(buffer.row_cbegin(row_index), buffer.row_cend(row_index), equal_zero));
        }
        print_buffer(buffer, "After construction");

        for (size_t row_index = 0; row_index < rows; row_index++) {
            std::iota(buffer.row_begin(row_index), buffer.row_end(row_index), 1);
            CHECK(std::none_of(buffer.row_cbegin(row_index), buffer.row_cend(row_index), equal_zero));
            CHECK(std::is_sorted(buffer.row_cbegin(row_index), buffer.row_cend(row_index)));
        }
        print_buffer(buffer, "After iota in order");

        for (size_t row_index = 0; row_index < rows; row_index++) {
            std::iota(buffer.row_rbegin(row_index), buffer.row_rend(row_index), 1);
            CHECK(std::is_sorted(buffer.row_rbegin(row_index), buffer.row_rend(row_index)));
            CHECK(not std::is_sorted(buffer.row_cbegin(row_index), buffer.row_cend(row_index)));
        }
        print_buffer(buffer, "After iota out of order");

        for (size_t row_index = 0; row_index < rows; row_index++) {
            std::reverse(buffer.row_begin(row_index), buffer.row_end(row_index));
            CHECK(std::is_sorted(buffer.row_cbegin(row_index), buffer.row_cend(row_index)));
            CHECK(not std::is_sorted(buffer.row_rbegin(row_index), buffer.row_rend(row_index)));
            CHECK(not std::is_sorted(buffer.row_crbegin(row_index), buffer.row_crend(row_index)));
        }
        print_buffer(buffer, "After reverse");

        SECTION("Buffer should throw if row index is out of range")
        {
            CHECK_THROWS_AS(buffer.row_begin(rows), std::out_of_range);
            CHECK_THROWS_AS(buffer.row_cbegin(rows), std::out_of_range);
            CHECK_THROWS_AS(buffer.row_rbegin(rows), std::out_of_range);
            CHECK_THROWS_AS(buffer.row_crbegin(rows), std::out_of_range);
            CHECK_THROWS_AS(buffer.row_end(rows), std::out_of_range);
            CHECK_THROWS_AS(buffer.row_cend(rows), std::out_of_range);
            CHECK_THROWS_AS(buffer.row_rend(rows), std::out_of_range);
            CHECK_THROWS_AS(buffer.row_crend(rows), std::out_of_range);
        }
    }

    SECTION("Buffer should allow column processing")
    {
        for (size_t col_index = 0; col_index < cols; col_index++) {
            CHECK(std::all_of(buffer.col_begin(col_index), buffer.col_end(col_index), equal_zero));
            CHECK(std::all_of(buffer.col_cbegin(col_index), buffer.col_cend(col_index), equal_zero));
        }
        print_buffer(buffer, "After construction");

        for (size_t col_index = 0; col_index < cols; col_index++) {
            std::iota(buffer.col_begin(col_index), buffer.col_end(col_index), 1);
            CHECK(std::none_of(buffer.col_cbegin(col_index), buffer.col_cend(col_index), equal_zero));
            CHECK(std::is_sorted(buffer.col_cbegin(col_index), buffer.col_cend(col_index)));
        }
        print_buffer(buffer, "After iota in order");

        for (size_t col_index = 0; col_index < cols; col_index++) {
            std::iota(buffer.col_rbegin(col_index), buffer.col_rend(col_index), 1);
            CHECK(std::is_sorted(buffer.col_rbegin(col_index), buffer.col_rend(col_index)));
            CHECK(not std::is_sorted(buffer.col_cbegin(col_index), buffer.col_cend(col_index)));
        }
        print_buffer(buffer, "After iota out of order");

        for (size_t col_index = 0; col_index < cols; col_index++) {
            std::reverse(buffer.col_begin(col_index), buffer.col_end(col_index));
            CHECK(std::is_sorted(buffer.col_cbegin(col_index), buffer.col_cend(col_index)));
            CHECK(not std::is_sorted(buffer.col_rbegin(col_index), buffer.col_rend(col_index)));
            CHECK(not std::is_sorted(buffer.col_crbegin(col_index), buffer.col_crend(col_index)));
        }
        print_buffer(buffer, "After reverse");

        SECTION("Buffer should throw if column index is out of range")
        {
            CHECK_THROWS_AS(buffer.col_begin(cols), std::out_of_range);
            CHECK_THROWS_AS(buffer.col_cbegin(cols), std::out_of_range);
            CHECK_THROWS_AS(buffer.col_rbegin(cols), std::out_of_range);
            CHECK_THROWS_AS(buffer.col_crbegin(cols), std::out_of_range);
            CHECK_THROWS_AS(buffer.col_end(cols), std::out_of_range);
            CHECK_THROWS_AS(buffer.col_cend(cols), std::out_of_range);
            CHECK_THROWS_AS(buffer.col_rend(cols), std::out_of_range);
            CHECK_THROWS_AS(buffer.col_crend(cols), std::out_of_range);
        }
    }
}
