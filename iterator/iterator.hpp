#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */


namespace lasd
{

/* ************************************************************************** */

	template<typename Data>
	class Iterator
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~Iterator() = default;

		/* ************************************************************************ */

		// Copy assignment
		Iterator& operator=(const Iterator&) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		Iterator& operator=(Iterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		bool operator==(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
		bool operator!=(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		virtual Data& operator*() const = 0; // (concrete function must throw std::out_of_range when terminated)

		[[nodiscard]] virtual bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)

	};

/* ************************************************************************** */

	template<typename Data>
	class ForwardIterator : virtual public Iterator<Data>
	{ // Must extend Iterator

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		~ForwardIterator() override = default;

		/* ************************************************************************ */

		// Copy assignment
		ForwardIterator& operator=(const ForwardIterator&) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		ForwardIterator& operator=(ForwardIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		bool operator==(const ForwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
		bool operator!=(const ForwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		virtual ForwardIterator& operator++() = 0; // (concrete function must throw std::out_of_range when terminated)

	};

/* ************************************************************************** */

	template<typename Data>
	class BackwardIterator : virtual public Iterator<Data>
	{ // Must extend Iterator

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		~BackwardIterator() override = default;

		/* ************************************************************************ */

		// Copy assignment
		BackwardIterator& operator=(const BackwardIterator&) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		BackwardIterator& operator=(BackwardIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		bool operator==(const BackwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
		bool operator!=(const BackwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		virtual BackwardIterator& operator--() = 0; // (concrete function must throw std::out_of_range when terminated)

	};

/* ************************************************************************** */

	template<typename Data>
	class BidirectionalIterator : virtual public ForwardIterator<Data>, virtual public BackwardIterator<Data>
	{ // Must extend ForwardIterator and BackwardIterator

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		~BidirectionalIterator() override = default;

		/* ************************************************************************ */

		// Copy assignment
		BidirectionalIterator& operator=(const BidirectionalIterator&) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		BidirectionalIterator& operator=(BidirectionalIterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		bool operator==(const BidirectionalIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
		bool operator!=(const BidirectionalIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		[[nodiscard]] bool Terminated() const noexcept override
		{
			return ForwardTerminated() || BackwardTerminated();
		} // Override Iterator member

		[[nodiscard]] virtual bool ForwardTerminated() const noexcept = 0; // (concrete function should not throw exceptions)

		[[nodiscard]] virtual bool BackwardTerminated() const noexcept = 0; // (concrete function should not throw exceptions)

	};

/* ************************************************************************** */

	template<typename Data>
	class ResettableIterator : virtual public Iterator<Data>
	{ // Must extend Iterator<Data>

	private:

	protected:

	public:

		// Destructor
		~ResettableIterator() override = default;

		/* ************************************************************************ */

		// Copy assignment
		ResettableIterator& operator=(const ResettableIterator& ri) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		ResettableIterator& operator=(ResettableIterator&& ri) noexcept = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		bool operator==(const ResettableIterator& ri) const noexcept = delete; // Comparison of abstract types might not be possible.
		bool operator!=(const ResettableIterator& ri) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		virtual void Reset() noexcept = 0; // (concrete function should not throw exceptions)

	};

/* ************************************************************************** */

}

#endif
