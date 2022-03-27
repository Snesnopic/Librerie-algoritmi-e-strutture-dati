#ifndef CONTAINER_CPP
#define CONTAINER_CPP
#include "container.hpp"
namespace lasd
{

/* ************************************************************************** */
//Container functions
bool Container::Empty()const noexcept
{
    if(size == 0)
        return true;
    return false;
}
unsigned long Container::Size()const noexcept
{
    return size;
}

//LinearContainer functions
template<typename Data>
Data LinearContainer<Data>::Front() const
{
    return this[0];
}
template<typename Data>
Data LinearContainer<Data>::Back() const
{
    return this[size-1];
}



/* ************************************************************************** */

}
#endif
