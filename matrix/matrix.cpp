#include <utility>
namespace lasd
{

	/* ************************************************************************ */
	// Specific constructors
	template<typename Data>
	Matrix<Data>::Matrix(const std::size_t rowSize, const std::size_t colSize)
	{
		matrix.Resize(rowSize);
		for (std::size_t i = 0; i < matrix.Size(); ++i)
			matrix[i].Resize(colSize);
		size = rowSize * colSize;
		rows = rowSize;
		cols = colSize;
	}

	template<typename Data>
	Matrix<Data>::Matrix(const std::size_t rowSize, const std::size_t colSize, const Data defaultValue) : Matrix(rowSize, colSize)
	{
		for (std::size_t i = 0; i < matrix.Size(); ++i)
		{
			for (std::size_t j = 0; j < matrix[0].Size(); ++j)
			{
				matrix[i][j] = defaultValue;
			}
		}
	}



	/* ************************************************************************ */

	// Copy constructor
	template<typename Data>
	Matrix<Data>::Matrix(const Matrix<Data>& m) : rows(m.rows), cols(m.cols), matrix(m.matrix)
	{
		size = m.size;
	}

	// Move constructor
	template<typename Data>
	Matrix<Data>::Matrix(Matrix<Data>&& m) noexcept : rows(std::move(m.rows)), cols(std::move(m.cols)), matrix(std::move(m.matrix))
	{
		size = std::move(m.size);
	}

	/* ************************************************************************ */

	// Destructor
	template<typename Data>
	Matrix<Data>::~Matrix()
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
	Matrix<Data>& Matrix<Data>::operator=(const Matrix& m)
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
	Matrix<Data>& Matrix<Data>::operator=(Matrix&& m) noexcept
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
	bool Matrix<Data>::operator==(const Matrix& m) const noexcept
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
	bool Matrix<Data>::operator!=(const Matrix& m) const noexcept
	{
		return !(*this == m);
	}

	/* ************************************************************************ */

	// Specific member functions

	template<typename Data>
	void Matrix<Data>::Resize(const std::size_t newRowSize, const std::size_t newColSize) // Resize the matrix to a given size
	{
		if (newRowSize == 0 || newColSize == 0)
			Clear();
		else
		{
			matrix.Resize(newRowSize);
			rows = newRowSize;
			for (std::size_t i = 0; i < rows; ++i)
				matrix[i].Resize(newColSize);
			cols = newColSize;
		}
	}

	template<typename Data>
	void Matrix<Data>::ResizeRows(const std::size_t newRowSize)
	{
		Resize(newRowSize, cols);
	}

	template<typename Data>
	void Matrix<Data>::ResizeCols(const std::size_t newColSize)
	{
		Resize(rows, newColSize);
	}

	template<typename Data>
	inline std::size_t Matrix<Data>::Rows() const noexcept
	{
		return rows;
	}

	template<typename Data>
	inline std::size_t Matrix<Data>::Columns() const noexcept
	{
		return cols;
	}

	template<typename Data>
	Vector<Data>& Matrix<Data>::MainDiagonal() const
	{
		Vector<Data> v(std::min(rows, cols));
		for (auto i = 0; i < std::min(rows, cols); ++i)
		{
			v[i] = matrix[i][i];
		}
		return v;
	}

	template<typename Data>
	Vector<Data>& Matrix<Data>::AntiDiagonal() const
	{
		Vector<Data> v(std::min(rows, cols));
		for (std::size_t i = 0; i < std::min(rows, cols); ++i)
		{
			v[i] = matrix[i][(cols - 1) - i];
		}
		return v;
	}

	template<typename Data>
	Vector<Data>& Matrix<Data>::Row(const std::size_t rowIndex) const
	{
		if (rowIndex >= rows)
			throw std::out_of_range("Index out of bounds!");

		return matrix[rowIndex];
	}

	template<typename Data>
	Vector<Data>& Matrix<Data>::Col(const std::size_t colIndex) const
	{
		if (colIndex >= cols)
			throw std::out_of_range("Index out of bounds!");

		Vector<Data> v(rows);
		for (std::size_t i = 0; i < rows; ++i)
		{
			v[i] = matrix[i][colIndex];
		}
		return v;
	}

	template<typename Data>
	Matrix<Data>& Matrix<Data>::SubMatrix(const std::size_t endRow, const std::size_t endCol)
	{
		if (endRow > rows || endCol > cols)
			throw std::out_of_range("Index out of bounds!");
		Matrix<Data> m(endRow, endCol);
		for (std::size_t i = 0; i < endRow; ++i)
		{
			for (std::size_t j = 0; j < endCol; ++j)
			{
				m.matrix[i][j] = matrix[i][j];
			}
		}
		return m;
	}


	/* ************************************************************************ */

	// Specific member functions (inherited from Container)

