#ifndef CONTAINER_CPP
#define CONTAINER_CPP
#include "container.hpp"
namespace lasd
{

/* ************************************************************************** */
//Container functions
bool Container::Empty()const noexcept
{
    return (size == 0);
}
unsigned long Container::Size()const noexcept
{
    return size;
}

//LinearContainer functions
bool LinearContainer<Data>::operator==(const LinearContainer<Data> &lc) const noexcept
{
    if(this.size != v.Size())
        return false;
    for(unsigned long i=0 ; i<this.size; i++)
    {
        if(operator[](i) != v[i])
            return false;
    }
    return true;
}
bool LinearContainer<Data>::operator!=(const LinearContainer<Data> &lc) const noexcept
{
    return !(*this == lc);
}
template<typename Data>
Data& LinearContainer<Data>::Front() const
{
    if(this.size == 0)
        throw std::out_of_range("Index out of bounds!");
    return operator[](0);
}
template<typename Data>
Data& LinearContainer<Data>::Back() const
{
    if(this.size == 0)
        throw std::out_of_range("Index out of bounds!");
    return operator[](size-1);
}
template <typename Data>

//FoldableContainer functions
template <typename Data>
void AuxFoldExists(const Data& dat,const void* val,void* exists) noexcept
{
    if(dat == *((Data*) val))
    {
        *((bool*) exists) = true;
    }
}
template <typename Data>
bool FoldableContainer<Data>::Exists(const Data& d) const noexcept
{
    bool esiste;
    Fold(&AuxFoldExists<Data>,&d,&esiste);
    return esiste;
}
//PreOrderMappableContainer functions
template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFunctor fun, void* par)
{
    MapPreOrder(fun,par);
}

//PreOrderFoldableContainer functions
template <typename Data>
void PreOrderFoldableContainer<Data>::Fold(FoldFunctor fun,const void* par,void* acc) const
{
    FoldPreOrder(fun,par,acc);
}
//PostOrderMappableContainer functions
template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFunctor fun,void* par)
{
    MapPostOrder(fun,par);
}
//PostOrderFoldableContainer functions
template <typename Data>
void PostOrderFoldableContainer<Data>::Fold(FoldFunctor fun,const void* par,void* acc) const
{
    FoldInOrder(fun,par,acc);
}
//InOrderMappableContainer functions
template <typename Data>
void InOrderMappableContainer<Data>::Map(MapFunctor fun,void* par)
{
    MapInOrder(fun,par);
}
//InOrderFoldableContainer functions
template <typename Data>
void InOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const
{
    FoldInOrder(fun,par,acc);
}
//BreadthMappableContainer functions
template <typename Data>
void BreadthMappableContainer<Data>::Map(MapFunctor fun,void* par)
{
    MapBreadth(fun,par);
}
//BreadthFoldableContainer functions
template <typename Data>
void BreadthFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const
{
    FoldBreadth(fun,par,acc);
}
/* ************************************************************************** */

}
#endif
