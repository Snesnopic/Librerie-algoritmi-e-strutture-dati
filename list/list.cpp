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
}
//Node Node move constructor
template <typename Data>
List<Data>::Node::Node(Node&& n) noexcept
{
    std::swap(dato,n.dato);;
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
    //
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
void List<Data>::Fold(FoldFunctor f,const void* par,void *acc)
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
        f(n->dato,par);
        n = n->next;
    }
}
//FoldPostOrder
template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor f,const void *par,void *acc) const
{
    FoldPostOrder(f,par,acc,n->next);
}
//FoldPostOrder ricorsiva
template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor f,const void *par,void *acc,Node *n) const
{
    FoldPostOrder(f,par,acc,n->next);
    while(n != nullptr)
    {
        f(n->dato,par);
        n = n->next;
    }
}
/* ************************************************************************** */

}
#endif
