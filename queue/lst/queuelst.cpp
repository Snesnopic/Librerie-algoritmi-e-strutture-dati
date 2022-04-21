namespace lasd
{

/* ************************************************************************** */

// Specific constructor
template <typename Data>
QueueLst::QueueLst(const LinearContainer<Data> &lc) // A queue obtained from a LinearContainer
{
    if(!lc.Empty())
    {
        head = new Node(lc[0]);
        Node *tmp = head;
        for(unsigned long i = 1; i<lc.Size(); i++)
        {
            tmp->next = new Node(lc[i]);
            tmp = tmp->next;
        }
        tail = tmp;
    }
    size = lc.Size();
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
QueueLst::QueueLst(const QueueLst &ql)
{
    size = ql.size;
    if(ql.head != nullptr)
    {
        head = new Node(ql.head->dato);
        Node *tmp1 = head;
        Node *tmp2 = ql.head->next;
        while(tmp2 != nullptr)
        {
            tmp1->next = new Node(tmp2->dato);
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        tmp1->next = nullptr;
        tail = tmp1;
    }
}

// Move constructor
template <typename Data>
QueueLst::QueueLst(QueueLst &&ql) noexcept
{
    if(ql.head != nullptr)
    {
        std::swap(head,ql.head);
        std::swap(size,ql.size);
    }
    Node *tmp = head;
    while(tmp->next != nullptr)
    {
        tmp = tmp->next;
    }
    tail = tmp;
}

/* ************************************************************************ */

// Destructor
template <typename Data>
QueueLst::~QueueLst()
{
    if(head != nullptr)
        delete head;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
QueueLst& QueueLst::operator=(const QueueLst& ql)
{
    size = ql.size;
    if(ql.head != nullptr)
    {
        head = new Node(ql.head->dato);
        Node *tmp1 = head;
        Node *tmp2 = ql.head->next;
        while(tmp2 != nullptr)
        {
            tmp1->next = new Node(tmp2->dato);
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        tmp1->next = nullptr;
        tail = tmp1;
    }
    return *this;
}

// Move assignment
template <typename Data>
QueueLst& QueueLst::operator=(QueueLst&& ql) noexcept
{
    if(ql.head != nullptr)
    {
        std::swap(head,ql.head);
        std::swap(size,ql.size);
    }
    Node *tmp = head;
    while(tmp->next != nullptr)
    {
        tmp = tmp->next;
    }
    tail = tmp;
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool QueueLst::operator==(const QueueLst& ql) const noexcept
{
    if(size != ql.size)
        return false;
    Node *tmp = head;
    Node *tmp2 = l.head;
    while(tmp != nullptr)
    {
        if(tmp->dato != tmp2->dato)
            return false;
        tmp = tmp->next;
        tmp2 = tmp2->next;
    }
    return true;
}
template <typename Data>
bool QueueLst::operator!=(const QueueLst& ql) const noexcept
{
    return !(this == ql);
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)
template <typename Data>
const Data& QueueLst::Head() const // Override Queue member (constant version; must throw std::length_error when empty)
{
    if(head == nullptr)
        throw std::length_error("Length error!");
    return tail->dato;
}
template <typename Data>
Data& QueueLst::Head() // Override Queue member (must throw std::length_error when empty)
{
    if(head == nullptr)
        throw std::length_error("Length error!");
    return tail->dato;
}
template <typename Data>
void QueueLst::Dequeue() // Override Queue member (must throw std::length_error when empty)
{
    if(head == nullptr)
        throw std::length_error("Length error!");
    Node *tmp = head;
    head = head->next;
    if(head == nullptr)
        tail = nullptr;
    delete tmp;
    size--;
}
template <typename Data>
Data& QueueLst::HeadNDequeue() // Override Queue member (must throw std::length_error when empty)
{
    if(head == nullptr)
    {
        throw std::length_error("Length error!");
    }
    Data &ref = *(new Data(Head()));
    Dequeue();
    return ref;
}
template <typename Data>
void QueueLst::Enqueue(const Data& d) noexcept // Override Queue member (copy of the value)
{
    Node *n = new Node(d);
    if(tail == nullptr)
        head = tail = n;
    else
    {
        tail->next = n;
        tail = n;
    }
    size++;
}
template <typename Data>
void QueueLst::Enqueue(Data &&d) noexcept // Override Queue member (move of the value)
{
    Node *n = new Node(std::move(d));
    if(tail == nullptr)
        head = tail = n;
    else
    {
        tail->next = n;
        tail = n;
    }
    size++;
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void QueueLst::Clear() // Override Container member
{
    if(head != nullptr)
        delete head;
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/* ************************************************************************** */

}
