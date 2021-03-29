#ifndef babel_MATRIX_operator_on_matrix
#define babel_MATRIX_operator_on_matrix

#include "../must_have.hpp"

namespace babel::MATRIX{
    template< typename T = double >
    requires babel::CONCEPTS::IS_ARITHMETIC<T>
    class matrix;

    using POSITION = long long int;

    template< typename T = double >
    matrix<T> zeros(const POSITION first_size, const POSITION second_size = -1) noexcept
    {
        if ( second_size == -1 )
            return matrix<T>(first_size, first_size, 0);
        return matrix<T>(first_size, second_size, 0);
    }

    template< typename T = double >
    matrix<T> ones(const POSITION first_size, const POSITION second_size = -1) noexcept
    {
        if ( second_size == -1 )
            return matrix<T>(first_size, first_size, 1);
        return matrix<T>(first_size, second_size, 1);
    }

    template< typename T = double, typename U = double >
    matrix<T> add(const matrix<T> &Matrix, const U number) noexcept
    {
        matrix<T> cpy = Matrix;
        auto rows = Matrix.rows();
        auto cols = Matrix.cols();
        for ( auto i = 0 ; i < rows ; ++i )
            for ( auto j = 0 ; j < cols ; ++j )
                cpy(i, j) +=  number;
        return cpy;
    }


    template< typename T = double, typename U = double >
    matrix<T> add(const matrix<T> &Matrix1, const matrix<U> &Matrix2)
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
    matrix<T> subtract(const matrix<T> &Matrix, const U number) noexcept
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
    matrix<T> subtract(const matrix<T> &Matrix1, const matrix<U> &Matrix2)
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
    matrix<T> transpose(const matrix<T> &Matrix1) noexcept
    {
       return matrix<T>(Matrix1).transpose();
    }


}

#endif