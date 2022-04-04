namespace lasd
{

/* ************************************************************************** */
//Node methods
//Node copy constructor
template <typename Data>
List<Data>::Node::Node(const Data& d)
{
    dato = d;
}
//Node Data move constructor
template <typename Data>
List<Data>::Node::Node(Data&& d) noexcept
{
    std::swap(dato,d);
}
//Node Node copy constructor
template <typename Data>
List<Data>::Node::Node(const Node& n)
{
    dato = n.dato;
    next = n.next;
}
//Node Node move constructor
template <typename Data>
List<Data>::Node::Node(Node&& n) noexcept
{
    std::swap(dato,n.dato);
    std::swap(next,n.next);
}
//Node destructor
template <typename Data>
List<Data>::Node::~Node()
{
    delete next;
}
//Node operators
//Equal comparison
template <typename Data>
bool List<Data>::Node::operator==(const Node& n) const noexcept
{
    if(dato == n.dato)                              //se i dati sono uguali...
    {
        if(next == nullptr && n.next == nullptr)    //e entrambi non hanno un prossimo...
        {
            return true;
        }
        if(next != nullptr && n.next != nullptr)    //o hanno un prossimo...
        {
            if(*next == *n.next)                    //ed è lo stesso...
                return true;
        }
    }
    return false;
}
//Not equal comparison
template <typename Data>
bool List<Data>::Node::operator!=(const Node& n) const noexcept
{
    return !(*this == n);
}
//List functions
//Destructor
template <typename Data>
List<Data>::~List()
{
    delete head;
}
//LinearContainer constructor
template <typename Data>
List<Data>::List(const LinearContainer<Data>& lc)
{
    size = lc.Size();
    Node *tmp = head;
    for(unsigned long i = 0;i<size;i++)
    {
        tmp->dato = lc[i];
        tmp = tmp->next;
    }
}
//Copy constructor
template <typename Data>
List<Data>::List(const List &l)
{
    size = l.size;
    head = l.head;
}
//Move constructor
template <typename Data>
List<Data>::List(List &&l) noexcept
{
    std::swap(size,l.size);
    std::swap(head,l.head);
}
//Clear
template <typename Data>
void List<Data>::Clear()
{
    size = 0;
    delete head;
    head = nullptr;
}
//Front
template <typename Data>
Data& List<Data>::Front() const
{
    if(size == 0)
        throw std::length_error("Index out of bounds!");
    return head->dato;
}
//Back
template <typename Data>
Data& List<Data>::Back() const
{
    if(size == 0)
        throw std::length_error("Index out of bounds!");
    Node* tmp = head;
    while(tmp->next != nullptr)
    {
        tmp = tmp->next;
    }
    return tmp->dato;
}
//Copy assignment
template <typename Data>
List<Data>& List<Data>::operator=(const List &l)
{
    if (l.head == nullptr)
    {
        Clear();
        size = l.size;
        return *this;
    }
    else
    {
        Clear();
        Node* tmp = l.head;
        head = new Node;
        head->dato = tmp->dato;
        head->next = nullptr;
        Node* current = head;
        tmp = tmp->next;
        while (tmp != nullptr)
        {
            current->next = new Node;
            current = current->next;
            current->dato = tmp->dato;
            current->next = nullptr;
            tmp = tmp->next;
        }
        size = l.size;
        return *this;
    }

}

//Move assignment
template <typename Data>
List<Data>& List<Data>::operator=(List &&l) noexcept
{
    if(this != &l)
    {
        std::swap(size,l.size);
        std::swap(head,l.head);
    }
    return *this;
}
//Random operator
template <typename Data>
Data& List<Data>::operator[](const unsigned long index) const
{
    if(size == 0)
        throw std::out_of_range("Index out of bounds!");
    Node* tmp = head;
    for(unsigned long i = 0; i<index; i++)
    {
        tmp = tmp->next;
    }
    return tmp->dato;
}
//Equal comparison operator
template <typename Data>
bool List<Data>::operator==(const List &l) const noexcept
{
    if(size != l.size)
        return false;
    Node *tmp = head;
    Node *tmp2 = l.head;
    while(tmp != nullptr)
    {
        if(tmp != tmp2)
            return false;
        tmp = tmp->next;
        tmp2 = tmp2->next;
    }
    return true;
}
//Not equal comparison operator
template <typename Data>
bool List<Data>::operator!=(const List &l) const noexcept
{
    return !(*this == l);
}
template <typename Data>
void List<Data>::InsertAtFront(const Data &d) noexcept
{
    Node* n = new Node(d);
    n->next = head;
    head = n;
    size++;
}
template <typename Data>
void List<Data>::InsertAtFront(Data &d) noexcept
{
    struct Node* n = new Node(d);
    n->next = head;
    head = n;
    size++;
}
template <typename Data>
void List<Data>::RemoveFromFront()
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
Data& List<Data>::FrontNRemove()
{
    if(size == 0)
        throw std::length_error("Lenght error!");
    Node *tmp = head;
    Data &tmp2 = Front();
    head = head ->next;
    delete tmp;
    return tmp2;
    size--;
}
template <typename Data>
void List<Data>::InsertAtBack(const Data &d) noexcept
{
    Node* n = new Node(d);
    n->next = nullptr;
    if(head == nullptr)
        head = n;
    else
    {
        Node *tmp = head;
        while(tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = n;
    }
    size++;
}
template <typename Data>
void List<Data>::InsertAtBack(Data &&d) noexcept
{
    struct Node* n = new Node(std::move(d));
    n->next = nullptr;
    if(head == nullptr)
        head = n;
    else
    {
        struct Node *tmp = head;
        while(tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = n;
    }
    size++;
}
//Map functions
//Map
template <typename Data>
void List<Data>::Map(MapFunctor f,void *par)
{
    MapPreOrder(f,par,head);
}
//MapPreOrder
template <typename Data>
void List<Data>::MapPreOrder(MapFunctor f,void *par)
{
    if(head != nullptr)
        MapPreOrder(f,par,head);
}
//MapPreOrder ricorsiva
template <typename Data>
void List<Data>::MapPreOrder(MapFunctor f,void *par,Node *n)
{
    while(n != nullptr)
    {
        f(n->dato,par);
        n = n->next;
    }
}
//MapPostOrder
template <typename Data>
void List<Data>::MapPostOrder(MapFunctor f,void *par)
{
    if(head != nullptr)
        MapPostOrder(f,par,head);
}
//MapPostOrder ricorsiva
template <typename Data>
void List<Data>::MapPostOrder(MapFunctor f,void *par,Node *n)
{
    if(n->next != nullptr)
        MapPostOrder(f,par,n->next);
    f(n->dato,par);
    n = n->next;
}
//Fold functions
//Fold
template <typename Data>
void List<Data>::Fold(FoldFunctor f,const void* par,void *acc) const
{
    FoldPreOrder(f,par,acc,head);
}
//FoldPreOrder
template <typename Data>
void List<Data>::FoldPreOrder(FoldFunctor f, const void *par,void *acc) const
{
    if(head != nullptr)
        FoldPreOrder(f,par,acc,head);
}
//FoldPreOrder ricorsiva
template <typename Data>
void List<Data>::FoldPreOrder(FoldFunctor f, const void *par,void *acc,Node *n) const
{
    while(n != nullptr)
    {
        f(n->dato,par,acc);
        n = n->next;
    }
}
//FoldPostOrder
template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor f,const void *par,void *acc) const
{
    if(head != nullptr)
        FoldPostOrder(f,par,acc,head);
}
//FoldPostOrder ricorsiva
template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor f,const void *par,void *acc,Node *n) const
{
    if(n->next != nullptr)
        FoldPostOrder(f,par,acc,n->next);
    f(n->dato,par,acc);
}
/* ************************************************************************** */

}
