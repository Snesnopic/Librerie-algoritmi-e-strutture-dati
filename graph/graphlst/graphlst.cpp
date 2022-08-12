#include "graphlst.hpp"

namespace lasd
{
	template<typename Data>
	GraphLst<Data>::GraphLst(const Vector<Data>& vertices, unsigned long expectedSize)
	{
		indices = vertices;
		size = std::max(expectedSize, indices.Size());
	}

	template<typename Data>
	GraphLst<Data>::GraphLst(const Vector<Data>& vertices):GraphLst(vertices, vertices.Size()) {};

	template<typename Data>
	GraphLst<Data>::GraphLst(unsigned long expectedSize): GraphLst(indices, expectedSize) {};

	template<typename Data>
	GraphLst<Data>::GraphLst(const GraphLst<Data>& gm)
	{
		indices = gm.indices;
		adjList = gm.adjList;
		size = gm.size;
	}

	template<typename Data>
	GraphLst<Data>::GraphLst(GraphLst<Data>&& gm) noexcept
	{
		indices = std::move(gm.indices);
		adjList = std::move(gm.adjList);
		size = std::move(gm.size);
	}

	template<typename Data>
	[[nodiscard]] unsigned long GraphLst<Data>::Vertices() const noexcept
	{
		return indices.Size();
	}

	template<typename Data>
	[[nodiscard]] unsigned long GraphLst<Data>::Edges() const noexcept
	{

	}

	template<typename Data>
	void GraphLst<Data>::RemoveVertex(Data& v1)
	{
		size--;
		adjList.Remove(indices.GetIndexOf(v1));
		for (auto i = 0; i < adjList.Size(); ++i)
		{
			for (auto j = 0; j < adjList[i].Size(); ++j)
			{
				if (adjList[i][j] == v1)
					adjList[i].Remove(j);
			}
		}
	}

	template<typename Data>
	unsigned long GraphLst<Data>::DegreeOf(const Data& v1) const
	{

	}

	template<typename Data>
	void GraphLst<Data>::RemoveEdge(Data& v1, Data& v2)
	{

	}

	template<typename Data>
	void GraphLst<Data>::AddVertex(Data& v1)
	{

	}

	template<typename Data>
	void GraphLst<Data>::AddVertex(Data&& v1) noexcept
	{

	}

	template<typename Data>
	void GraphLst<Data>::AddEdge(const Data& v1, const Data& v2)
	{

	}

	template<typename Data>
	void GraphLst<Data>::AddEdge(const Data& v1, const Data& v2, double weight)
	{

	}

	template<typename Data>
	void GraphLst<Data>::AddEdge(const Data& v1, const Data& v2, double weight, bool isDirected)
	{

	}

	template<typename Data>
	void GraphLst<Data>::AddEdge(const Data& v1, const Data& v2, bool isDirected)
	{

	}

	template<typename Data>
	bool GraphLst<Data>::AreLinked(const Data& v1, const Data& v2) const
	{

	}

	template<typename Data>
	bool GraphLst<Data>::AreDirectlyLinked(const Data& v1, const Data& v2) const
	{

	}

	template<typename Data>
	double GraphLst<Data>::WalkWeight(const Data& v1, const Data& v2) const
	{

	}

	template<typename Data>
	[[nodiscard]] bool GraphLst<Data>::IsAcyclic() const
	{

	}

	template<typename Data>
	[[nodiscard]] bool GraphLst<Data>::IsConnected() const
	{

	}

	template<typename Data>
	[[nodiscard]] bool GraphLst<Data>::IsRegular() const
	{

	}

	template<typename Data>
	bool GraphLst<Data>::IsIsomorphism(Graph<Data>& g) const
	{

	}

	template<typename Data>
	GraphLst<Data> GraphLst<Data>::Transpose() const
	{

	}

	template<typename Data>
	GraphLst<Data> GraphLst<Data>::Converse() const
	{

	}

	template<typename Data>
	GraphLst<Data> GraphLst<Data>::Reverse() const
	{

	}

	template<typename Data>
	Vector<Data> GraphLst<Data>::LinksOf(Data& v1) const
	{

	}

	// Specific member functions (inherited from MappableContainer)

	template<typename Data>
	void GraphLst<Data>::Map(MapFunctor f, void *par) // Override MappableContainer member
	{

	}

	template<typename Data>
	void GraphLst<Data>::MapBreadth(MapFunctor f, void *par)
	{

	}

	template<typename Data>
	void GraphLst<Data>::MapDepth(MapFunctor f, void *par)
	{

	}

	/* ************************************************************************ */

	// Specific member functions (inherited from FoldableContainer)

	template<typename Data>
	void GraphLst<Data>::Fold(FoldFunctor f, const void *par, void *acc) const // Override FoldableContainer member
	{

	}

	template<typename Data>
	void GraphLst<Data>::FoldBreadth(FoldFunctor f, const void *par, void *acc) const
	{

	}

	template<typename Data>
	void GraphLst<Data>::FoldDepth(FoldFunctor f, const void *par, void *acc) const
	{

	}


}