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
void Container::Clear()
{
    this->size = 0;
}
//LinearContainer functions

bool LinearContainer<Data>::operator==(const Vector &v)
{
    if(this.size != v.Size())
        return false;
    for(int i=0 ; i<this.size; i++)
    {
        if(operator[](i) != v[i])
            return false;
    }
    return true;
}
template<typename Data>
Data LinearContainer<Data>::Front() const
{
    if(this.size == 0)
        throw std::out_of_range("Index out of bounds!");
    return this[0];
}
template<typename Data>
Data LinearContainer<Data>::Back() const
{
    if(this.size == 0)
        throw std::out_of_range("Index out of bounds!");
    return this[size-1];
}
template <typename Data>
bool TestableContainer<Data>::Exists(Data &d)
{

}
bool FoldableContainer<Data>::Exists(const Data d)
{
    //chiamata a FoldableContainer::Fold()
    return true;
}




/* ************************************************************************** */

}
#endif
