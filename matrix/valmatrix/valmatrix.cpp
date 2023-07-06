namespace lasd
{
    // Destructor
    template<typename Data>
    ValMatrix<Data>::~ValMatrix()
    {
        for (std::size_t i = 0; i < matrix.Size(); ++i)
        {
            matrix[i].Clear();
        }
        matrix.Clear();
    }

    /* ************************************************************************ */

    // Copy assignment
    template<typename Data>
    ValMatrix<Data>& ValMatrix<Data>::operator=(const ValMatrix& m)
    {
        if (this != &m)
        {
            matrix = m.matrix;
            size = m.size;
            rows = m.rows;
            cols = m.cols;
        }
        return *this;
    }

    // Move assignment
    template<typename Data>
    ValMatrix<Data>& ValMatrix<Data>::operator=(ValMatrix&& m) noexcept
    {
        if (this != &m)
        {
            matrix = std::move(m.matrix);
            size = std::move(m.size);
            rows = std::move(m.rows);
            cols = std::move(m.cols);
        }
        return *this;
    }

    /* ************************************************************************ */

    // Comparison operators
    template<typename Data>
    bool ValMatrix<Data>::operator==(const ValMatrix& m) const noexcept
    {
        if (size == m.size && cols == m.cols && rows == m.rows)
        {
            for (std::size_t i = 0; i < rows; ++i)
            {
                for (std::size_t j = 0; j < cols; ++j)
                {
                    if (matrix[i][j] != m.matrix[i][j])
                        return false;
                }
            }
        }
        else
            return false;
        return true;
    }

    template<typename Data>
    bool ValMatrix<Data>::operator!=(const ValMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    template<typename Data>
    ValMatrix<Data> ValMatrix<Data>::Transpose()
    {
        ValMatrix<Data> newMatrix(cols,rows);
        for(std::size_t i = 0; i < rows; ++i)
        {
            for(std::size_t j = 0; j < cols; ++j)
            {
                newMatrix[j][i] = matrix[i][j];
            }
        }
        return newMatrix;
    }

    template<typename Data>
    ValMatrix<Data> ValMatrix<Data>::operator+(const ValMatrix<Data>& other) const
    {
        if(rows == other.rows && cols == other.cols)
        {
            ValMatrix<Data> newMatrix(rows,cols);
            for(std::size_t i = 0; i < rows; ++i)
            {
                for(std::size_t j = 0; j < cols; ++j)
                {
                    newMatrix[i][j] = matrix[i][j] + other.matrix[i][j];
                }
            }
            return newMatrix;
        }
        else
            throw std::length_error("Tried to add two matrices with different sizes!");
    }

    template<typename Data>
    ValMatrix<Data> ValMatrix<Data>::operator*(const ValMatrix<Data>& other) const
    {
        if (cols != other.rows) {
            throw std::length_error("Tried to multiply two matrices with incompatible sizes!");
        }
        ValMatrix<Data> result(rows, other.cols);
        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < other.cols; ++j) {
                for (std::size_t k = 0; k < cols; ++k) {
                    result[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    template<typename Data>
    ValMatrix<Data> ValMatrix<Data>::operator*(const auto& other) const
    {
        ValMatrix<Data> newMatrix(rows,cols);
        for(std::size_t i = 0; i < rows; ++i)
        {
            for(std::size_t j = 0; j < cols; ++j)
            {
                newMatrix[i][j] = matrix[i][j] * other;
            }
        }
        return newMatrix;
    }
    template<typename Data>
    ValMatrix<Data> ValMatrix<Data>::SubMatrixRemoving(std::size_t rowToExclude,std::size_t colToExclude) const
    {
        ValMatrix<Data> subMatrix(rows-1,cols-1);
        std::size_t subi = 0;
        for(std::size_t i = 0; i < rows; ++i)
        {
            if(i != rowToExclude)
            {
                std::size_t subj = 0;
                for(std::size_t j = 0; j < cols; ++j)
                {
                    if(j != colToExclude)
                    {
                        subMatrix[subi][subj] = matrix[i][j];
                        subj++;
                    }
                }
                subi++;
            }
        }
        return subMatrix;
    }
    template<typename Data>
    Data ValMatrix<Data>::Determinant() const
    {
        if(rows != cols)
            throw std::length_error("The matrix isn't a square matrix!");
        if(rows == 1)
            return matrix[0][0];
        if(rows == 2)
            return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);

        Data det{};
        short sign = 1;
        for(std::size_t i = 0; i < rows; ++i)
        {
            det += sign * matrix[i][0] * SubMatrixRemoving(i,0).Determinant();
            sign *= -1;
        }

        return det;
    }

    template<typename Data>
    ValMatrix<Data> ValMatrix<Data>::Inverse() const
    {

    }
}