	template<typename Data>
	void Matrix<Data>::Clear() // Override Container member
	{
		size = 0;
		rows = 0;
		cols = 0;
		for (std::size_t i = 0; i < matrix.Size(); ++i)
		{
			matrix[i].Clear();
		}
		matrix.Clear();
	}

	/* ************************************************************************ */

	// Specific member functions (inherited from LinearContainer)

	template<typename Data>
	Vector<Data>& Matrix<Data>::operator[](const std::size_t rowIndex) const // Override LinearContainer member (must throw std::out_of_range when out of range)
	{
		return Row(rowIndex);
	}

	/* ************************************************************************ */

	// Specific member functions (inherited from MappableContainer)

	template<typename Data>
	void Matrix<Data>::Map(MapFunctor f, void *par) // Override MappableContainer member
	{
		MapRowWise(f, par);
	}

	/* ************************************************************************ */

	template<typename Data>
	void Matrix<Data>::MapInOrder(MapFunctor f, void *par)
	{
		MapRowWise(f, par);
	}

	template<typename Data>
	void Matrix<Data>::MapRowWise(MapFunctor f, void *par)
	{
		for (std::size_t i = 0; i < rows; ++i)
		{
			matrix[i].MapPreOrder(f, par);
		}
	}

	template<typename Data>
	void Matrix<Data>::MapPreOrder(MapFunctor f, void *par)
	{
		MapColumnWise(f, par);
	}

	template<typename Data>
	void Matrix<Data>::MapColumnWise(MapFunctor f, void *par)
	{
		for (std::size_t i = 0; i < cols; ++i)
		{
			for (std::size_t j = 0; j < rows; ++j)
			{
				f(matrix[j][i], par);
			}
		}
	}

	template<typename Data>
	void Matrix<Data>::MapBreadth(MapFunctor f, void *par)
	{
		MapSpiral(f, par);
	}

	template<typename Data>
	void Matrix<Data>::MapSpiral(MapFunctor f, void *par)
	{
		for (long i = 0; std::cmp_less(i , rows + cols - 1); ++i)
		{
			if (i % 2 == 0)
			{
				for (long y = 0; std::cmp_less(y , cols); ++y)
				{
					if (std::cmp_greater(cols , i - y) && i - y >= 0)
					{
						f(matrix[i - y][y], par);
					}
				}
			}
			else
			{
				for (long x = 0; std::cmp_less(x ,rows); ++x)
				{
					if (std::cmp_greater(cols , i - x) && i - x >= 0)
					{
						f(matrix[x][i - x], par);
					}
				}
			}
		}
	}

	/* ************************************************************************ */

	// Specific member functions (inherited from FoldableContainer)

	template<typename Data>
	void Matrix<Data>::Fold(FoldFunctor f, const void *par, void *acc) const // Override FoldableContainer member
	{
		FoldRowWise(f, par, acc);
	}

	/* ************************************************************************ */

	// Specific member functions (inherited from PreOrderFoldableContainer)

	template<typename Data>
	void Matrix<Data>::FoldInOrder(FoldFunctor f, const void *par, void *acc) const
	{
		FoldRowWise(f, par, acc);
	}

	template<typename Data>
	void Matrix<Data>::FoldRowWise(FoldFunctor f, const void *par, void *acc) const
	{
		for (std::size_t i = 0; i < rows; ++i)
		{
			matrix[i].FoldPreOrder(f, par, acc);
		}
	}

	template<typename Data>
	void Matrix<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc) const
	{
		FoldColumnWise(f, par, acc);
	}

	template<typename Data>
	void Matrix<Data>::FoldColumnWise(FoldFunctor f, const void *par, void *acc) const
	{
		for (std::size_t i = 0; i < cols; ++i)
		{
			for (std::size_t j = 0; j < rows; ++j)
			{
				f(matrix[j][i], par, acc);
			}
		}
	}

	template<typename Data>
	void Matrix<Data>::FoldBreadth(FoldFunctor f, const void *par, void *acc) const
	{
		FoldSpiral(f, par, acc);
	}

	template<typename Data>
	void Matrix<Data>::FoldSpiral(FoldFunctor f, const void *par, void *acc) const
	{
		for (long i = 0; std::cmp_less(i , rows + cols - 1); ++i)
		{
			if (i % 2 == 0)
			{
				for (long y = 0; std::cmp_less(y , cols); ++y)
				{
					if (std::cmp_greater(cols , i - y) && i - y >= 0)
					{
						f(matrix[i - y][y], par, acc);
					}
				}
			}
			else
			{
				for (long x = 0; std::cmp_less(x , rows); ++x)
				{
					if (std::cmp_greater(cols , i - x) && i - x >= 0)
					{
						f(matrix[x][i - x], par, acc);
					}
				}
			}
		}
	}


}
