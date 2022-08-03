#ifndef GRAPHMTRX_HPP
#define GRAPHMTRX_HPP

#include "../graph.hpp"
#include "../../matrix/matrix.hpp"

namespace lasd
{

/* ************************************************************************** */

    template<typename Data>
    class GraphMtrx : virtual public Graph<Data>{
    protected:
        Matrix<Data> adjMatr;
        using Graph<Data>::size;
    public:
        GraphMtrx() = default;

    };
    }
#include "graphmtrx.cpp"
#endif
