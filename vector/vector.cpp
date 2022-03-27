#ifndef VECTOR_CPP
#define VECTOR_CPP
#include "vector.hpp"
namespace lasd
{

/* ************************************************************************** */

// ...
template <typename Data>
void Vector<Data>::Clear()
{
    this.size = 0;
    delete[] array;
}
template <typename Data>
Vector<Data>::Vector(unsigned long initialSize)
{
    this.array = new Data[initialSize];
}
template <typename Data>
Vector<Data>::~Vector()
{
    delete[] array;
}
template <typename Data>
Data& Vector<Data>::operator[](const unsigned long index)
{
    if(index >= this.size)
        throw std::out_of_range("Index out of bounds!");
    return array[index];
}
template <typename Data>
void Vector<Data>::Resize(const unsigned long newSize)
{

}
template <typename Data>
bool Vector<Data>::operator==(const Vector &v)
{
    if(this.size != v.Size())
        return false;
    for(int i=0 ; i<this.size; i++)
    {
        if(array[i] != v[i])
            return false;
    }
    return true;
}
template <typename Data>
bool Vector<Data>::operator!=(const Vector &v)
{
    return !(this == v);
}
template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data> v)
{
    if(this != &v)
    {
        if(this.size != v.Size())
        {
            delete[] array;
            this.size = v.Size();
            array = new Data[this.size];
        }
        std::copy(v.array,v.array + v.Size(),array);
    }
    return *this;
}
template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data> &&v)
{
    if(this != &v)
    {
        delete[] array;
        array = std::exchange(v.array,nullptr);
        this.size = std::exchange(v.size,nullptr);
    }
    return *this;
}
/* ************************************************************************** */

}
#endif
