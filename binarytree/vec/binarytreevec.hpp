#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

	template<typename Data>
	class BinaryTreeVec : virtual public BinaryTree<Data>
	{
		// Must extend BinaryTree<Data>

	private:

		// ...

	protected:

		using BinaryTree<Data>::size;

		// ...

		struct NodeVec : virtual public BinaryTree<Data>::Node  // Must extend Node
		{

		private:

			// ...

		protected:

			// ...

		public:
			using BinaryTree<Data>::Node::dato;
			unsigned long index{};
			Vector<NodeVec *> *arrayRef = nullptr;

			NodeVec() = default;

			NodeVec(Vector<NodeVec *> *arr, unsigned long i, const Data& d) : index(i), arrayRef(arr)
			{
				dato = d;
			}

			NodeVec(Vector<NodeVec *> *arr, unsigned long i, Data&& d) : index(i), arrayRef(arr)
			{
				dato = std::move(d);
			}

			[[nodiscard]] bool HasLeftChild() const noexcept override // (concrete function should not throw exceptions)
			{
				return arrayRef->Size() > (2 * index) + 1;
			}

			[[nodiscard]] bool HasRightChild() const noexcept override // (concrete function should not throw exceptions)
			{

				return arrayRef->Size() > (2 * index) + 2;
			}

			NodeVec& LeftChild() const override // (concrete function must throw std::out_of_range when not existent)
			{
				if (!HasLeftChild())
					throw std::out_of_range("Out of range!");
				return *(arrayRef->operator[]((2 * index) + 1));
			}

			NodeVec& RightChild() const override // (concrete function must throw std::out_of_range when not existent)
			{
				if (!HasRightChild())
					throw std::out_of_range("Out of range!");
				return *(arrayRef->operator[]((2 * index) + 2));
			}
		};

		Vector<NodeVec *> array{};
	public:

		// Default constructor
		BinaryTreeVec() = default;

		/* ************************************************************************ */

		// Specific constructors
		explicit BinaryTreeVec(const LinearContainer<Data>& lc); // A binary tree obtained from a LinearContainer

		/* ************************************************************************ */

		// Copy constructor
		BinaryTreeVec(const BinaryTreeVec& btv);

		// Move constructor
		BinaryTreeVec(BinaryTreeVec&& btv) noexcept;

		/* ************************************************************************ */

		// Destructor
		virtual ~BinaryTreeVec();

		/* ************************************************************************ */

		// Copy assignment
		BinaryTreeVec& operator=(const BinaryTreeVec& btv);

		// Move assignment
		BinaryTreeVec& operator=(BinaryTreeVec&& btv) noexcept;

		/* ************************************************************************ */

		// Specific member functions (inherited from BinaryTree)

		NodeVec& Root() const override // Override BinaryTree member (throw std::length_error when empty)
		{
			if (size == 0)
				throw std::length_error("Length error!");
			return *(array[0]);
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from Container)

		void Clear() override; // Override Container member

		/* ************************************************************************ */

		// Specific member functions (inherited from BreadthMappableContainer)
		using typename MappableContainer<Data>::MapFunctor;

		void MapBreadth(MapFunctor f, void *par) override;// Override BreadthMappableContainer member // Override BreadthMappableContainer member

		/* ************************************************************************ */

		// Specific member functions (inherited from BreadthFoldableContainer)
		using typename FoldableContainer<Data>::FoldFunctor;

		void FoldBreadth(FoldFunctor f, const void *par, void *acc) const override; // Override BreadthFoldableContainer member

	};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
