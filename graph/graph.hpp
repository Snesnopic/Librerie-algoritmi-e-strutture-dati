#ifndef GRAPH_HPP
#define GRAPH_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../iterator/iterator.hpp"
#include "vector.hpp"

/* ************************************************************************** */

namespace lasd {
    template<typename Data>
    class Graph :
            virtual public DepthMappableContainer<Data>,
            virtual public DepthFoldableContainer<Data>,
            virtual public BreadthMappableContainer<Data>,
            virtual public BreadthFoldableContainer<Data> {
    protected:
        using BreadthMappableContainer<Data>::size;
    public:
        void AddVertex(Data &v1) = 0;

        void AddVertex(Data &&v1) noexcept = 0;

        void AddEdge(Data &v1, Data &v2) = 0;

        void AddEdge(Data &v1, Data &v2, double weight) = 0;

        void AddEdge(Data &v1, Data &v2, double weight, bool isDirected) = 0;

        void AddEdge(Data &v1, Data &v2, bool isDirected) = 0;

        bool AreLinked(Data &v1, Data &v2) const = 0;

        double WalkWeight(Data &v1, Data &v2) const = 0;

        [[nodiscard]] bool IsAcyclic() const = 0;

        [[nodiscard]] bool IsConnected() const = 0;

        [[nodiscard]] bool IsRegular() const = 0;

        bool IsIsomorphism(Graph<Data> g) const = 0;

        Graph<Data> Transpose() const = 0;
        Graph<Data> Converse() const = 0;
        Graph<Data> Reverse() const = 0;

        Vector<Data> LinksOf(Data &v1) const = 0;

        // Specific member functions (inherited from MappableContainer)

        using typename MappableContainer<Data>::MapFunctor;

        void Map(MapFunctor f, void *par) override; // Override MappableContainer member
        void MapBreadth(MapFunctor f, void *par) override;
        void MapDepth(MapFunctor f, void *par) override;

        /* ************************************************************************ */

        // Specific member functions (inherited from FoldableContainer)

        using typename FoldableContainer<Data>::FoldFunctor;

        void Fold(FoldFunctor f, const void *par, void *acc) const override; // Override FoldableContainer member
        void FoldBreadth(FoldFunctor f, const void *par, void *acc) const override;
        void FoldDepth(FoldFunctor f, const void *par, void *acc) const override;

    };

    template<typename Data>
    class GDepthIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {
    private:

        // ...

    protected:
/*
        struct BinaryTree<Data>::Node *curr = nullptr;
        QueueLst<struct BinaryTree<Data>::Node *> que{};
        const BinaryTree<Data> *treePtr = nullptr;*/
    public:

        // Specific constructors
        explicit GDepthIterator(const Graph<Data> &bt); // An iterator over a given binary tree


        /* ************************************************************************ */

        // Copy constructor
        GDepthIterator(const GDepthIterator &bi);

        // Move constructor
        GDepthIterator(GDepthIterator &&bi) noexcept;

        /* ************************************************************************ */

        // Destructor
        ~GDepthIterator() override;

        /* ************************************************************************ */

        // Copy assignment
        GDepthIterator &operator=(const GDepthIterator &bi);

        // Move assignment
        GDepthIterator &operator=(GDepthIterator &&bi) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const GDepthIterator &bi) const noexcept;

        bool operator!=(const GDepthIterator &bi) const noexcept;

        /* ************************************************************************ */

        // Specific member functions (inherited from Iterator)

        Data &operator*() const override; // (throw std::out_of_range when terminated)

        [[nodiscard]] bool Terminated() const noexcept override; // (should not throw exceptions)

        /* ************************************************************************ */

        // Specific member functions (inherited from ForwardIterator)

        GDepthIterator &operator++() override; // (throw std::out_of_range when terminated)


        /* ************************************************************************ */

        // Specific member functions (inherited from ResettableIterator)

        void Reset() noexcept override; // (should not throw exceptions)
    };

    template<typename Data>
    class GBreadthIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {
    private:

        // ...

    protected:
        /*
        struct BinaryTree<Data>::Node *curr = nullptr;
        QueueLst<struct BinaryTree<Data>::Node *> que{};
        const BinaryTree<Data> *treePtr = nullptr;*/
    public:

        // Specific constructors
        explicit GBreadthIterator(const Graph<Data> &bt); // An iterator over a given binary tree


        /* ************************************************************************ */

        // Copy constructor
        GBreadthIterator(const GBreadthIterator &bi);

        // Move constructor
        GBreadthIterator(GBreadthIterator &&bi) noexcept;

        /* ************************************************************************ */

        // Destructor
        ~GBreadthIterator() override;

        /* ************************************************************************ */

        // Copy assignment
        GBreadthIterator &operator=(const GBreadthIterator &bi);

        // Move assignment
        GBreadthIterator &operator=(GBreadthIterator &&bi) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const GBreadthIterator &bi) const noexcept;

        bool operator!=(const GBreadthIterator &bi) const noexcept;

        /* ************************************************************************ */

        // Specific member functions (inherited from Iterator)

        Data &operator*() const override; // (throw std::out_of_range when terminated)

        [[nodiscard]] bool Terminated() const noexcept override; // (should not throw exceptions)

        /* ************************************************************************ */

        // Specific member functions (inherited from ForwardIterator)

        GBreadthIterator &operator++() override; // (throw std::out_of_range when terminated)


        /* ************************************************************************ */

        // Specific member functions (inherited from ResettableIterator)

        void Reset() noexcept override; // (should not throw exceptions)
    };
}

#include "graph.cpp"

#endif

