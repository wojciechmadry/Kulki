// Copyright [2021] <Wojtek>"
#ifndef BABLIB_MATRIX_MATRIX_HPP_
#define BABLIB_MATRIX_MATRIX_HPP_

#include "operator_on_matrix.hpp"


namespace babel::MATRIX{
    constexpr const char *READ_BEFORE_USE = "babel::MATRIX is not ended !!! Work in progress";

    template< typename T >
    requires babel::CONCEPTS::IS_ARITHMETIC<T>
    class matrix
    {
        using POSITION = uint64_t;
        std::vector<std::vector<T>> mat;
    public:
        matrix() = default;

        ~matrix() = default;

        matrix(size_t rows, size_t columns, T data = 0) noexcept: mat(rows, std::vector<T>(columns, data))
        { }

        matrix(const matrix &other) noexcept: mat(other.mat)
        { }

        matrix(matrix &&other) noexcept: mat(std::move(other.mat))
        { }

        matrix(std::initializer_list<T> init_list) noexcept: mat(init_list)
        { }

        matrix(std::initializer_list<std::initializer_list<T>> init_list) noexcept
        {
            std::copy(std::begin(init_list), std::end(init_list), std::back_inserter(mat));
        }


        matrix &operator=(std::initializer_list<std::initializer_list<T>> init_list) noexcept
        {
            mat.clear();
            std::copy(std::begin(init_list), std::end(init_list), std::back_inserter(mat));
            return *this;
        }

        matrix &operator=(matrix &&other) noexcept
        {
            mat = std::move(other.mat);
            return *this;
        }

        matrix &operator=(const matrix &other) noexcept
        {
            mat = other.mat;
            return *this;
        }

        T &at(POSITION first)
        {
            if ( mat.empty() || mat[0].size() <= first )
                throw std::out_of_range("Matrix out ouf range.");
            return mat[0][first];
        }

        T &at(POSITION first, POSITION second)
        {
            if ( first >= mat.size() || mat[first].size() <= second )
                throw std::out_of_range("Matrix out ouf range.");
            return mat[first][second];
        }

        const T &at(POSITION first) const
        {
            if ( mat.empty() || mat[0].size() <= first )
                throw std::out_of_range("Matrix out ouf range.");
            return mat[0][first];
        }

        const T &at(POSITION first, POSITION second) const
        {
            if ( first >= mat.size() || mat[first].size() <= second )
                throw std::out_of_range("Matrix out ouf range.");
            return mat[first][second];
        }

        T &operator()(POSITION first)
        {
            if ( mat.empty() || mat[0].size() <= first )
                throw std::out_of_range("Matrix out ouf range.");
            return mat[0][first];
        }

        const T &operator()(POSITION first) const
        {
            if ( mat.empty() || mat[0].size() <= first )
                throw std::out_of_range("Matrix out ouf range.");
            return mat[0][first];
        }

        T &operator()(POSITION first, POSITION second)
        {
            if ( first >= mat.size() || mat[first].size() <= second )
                throw std::out_of_range("Matrix out ouf range.");
            return mat[first][second];
        }

        const T &operator()(POSITION first, POSITION second) const
        {
            if ( first >= mat.size() || mat[first].size() <= second )
                throw std::out_of_range("Matrix out ouf range.");
            return mat[first][second];
        }

        [[nodiscard]] size_t rows() const noexcept
        {
            return mat.size();
        }

        [[nodiscard]] size_t cols() const noexcept
        {
            return mat.empty() ? 0 : mat[0].size();
        }

        matrix &add(const T number) noexcept
        {
            auto row = rows();
            auto col = cols();
            for ( auto i = 0 ; i < row ; ++i )
                for ( auto j = 0 ; j < col ; ++j )
                    mat[i][j] += number;
            return *this; //NOLINT
        }

        template< typename U = double >
        matrix &add(const matrix<U> &Matrix)
        {
            auto row = rows();
            auto col = cols();
            if ( row != Matrix.rows() || col != Matrix.cols() )
                throw std::out_of_range("Matrix must be the same size.");
            for ( auto i = 0 ; i < row ; ++i )
                for ( auto j = 0 ; j < col ; ++j )
                    mat[i][j] += Matrix.mat[i][j];
            return *this;
        }

