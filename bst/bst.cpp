#include "bst.hpp"

namespace lasd {

/* ************************************************************************** */

    // Specific constructors
    template<typename Data>
    BST<Data>::BST(const LinearContainer<Data> &lc) // A bst obtained from a LinearContainer
    {
        for (unsigned long i = 0; i < lc.Size(); i++) {
            Insert(lc[i]);
        }
    }

    // Copy assignment
    template<typename Data>
    BST<Data> &BST<Data>::operator=(const BST &bst) {
        BinaryTreeLnk<Data>::operator=(bst);
        return *this;
    }

    // Move assignment
    template<typename Data>
    BST<Data> &BST<Data>::operator=(BST &&bst) noexcept {
        BinaryTreeLnk<Data>::operator=(std::move(bst));
        return *this;
    }

    // Comparison operators
    template<typename Data>
    bool BST<Data>::operator==(const BST &bst) const noexcept {
        if (size == bst.size) {
            BTInOrderIterator<Data> i(*this);
            BTInOrderIterator<Data> j(bst);
            while (!i.Terminated()) {
                if (*i != *j)
                    return false;
                ++i;
                ++j;
            }
            return true;
        } else
            return false;
    }

    template<typename Data>
    bool BST<Data>::operator!=(const BST &bst) const noexcept {
        return !(*this == bst);
    }
/* ************************************************************************** */

}
