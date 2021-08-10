// Copyright [2021] <Wojtek>"
#ifndef BABLIB_MATRIX_OPERATOR_ON_MATRIX_HPP_
#define BABLIB_MATRIX_OPERATOR_ON_MATRIX_HPP_

#include "../concepts/concepts.hpp"
#include <cstdint>
#include <numeric>
#include <vector>

namespace babel::MATRIX{
    template< typename T = double >
    requires babel::CONCEPTS::IS_ARITHMETIC<T>
    class matrix;

    using POSITION = uint64_t;

    template< typename T = double >
    inline matrix<T>
    zeros(const POSITION first_size, const POSITION second_size = std::numeric_limits<POSITION>::max()) noexcept
    {
        if ( second_size == std::numeric_limits<POSITION>::max() )
            return matrix<T>(first_size, first_size, 0);
        return matrix<T>(first_size, second_size, 0);
    }

    template< typename T = double >
    inline matrix<T>
    ones(const POSITION first_size, const POSITION second_size = std::numeric_limits<POSITION>::max()) noexcept
    {
        if ( second_size == std::numeric_limits<POSITION>::max() )
            return matrix<T>(first_size, first_size, 1);
        return matrix<T>(first_size, second_size, 1);
    }

    template< typename T = double, typename U = double >
    inline matrix<T> add(const matrix<T> &Matrix, const U number) noexcept
    {
        matrix<T> cpy = Matrix;
        auto rows = Matrix.rows();
        auto cols = Matrix.cols();
        for ( auto i = 0 ; i < rows ; ++i )
            for ( auto j = 0 ; j < cols ; ++j )
                cpy(i, j) += number;
        return cpy;
    }


    template< typename T = double, typename U = double >
    inline matrix<T> add(const matrix<T> &Matrix1, const matrix<U> &Matrix2)
    {
        auto rows = Matrix1.rows();
        auto cols = Matrix1.cols();
        if ( rows != Matrix2.rows() || cols != Matrix2.cols() )
            throw std::out_of_range("Matrix must be the same size.");
        matrix<T> cpy = Matrix1;
        for ( auto i = 0 ; i < rows ; ++i )
            for ( auto j = 0 ; j < cols ; ++j )
                cpy(i, j) += Matrix2(i, j);
        return cpy;
    }

    template< typename T = double, typename U = double >
    inline matrix<T> subtract(const matrix<T> &Matrix, const U number) noexcept
    {
        matrix<T> cpy = Matrix;
        auto rows = Matrix.rows();
        auto cols = Matrix.cols();
        for ( auto i = 0 ; i < rows ; ++i )
            for ( auto j = 0 ; j < cols ; ++j )
                cpy(i, j) -= number;
        return cpy;
    }


    template< typename T = double, typename U = double >
    inline matrix<T> subtract(const matrix<T> &Matrix1, const matrix<U> &Matrix2)
    {
        auto rows = Matrix1.rows();
        auto cols = Matrix1.cols();
        if ( rows != Matrix2.rows() || cols != Matrix2.cols() )
            throw std::out_of_range("Matrix must be the same size.");
        matrix<T> cpy = Matrix1;
        for ( auto i = 0 ; i < rows ; ++i )
            for ( auto j = 0 ; j < cols ; ++j )
                cpy(i, j) -= Matrix2(i, j);
        return cpy;
    }

    template< typename T = double >
    inline matrix<T> transpose(const matrix<T> &Matrix1) noexcept
    {
        return matrix<T>(Matrix1).transpose();
    }

}  // namespace babel::MATRIX

#endif  // BABLIB_MATRIX_OPERATOR_ON_MATRIX_HPP_