        matrix &subtract(const T number) noexcept
        {
            auto row = rows();
            auto col = cols();
            for ( auto i = 0 ; i < row ; ++i )
                for ( auto j = 0 ; j < col ; ++j )
                    mat[i][j] -= number;
            return *this; //NOLINT
        }

        template< typename U = double >
        matrix &subtract(const matrix<U> &Matrix)
        {
            auto row = rows();
            auto col = cols();
            if ( row != Matrix.rows() || col != Matrix.cols() )
                throw std::out_of_range("Matrix must be the same size.");
            for ( auto i = 0 ; i < row ; ++i )
                for ( auto j = 0 ; j < col ; ++j )
                    mat[i][j] -= Matrix.mat[i][j];
            return *this;
        }

        matrix &mult(const T number) noexcept
        {
            auto row = rows();
            auto col = cols();
            for ( auto i = 0 ; i < row ; ++i )
                for ( auto j = 0 ; j < col ; ++j )
                    mat[i][j] *= number;
            return *this; //NOLINT
        }

        matrix &transpose() noexcept
        {
            auto col = cols();
            auto row = rows();
            if ( col == row )
            {
                for ( size_t i = 0 ; i < col - 1 ; ++i )
                    for ( size_t j = i + 1 ; j < col ; ++j )
                    {
                        T _temp = mat[i][j];
                        mat[i][j] = mat[j][i];
                        mat[j][i] = _temp;
                    }
            } else
            {
                std::vector<std::vector<T>> new_mat(col, std::vector<T>(row, 0));
                for ( size_t i = 0 ; i < mat.size() ; ++i )
                    for ( size_t j = 0 ; j < mat[i].size() ; ++j )
                        new_mat[j][i] = mat[i][j];
                mat = std::move(new_mat);
            }
            return *this;
        }

        template< typename U = double >
        matrix &mult(const matrix<U> &Matrix)
        {
            auto row = rows();
            auto col = cols();
            if ( col != Matrix.rows() )
                throw std::out_of_range(
                        "Number of columns of 1st matrix must be equal to number of rows of second matrix");
            matrix<T> new_matrix(row, Matrix.cols(), 0);
            constexpr int algo = 1;
            switch (algo)
            {
                case 1:
                {
                    // Iterative algorithm
                    T _sum;
                    auto sec_cols = Matrix.cols();
                    for ( size_t i = 0 ; i < row ; ++i )
                        for ( size_t j = 0 ; j < sec_cols ; ++j )
                        {
                            _sum = 0;
                            for ( size_t k = 0 ; k < col ; ++k )
                                _sum += mat[i][k] * Matrix.mat[k][j];
                            new_matrix.mat[i][j] = _sum;
                        }
                    break;
                }
            }
            mat = std::move(new_matrix.mat);
            return *this; //NOLINT
        }

        [[nodiscard]] std::string to_string() const noexcept
        {
            //Can be faster !
            std::string res;
            for ( auto rows_it : mat )
            {
                for ( auto cols_it : rows_it )
                    res += std::to_string(cols_it) + ' ';
                res += '\n';
            }
            return res;
        }

        std::vector<T> get_row(size_t row) const
        {
            if ( row >= rows() )
                throw std::out_of_range("Row out ouf range.");
            return mat[row];
        }

        std::vector<T> get_coll(size_t coll) const
        {
            if ( coll >= cols() )
                throw std::out_of_range("Coll out ouf range.");
            std::vector<T> _colls(mat.size());
            for ( size_t i = 0 ; i < _colls.size() ; ++i )
                _colls[i] = mat[i][coll];
            return _colls;
        }

        template< typename Op = std::plus<T>>
        matrix<T> &operator_to_row(T number, size_t row)
        {
            if ( row >= rows() )
                throw std::out_of_range("Row out ouf range.");
            for ( size_t i = 0 ; i < mat[row].size() ; ++i )
                mat[row][i] = Op { }(mat[row][i], number);
            return *this;
        }

        template< typename Op = std::plus<T>>
        matrix<T> &operator_to_coll(T number, size_t coll)
        {
            if ( coll >= cols() )
                throw std::out_of_range("Coll out ouf range.");
            for ( size_t i = 0 ; i < mat.size() ; ++i )
                mat[i][coll] = Op { }(mat[i][coll], number);
            return *this;
        }

