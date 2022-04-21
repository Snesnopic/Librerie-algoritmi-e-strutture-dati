namespace lasd
{

/* ************************************************************************** */

// ...
template <typename Data>
StackLst::StackLst(const LinearContainer<Data> &lc)
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
    }
    size = lc.Size();
}
// Copy constructor
template <typename Data>
StackLst::StackLst(const StackLst &sl)
{
    size = sl.size;
    if(sl.head != nullptr)
    {
        head = new Node(sl.head->dato);
        Node *tmp1 = head;
        Node *tmp2 = sl.head->next;
        while(tmp2 != nullptr)
        {
            tmp1->next = new Node(tmp2->dato);
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        tmp1->next = nullptr;
    }
}

// Move constructor
template <typename Data>
StackLst::StackLst(StackLst &&sl) noexcept
{
    if(sl.head != nullptr)
    {
        std::swap(head,sl.head);
        std::swap(size,sl.size);
    }
}

/* ************************************************************************ */

// Destructor
template <typename Data>
StackLst::~StackLst()
{
    if(head != nullptr)
        delete head;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
StackLst& StackLst::operator=(const StackLst &sl)
{
    if(this != &sl)
    {
        if(sl.head != nullptr)
        {
            Clear();
            head = new Node(sl.head->dato);
            Node *tmp1 = head;
            Node *tmp2 = sl.head->next;
            while(tmp2 != nullptr)
            {
                tmp1->next = new Node(tmp2->dato);
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }
            tmp1->next = nullptr;
        }
        size = sl.size;
    }
    return *this;
}

// Move assignment
template <typename Data>
StackLst& StackLst::operator=(StackLst &&sl) noexcept
{
    if(this != &sl)
    {
        std::swap(size,sl.size);
        std::swap(head,sl.head);
    }
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool StackLst::operator==(const StackLst &sl) const noexcept
{
    if(size != sl.size)
        return false;
    Node *tmp = head;
    Node *tmp2 = sl.head;
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
bool StackLst::operator!=(const StackLst &sl) const noexcept
{
    return !(this == sl);
}

/* ************************************************************************ */

// Specific member functions (inherited from Stack)
template <typename Data>
const StackLst::Data& Top() const // Override Stack member (constant version; must throw std::length_error when empty)
{
    if(size == 0)
        throw std::length_error;
    return head->dato;
}
template <typename Data>
StackLst::Data& Top() // Override Stack member (must throw std::length_error when empty)
{
    if(size == 0)
        throw std::length_error;
    return head->dato;
}
template <typename Data>
void StackLst::Pop() // Override Stack member (must throw std::length_error when empty)
{
    if(size == 0)
        throw std::length_error("Lenght error!");
    Node *tmp = head;
    head = head->next;
    tmp->next = nullptr;
    delete tmp;
    size--;
}
template <typename Data>
Data& StackLst::TopNPop() // Override Stack member (must throw std::length_error when empty)
{
    if(size == 0)
        throw std::length_error("Lenght error!");
    Data &ref = *(new Data(head->dato));
    Pop();
    return ref;
}
template <typename Data>
void StackLst::Push(const Data& d) // Override Stack member (copy of the value)
{
    Node *n = new Node(d);
    n->next = head;
    head = n;
    size++;
}
template <typename Data>
void StackLst::Push(Data &&d) noexcept// Override Stack member (move of the value)
{
    Node* n = new Node(std::move(d));
    n->next = head;
    head = n;
    size++;
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void StackLst::Clear() // Override Container member
{
    if(head != nullptr)
        delete head;
    head = nullptr;
    size = 0;
}

/* ************************************************************************** */

}
