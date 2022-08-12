#include "graphmtrx.hpp"

namespace lasd
{
	template<typename Data>
	GraphMtrx<Data>::GraphMtrx(const Vector<Data>& vertices, unsigned long expectedSize)
	{
		indices = vertices;
		size = std::max(expectedSize, indices.Size());
	}

	template<typename Data>
	GraphMtrx<Data>::GraphMtrx(const Vector<Data>& vertices):GraphMtrx(vertices, vertices.Size()) {};

	template<typename Data>
	GraphMtrx<Data>::GraphMtrx(unsigned long expectedSize): GraphMtrx(indices, expectedSize) {};

	template<typename Data>
	GraphMtrx<Data>::GraphMtrx(const GraphMtrx<Data>& gm)
	{
		indices = gm.indices;
		adjList = gm.adjList;
		size = gm.size;
	}

	template<typename Data>
	GraphMtrx<Data>::GraphMtrx(GraphMtrx<Data>&& gm) noexcept
	{
		indices = std::move(gm.indices);
		adjList = std::move(gm.adjList);
		size = std::move(gm.size);
	}

	template<typename Data>
	[[nodiscard]] unsigned long GraphMtrx<Data>::Vertices() const noexcept
	{

	}

	template<typename Data>
	[[nodiscard]] unsigned long GraphMtrx<Data>::Edges() const noexcept
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::RemoveVertex(Data& v1)
	{

	}

	template<typename Data>
	unsigned long GraphMtrx<Data>::DegreeOf(const Data& v1) const
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::RemoveEdge(Data& v1, Data& v2)
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::AddVertex(Data& v1)
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::AddVertex(Data&& v1) noexcept
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::AddEdge(const Data& v1, const Data& v2)
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::AddEdge(const Data& v1, const Data& v2, double weight)
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::AddEdge(const Data& v1, const Data& v2, double weight, bool isDirected)
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::AddEdge(const Data& v1, const Data& v2, bool isDirected)
	{

	}

	template<typename Data>
	bool GraphMtrx<Data>::AreLinked(const Data& v1, const Data& v2) const
	{

	}

	template<typename Data>
	bool GraphMtrx<Data>::AreDirectlyLinked(const Data& v1, const Data& v2) const
	{

	}

	template<typename Data>
	double GraphMtrx<Data>::WalkWeight(const Data& v1, const Data& v2) const
	{

	}

	template<typename Data>
	[[nodiscard]] bool GraphMtrx<Data>::IsAcyclic() const
	{

	}

	template<typename Data>
	[[nodiscard]] bool GraphMtrx<Data>::IsConnected() const
	{

	}

	template<typename Data>
	[[nodiscard]] bool GraphMtrx<Data>::IsRegular() const
	{

	}

	template<typename Data>
	bool GraphMtrx<Data>::IsIsomorphism(Graph<Data>& g) const
	{

	}

	template<typename Data>
	GraphMtrx<Data> GraphMtrx<Data>::Transpose() const
	{

	}

	template<typename Data>
	GraphMtrx<Data> GraphMtrx<Data>::Converse() const
	{

	}

	template<typename Data>
	GraphMtrx<Data> GraphMtrx<Data>::Reverse() const
	{

	}

	template<typename Data>
	Vector<Data> GraphMtrx<Data>::LinksOf(Data& v1) const
	{

	}

	// Specific member functions (inherited from MappableContainer)

	template<typename Data>
	void GraphMtrx<Data>::Map(MapFunctor f, void *par) // Override MappableContainer member
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::MapBreadth(MapFunctor f, void *par)
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::MapDepth(MapFunctor f, void *par)
	{

	}

	/* ************************************************************************ */

	// Specific member functions (inherited from FoldableContainer)

	template<typename Data>
	void GraphMtrx<Data>::Fold(FoldFunctor f, const void *par, void *acc) const // Override FoldableContainer member
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::FoldBreadth(FoldFunctor f, const void *par, void *acc) const
	{

	}

	template<typename Data>
	void GraphMtrx<Data>::FoldDepth(FoldFunctor f, const void *par, void *acc) const
	{

	}


}