#ifndef GRAPHLST_HPP
#define GRAPHLST_HPP

#include "../graph.hpp"
#include "../../list/list.hpp"

namespace lasd
{

/* ************************************************************************** */

    template<typename Data>
    class GraphLst : virtual public Graph<Data> {
    };
}
#include "graphlst.cpp"
#endif
