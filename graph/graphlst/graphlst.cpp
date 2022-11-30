#include "graphlst.hpp"

namespace lasd
{
	template<typename Data>
	GraphLst<Data>::GraphLst(const Vector<Data>& vertices, unsigned long expectedSize)
	{
		graph.Resize(std::max(expectedSize,vertices.Size()));
		for(unsigned long i = 0; i < vertices.Size() ; ++i)
		{
			AddVertex(vertices[i]);
		}
	}

	template<typename Data>
	GraphLst<Data>::GraphLst(const Vector<Data>& vertices):GraphLst(vertices, vertices.Size()) {};

	template<typename Data>
	GraphLst<Data>::GraphLst(const GraphLst<Data>& gm) : nameMap(gm.nameMap), graph(gm.graph)
	{
		size = gm.size;
	}

	template<typename Data>
	GraphLst<Data>::GraphLst(GraphLst<Data>&& gm) noexcept : nameMap(std::move(gm.nameMap)), graph(std::move(gm.graph))
	{
		size = std::move(gm.size);
	}

	template<typename Data>
	[[nodiscard]] unsigned long GraphLst<Data>::Vertices() const noexcept
	{
		return graph.Size();
	}

	template<typename Data>
	[[nodiscard]] unsigned long GraphLst<Data>::Edges() const noexcept
	{
		unsigned long sum = 0;
		for(unsigned long i = 0; i < graph.Size(); ++i)
		{
			sum += graph[i].Size();
		}
		return sum/2;
	}

	template<typename Data>
	void GraphLst<Data>::RemoveVertex(Data& v1)
	{

	}

	template<typename Data>
	unsigned long GraphLst<Data>::DegreeOf(const Data& v1) const
	{
		return 0;
	}

	template<typename Data>
	void GraphLst<Data>::RemoveEdge(Data& v1, Data& v2)
	{

	}

	template<typename Data>
	void GraphLst<Data>::AddVertex(const Data& v1)
	{
		if(!nameMap.HasKey(v1))
		{
			nameMap.Set(v1,kg());
			if(graph.Size() < kg.key)
				graph.Resize(kg.key);
		}
	}

	template<typename Data>
	void GraphLst<Data>::AddVertex(Data&& v1) noexcept
	{
		if(!nameMap.HasKey(v1))
		{
			nameMap.Set(std::move(v1),kg());
			if(graph.Size() < kg.key)
				graph.Resize(kg.key);
		}
	}

	template<typename Data>
	void GraphLst<Data>::AddEdge(const Data& v1, const Data& v2)
	{
		AddEdge(v1,v2,0,false);
	}

	template<typename Data>
	void GraphLst<Data>::AddEdge(const Data& v1, const Data& v2, double weight)
	{
		AddEdge(v1,v2,weight,false);
	}

	template<typename Data>
	void GraphLst<Data>::AddEdge(const Data& v1, const Data& v2, double weight, bool isDirected)
	{
		AddVertex(v1);
		AddVertex(v2);
		auto&& v = graph[nameMap.ValueOfKey(v1)];
		bool exists = false;
		for(unsigned long i = 0; i < v.Size() && !exists; ++i)
		{
			if(v[i].destination == nameMap.ValueOfKey(v2))
			{
				exists = true;
				v[i].weight = weight;
			}
		}
		if(!exists)
		{
			v.Insert({nameMap.ValueOfKey(v2),weight});
		}
		if(!isDirected)
			AddEdge(v2,v1,weight,true);
	}

	template<typename Data>
	void GraphLst<Data>::AddEdge(const Data& v1, const Data& v2, bool isDirected)
	{
		AddEdge(v1,v2,0,isDirected);
	}
/*
	template<typename Data>
	bool GraphLst<Data>::AreLinked(const Data& v1, const Data& v2) const
	{

	}*/

	template<typename Data>
	bool GraphLst<Data>::AreDirectlyLinked(const Data& v1, const Data& v2) const
	{
		if(nameMap.HasKey(v1) && nameMap.HasKey(v2))
		{
			auto&& v = graph[nameMap.ValueOfKey(v1)];
			bool exists = false;
			for(unsigned long i = 0; i < v.Size() && !exists; ++i)
			{
				if(v[i].destination == nameMap.ValueOfKey(v2))
				{
					exists = true;
				}
			}
			return exists;
		}
		return false;
	}
/*
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
*/
	template<typename Data>
	bool GraphLst<Data>::operator==(const GraphLst<Data>& g) const
	{
		return true;
	}
	template<typename Data>
	bool GraphLst<Data>::operator!=(const GraphLst<Data>& g) const
	{
		return false;
	}

	template<typename Data>
	void GraphLst<Data>::Clear()
	{

	}

	template<typename Data>
	Vector<Data> GraphLst<Data>::LinksOf(Data& v1) const
	{
		Vector<Data> links;
		if(nameMap.HasKey(v1))
		{

			auto&& v = graph[nameMap.ValueOfKey(v1)];
			for(unsigned long i = 0; i < v.Size(); ++i)
			{

			}
		}
		return links;
	}

	// Specific member functions (inherited from MappableContainer)
/*
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
*/
	/* ************************************************************************ */

	// Specific member functions (inherited from FoldableContainer)
/*
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
*/

}