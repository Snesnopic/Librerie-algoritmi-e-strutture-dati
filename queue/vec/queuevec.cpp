namespace lasd
{

/* ************************************************************************** */

// Specific constructor
template <typename Data>
QueueVec::QueueVec(const LinearContainer<Data> &lc) // A queue obtained from a LinearContainer
{

}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
QueueVec::QueueVec(const QueueVec &qv)
{

}

// Move constructor
template <typename Data>
QueueVec::QueueVec(QueueVec &&qv) noexcept
{

}

/* ************************************************************************ */

// Destructor
template <typename Data>
QueueVec::~QueueVec();

/* ************************************************************************ */

// Copy assignment
template <typename Data>
QueueVec& QueueVec::operator=(const QueueVec &qv)
{

}

// Move assignment
template <typename Data>
QueueVec& QueueVec::operator=(QueueVec &&qv) noexcept
{

}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool QueueVec::operator==(const QueueVec &qv) const noexcept
{

}
template <typename Data>
bool QueueVec::operator!=(const QueueVec &qv) const noexcept
{

}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)
template <typename Data>
const Data& QueueVec::Head() const // Override Queue member (constant version; must throw std::length_error when empty)
{

}
template <typename Data>
Data& QueueVec::Head() // Override Queue member (must throw std::length_error when empty)
{

}
template <typename Data>
void QueueVec::Dequeue() // Override Queue member (must throw std::length_error when empty)
{

}
template <typename Data>
Data& QueueVec::HeadNDequeue() // Override Queue member (must throw std::length_error when empty)
{

}
template <typename Data>
void QueueVec::Enqueue(const Data& d) noexcept // Override Queue member (copy of the value)
{

}
template <typename Data>
void QueueVec::Enqueue(Data &&d) noexcept // Override Queue member (move of the value)
{

}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
bool QueueVec::Empty() const noexcept // Override Container member
{

}
template <typename Data>
unsigned int QueueVec::Size() const noexcept // Override Container member
{

}
template <typename Data>
void QueueVec::Clear() noexcept // Override Container member
{

}


// Auxiliary member functions
template <typename Data>
void QueueVec::Expand() noexcept
{

}
template <typename Data>
void QueueVec::Reduce() noexcept
{

}
template <typename Data>
void QueueVec::SwapVectors(QueueVec &qv) noexcept
{

}

/* ************************************************************************** */

}
