#ifndef LASD_VALMATRIX_HPP
#define LASD_VALMATRIX_HPP

#include "../matrix.hpp"

namespace lasd
{
    template<typename Data>
    class ValMatrix: virtual public Matrix<Data>
    {
    private:
        ValMatrix<Data> SubMatrixRemoving(std::size_t rowToExclude,std::size_t colToExclude);
    protected:
        using Matrix<Data>::rows;
        using Matrix<Data>::cols;
        using Matrix<Data>::size;
        using Matrix<Data>::matrix;
    public:
        using Matrix<Data>::Matrix;

        // Copy constructor
        ValMatrix(const ValMatrix& m) : Matrix<Data>(m) {}

        // Move constructor
        ValMatrix(ValMatrix&& m) noexcept : Matrix<Data>(m) {}

        /* ************************************************************************ */

        // Destructor
        ~ValMatrix() override;

        /* ************************************************************************ */

        // Copy assignment
        ValMatrix& operator=(const ValMatrix& m);

        // Move assignment
        ValMatrix& operator=(ValMatrix&& m) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const ValMatrix& m) const noexcept;

        bool operator!=(const ValMatrix& m) const noexcept;

        /* ************************************************************************ */
        ValMatrix<Data> Transpose();
        ValMatrix<Data>& operator+(const ValMatrix<Data>& other);
        ValMatrix<Data>& operator*(const ValMatrix<Data>& other);
        ValMatrix<Data>& operator*(const auto& other);
        Data Determinant();
        ValMatrix<Data>& Inverse();
    };



}



#include "valmatrix.cpp"
#endif //LASD_VALMATRIX_HPP