        matrix<T> &swap_rows(size_t first, size_t second)
        {
            if ( first >= rows() || second >= rows() )
                throw std::out_of_range("Rows out ouf range.");
            std::swap(mat[first], mat[second]);
            return *this;
        }

        matrix<T> &swap_cols(size_t first, size_t second)
        {
            if ( first >= cols() || second >= cols() )
                throw std::out_of_range("Cols out ouf range.");
            for ( size_t i = 0 ; i < mat.size() ; ++i )
            {
                T temp = mat[i][first];
                mat[i][first] = mat[i][second];
                mat[i][second] = temp;
            }
            return *this;
        }

        matrix<T> &swap(matrix &other) noexcept
        {
            std::swap(other.mat, mat);
            return *this;
        }
    };

    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T>
    operator+(const babel::MATRIX::matrix<T> &Matrix1, const babel::MATRIX::matrix<U> &Matrix2)
    {
        return babel::MATRIX::add(Matrix1, Matrix2);
    }

    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T> operator+(const babel::MATRIX::matrix<T> &Matrix, const U number)
    {
        return babel::MATRIX::add(Matrix, number);
    }

    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T> operator+(const U number, const babel::MATRIX::matrix<T> &Matrix)
    {
        return babel::MATRIX::add(Matrix, number);
    }

    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T> &
    operator+=(babel::MATRIX::matrix<T> &Matrix1, const babel::MATRIX::matrix<U> &Matrix2)
    {
        Matrix1.add(Matrix2);
        return Matrix1;
    }


    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T> &operator+=(babel::MATRIX::matrix<T> &Matrix, const U number)
    {
        Matrix.add(number);
        return Matrix;
    }

    template< typename T >
    inline babel::MATRIX::matrix<T> &operator++(babel::MATRIX::matrix<T> &Matrix)
    {
        Matrix.add(1);
        return Matrix;
    }

    template< typename T >
    inline const babel::MATRIX::matrix<T> operator++(babel::MATRIX::matrix<T> &Matrix, int) //NOLINT
    {
        auto cpy = Matrix;
        ++Matrix;
        return cpy;
    }


    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T>
    operator-(const babel::MATRIX::matrix<T> &Matrix1, const babel::MATRIX::matrix<U> &Matrix2)
    {
        return babel::MATRIX::subtract(Matrix1, Matrix2);
    }

    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T> operator-(const babel::MATRIX::matrix<T> &Matrix, const U number)
    {
        return babel::MATRIX::subtract(Matrix, number);
    }

    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T> operator-(const U number, const babel::MATRIX::matrix<T> &Matrix)
    {
        return babel::MATRIX::subtract(Matrix, number);
    }

    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T> &
    operator-=(babel::MATRIX::matrix<T> &Matrix1, const babel::MATRIX::matrix<U> &Matrix2)
    {
        Matrix1.subtract(Matrix2);
        return Matrix1;
    }


    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T> &operator-=(babel::MATRIX::matrix<T> &Matrix, const U number)
    {
        Matrix.subtract(number);
        return Matrix;
    }

    template< typename T >
    inline babel::MATRIX::matrix<T> &operator--(babel::MATRIX::matrix<T> &Matrix)
    {
        Matrix.subtract(1);
        return Matrix;
    }

    template< typename T >
    inline const babel::MATRIX::matrix<T> operator--(babel::MATRIX::matrix<T> &Matrix, int) //NOLINT
    {
        auto cpy = Matrix;
        --Matrix;
        return cpy;
    }


    template< typename T = double, typename U = double >
    inline babel::MATRIX::matrix<T>
    operator*(const babel::MATRIX::matrix<T> &Matrix1, const babel::MATRIX::matrix<U> &Matrix2) noexcept
    {
        auto cpy = Matrix1;
        cpy.mult(Matrix2);
        return cpy;
    }
/*
    template<typename T>
    babel::MATRIX::matrix<T> operator-(const babel::MATRIX::matrix<T>& Matrix) //NOLINT
    {
        auto cpy = Matrix;
        cpy.
        return cpy;
    }*/



}  // namespace babel::MATRIX
#endif  // BABLIB_MATRIX_MATRIX_HPP_
