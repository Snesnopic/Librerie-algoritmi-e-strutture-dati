#ifndef LIST_CPP
#define LIST_CPP

#include "list.hpp"
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
    return (dato == n.dato && next == n.next);
}
//Not equal comparison
template <typename Data>
bool List<Data>::Node::operator!=(const Node& n) const noexcept
{
    return !(*this == n);
}
//List functions
//LinearContainer constructor
template <typename Data>
List<Data>::List(const LinearContainer& lc)
{
    size = lc.size;
    for(unsigned long i = 0;i<size;i++)
    {

    }
}
//Copy constructor
template <typename Data>
List<Data>::List(const List &l)
{
    size = l.size;

}
//Clear
template <typename Data>
void List<Data>::Clear()
{
    size = 0;
    delete head->next;
    head = nullptr;
}
//Front
template <typename Data>
Data& List<Data>::Front() const
{
    return head->next->dato;
}
//Back
template <typename Data>
Data& List<Data>::Back() const
{
    struct Node* tmp = head->next;
    while(tmp->next != nullptr)
    {
        tmp = tmp->next;
    }
    return tmp->dato;
}
//Random operator
template <typename Data>
Data& List<Data>::operator[](const unsigned long index) const
{
    if(size == 0)
        throw std::out_of_range("Index out of bounds!");
    Node* tmp = head->next;
    for(unsigned long i = 0; i<index; i++)
    {
        tmp = tmp->next;
    }
    return tmp->dato;
}
template <typename Data>
void List<Data>::InsertAtFront(const Data &d) noexcept
{
    struct Node* n = new Node(d);
    n->next = head;
    head = n;
}
template <typename Data>
void List<Data>::InsertAtFront(Data &d) noexcept
{
    struct Node* n = new Node(std::move(d));
    n->next = head;
    head = n;
}
template <typename Data>
void List<Data>::RemoveFromFront()
{
    Node *tmp = head->next;
    head->next = tmp->next;
    delete tmp;
}
template <typename Data>
Data& List<Data>::FrontNRemove()
{
    Node *tmp = head->next;
    head->next = tmp->next;
    Data tmp2 = tmp->dato;
    delete tmp;
    return tmp2;
}
template <typename Data>
void List<Data>::InsertAtBack(const Data &d) noexcept
{
    struct Node* n = new Node(d);
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
void List<Data>::MapPostOrder(MapFunctor f,void *par,Node *n)
{
    MapPostOrder(f,par,n->next);
    while(n != nullptr)
    {
        f(n->dato,par);
        n = n->next;
    }
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
    FoldPostOrder(f,par,acc,head);
}
//FoldPostOrder ricorsiva
template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor f,const void *par,void *acc,Node *n) const
{
    FoldPostOrder(f,par,acc,n->next);
    while(n != nullptr)
    {
        f(n->dato,par,acc);
        n = n->next;
    }
}
/* ************************************************************************** */

}
#endif // LIST_CPP
