#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

	template<typename Data>
	class Stack : virtual public Container
	{
		// Must extend Container

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~Stack() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual Stack& operator=(const Stack& s) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual Stack& operator=(Stack&& s) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const Stack& s) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const Stack& s) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		virtual const Data& Top() const = 0; // (constant version; concrete function must throw std::length_error when empty)
		virtual Data& Top() = 0; // (concrete function must throw std::length_error when empty)
		virtual void Pop() = 0; // (concrete function must throw std::length_error when empty)
		virtual Data& TopNPop() = 0; // (concrete function must throw std::length_error when empty)
		virtual void Push(const Data& d) = 0; // Copy of the value
		virtual void Push(Data&& d) noexcept = 0; // Move of the value

	};

/* ************************************************************************** */

}

#endif
