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
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                newMatrix[j][i] = matrix[i][j];
            }
        }
        return newMatrix;
    }

    template<typename Data>
    ValMatrix<Data>& ValMatrix<Data>::operator+(const ValMatrix<Data>& other)
    {
        if(rows == other.rows && cols == other.cols)
        {
            ValMatrix<Data> newMatrix(rows,cols);
            for(int i = 0; i < rows; ++i)
            {
                for(int j = 0; j < cols; ++j)
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
    ValMatrix<Data>& ValMatrix<Data>::operator*(const ValMatrix<Data>& other)
    {

    }

    template<typename Data>
    ValMatrix<Data>& ValMatrix<Data>::operator*(const auto& other)
    {
        if(rows == other.rows && cols == other.cols)
        {
            ValMatrix<Data> newMatrix(rows,cols);
            for(int i = 0; i < rows; ++i)
            {
                for(int j = 0; j < cols; ++j)
                {
                    newMatrix[i][j] = matrix[i][j] * other;
                }

            }
            return newMatrix;
        }
    }
    template<typename Data>
    ValMatrix<Data> ValMatrix<Data>::SubMatrixRemoving(std::size_t rowToExclude,std::size_t colToExclude)
    {
        ValMatrix<Data> subMatrix;
        for(int i = 0; i < rows; i++)
        {
            if(i != rowToExclude)
            {
                Vector<Data> rowVec;
                for(int j = 0; j < cols; j++)
                {
                    if(j != colToExclude)
                    {
                        rowVec.Insert(matrix[i][j]);
                    }
                }
                subMatrix.matrix.Insert(rowVec);
            }
        }
        return subMatrix;
    }
    template<typename Data>
    Data ValMatrix<Data>::Determinant()
    {
        if(rows != cols)
            throw std::length_error("");
        if(rows == 1)
            return matrix[0][0];
        if(rows == 2)
            return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);

        Data det{};
        int sign = 1;
        for(int i = 0; i < rows; ++i)
        {
            auto subMatrix = SubMatrixRemoving(0,i);
            det += sign * matrix[0][i] * subMatrix.Determinant();
            sign *= -1;
        }

        return det;
    }

    template<typename Data>
    ValMatrix<Data>& ValMatrix<Data>::Inverse()
    {

    }
}
