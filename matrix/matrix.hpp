#ifndef MATRIX_HPP
#define MATRIX_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    class Matrix
            : virtual public PreOrderMappableContainer<Data>,
              virtual public InOrderMappableContainer<Data>,
              virtual public PreOrderFoldableContainer<Data>,
              virtual public InOrderFoldableContainer<Data>,
              virtual public BreadthMappableContainer<Data>,
              virtual public BreadthFoldableContainer<Data> {
    protected:
        unsigned long rows = 0;
        unsigned long cols = 0;
        using PreOrderFoldableContainer<Data>::size;
        Vector<Vector<Data>> matrix;
    public:
        // Default constructor
        Matrix() = default;
        /* ************************************************************************ */
        // Specific constructors
        Matrix(unsigned long rowSize, unsigned long colSize);

        Matrix(unsigned long rowSize, unsigned long colSize, Data defaultValue);


        /* ************************************************************************ */

        // Copy constructor
        Matrix(const Matrix &m);

        // Move constructor
        Matrix(Matrix &&m) noexcept;

        /* ************************************************************************ */

        // Destructor
        ~Matrix() override;

        /* ************************************************************************ */

        // Copy assignment
        Matrix &operator=(const Matrix &m);

        // Move assignment
        Matrix &operator=(Matrix &&m) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const Matrix &m) const noexcept;

        bool operator!=(const Matrix &m) const noexcept;

        /* ************************************************************************ */

        // Specific member functions

        void Resize(unsigned long newRowSize, unsigned long newColSize); // Resize the matrix to a given size

        void ResizeRows(unsigned long newRowSize);

        void ResizeCols(unsigned long newColSize);

        [[nodiscard]] unsigned long Rows() const noexcept;

        [[nodiscard]] unsigned long Columns() const noexcept;

        Vector<Data> &MainDiagonal() const;

        Vector<Data> &AntiDiagonal() const;

        Vector<Data> &Row(unsigned long rowIndex) const;

        Vector<Data> &Col(unsigned long colIndex) const;

        Matrix &SubMatrix(unsigned long endRow, unsigned long endCol);


        /* ************************************************************************ */

        // Specific member functions (inherited from Container)

        void Clear() override; // Override Container member

        /* ************************************************************************ */

        // Specific member functions (inherited from LinearContainer)

        Vector<Data> &operator[](unsigned long rowIndex) const; // Override LinearContainer member (must throw std::out_of_range when out of range)


        /* ************************************************************************ */

        // Specific member functions (inherited from MappableContainer)

        using typename MappableContainer<Data>::MapFunctor;

        void Map(MapFunctor f, void *par) override; // Override MappableContainer member

        /* ************************************************************************ */

        void MapInOrder(MapFunctor f, void *par) override;

        void MapRowWise(MapFunctor f, void *par);

        void MapPreOrder(MapFunctor f, void *par) override;

        void MapColumnWise(MapFunctor f, void *par);

        void MapBreadth(MapFunctor f, void *par) override;

        void MapSpiral(MapFunctor f, void *par);

        /* ************************************************************************ */

        // Specific member functions (inherited from FoldableContainer)

        using typename FoldableContainer<Data>::FoldFunctor;

        void Fold(FoldFunctor f, const void *par, void *acc) const override; // Override FoldableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from PreOrderFoldableContainer)

        void FoldInOrder(FoldFunctor f, const void *par, void *acc) const override;

        void FoldRowWise(FoldFunctor f, const void *par, void *acc) const;

        void FoldPreOrder(FoldFunctor f, const void *par, void *acc) const override;

        void FoldColumnWise(FoldFunctor f, const void *par, void *acc) const;

        void FoldBreadth(FoldFunctor f, const void *par, void *acc) const override;

        void FoldSpiral(FoldFunctor f, const void *par, void *acc) const;

    };

/* ************************************************************************** */

}

#include "matrix.cpp"

#endif
