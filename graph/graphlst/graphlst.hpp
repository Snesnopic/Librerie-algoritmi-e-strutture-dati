#ifndef GRAPHLST_HPP
#define GRAPHLST_HPP

#include "../graph.hpp"
#include "../../list/list.hpp"
#include "../../vector/vector.hpp"
#include "../../bimap/bimap.hpp"

namespace lasd
{

/* ************************************************************************** */

	template<typename Data>
	class GraphLst : virtual public Graph<Data>
	{
		private:
		struct KeyGen
		{
			unsigned long key;
			KeyGen() : key(0){};
			unsigned long operator()(unsigned long x = 1)
			{
				return (key += x);
			}

		};
		struct Edge
		{
			long destination{};
			double weight{};
			bool operator==(const Edge& it) const{
				return (true);
			}

			bool operator!=(const Edge& it) const{
				return !(*this == it);
			}
		};
	protected:
		KeyGen kg;
		friend class Bimap<Data,long>;
		Bimap<Data,long> nameMap;
		Vector<Vector<Edge>> graph;
		using Graph<Data>::size;
	public:
		GraphLst() = default;

		GraphLst(const Vector<Data>& vertices, unsigned long expectedSize);

		explicit GraphLst(const Vector<Data>& vertices);

		GraphLst(const GraphLst<Data>& gm);

		GraphLst(GraphLst<Data>&& gm) noexcept;

		[[nodiscard]] unsigned long Vertices() const noexcept override;

		[[nodiscard]] unsigned long Edges() const noexcept override;

		void RemoveVertex(Data& v1) override;

		unsigned long DegreeOf(const Data& v1) const override;

		void RemoveEdge(Data& v1, Data& v2) override;

		void AddVertex(const Data& v1) override;

		void AddVertex(Data&& v1) noexcept override;

		void AddEdge(const Data& v1, const Data& v2) override;

		void AddEdge(const Data& v1, const Data& v2, double weight) override;

		void AddEdge(const Data& v1, const Data& v2, double weight, bool isDirected) override;

		void AddEdge(const Data& v1, const Data& v2, bool isDirected) override;

		//bool AreLinked(const Data& v1, const Data& v2) const override;

		bool AreDirectlyLinked(const Data& v1, const Data& v2) const override;
		/*
		double WalkWeight(const Data& v1, const Data& v2) const override;

		[[nodiscard]] bool IsAcyclic() const override;

		[[nodiscard]] bool IsConnected() const override;

		[[nodiscard]] bool IsRegular() const override;

		bool IsIsomorphism(Graph<Data>& g) const override;

		GraphLst<Data> Transpose() const override;

		GraphLst<Data> Converse() const override;

		GraphLst<Data> Reverse() const override;

*/		bool operator==(const GraphLst<Data>& g) const;
		bool operator!=(const GraphLst<Data>& g) const;

		void Clear() override;
		Vector<Data> LinksOf(Data& v1) const override;

		// Specific member functions (inherited from MappableContainer)
/*/
		using typename MappableContainer<Data>::MapFunctor;

		void Map(MapFunctor f, void *par) override; // Override MappableContainer member
		void MapBreadth(MapFunctor f, void *par) override;

		void MapDepth(MapFunctor f, void *par) override;
*/
		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)
/*/
		using typename FoldableContainer<Data>::FoldFunctor;

		void Fold(FoldFunctor f, const void *par, void *acc) const override; // Override FoldableContainer member
		void FoldBreadth(FoldFunctor f, const void *par, void *acc) const override;

		void FoldDepth(FoldFunctor f, const void *par, void *acc) const override;
*/
	};
}

#include "graphlst.cpp"

#endif