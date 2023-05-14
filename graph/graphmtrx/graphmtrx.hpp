#ifndef GRAPHMTRX_HPP
#define GRAPHMTRX_HPP

#include "../graph.hpp"
#include "../../matrix/matrix.hpp"

namespace lasd
{

/* ************************************************************************** */

	template<typename Data>
	class GraphMtrx : virtual public Graph<Data>
	{
	protected:
		Matrix<Data> adjMatr;
		using Graph<Data>::size;
	public:
		GraphMtrx() = default;

		GraphMtrx(Vector<Data> vertices, std::size_t expectedSize);

		GraphMtrx(Vector<Data> vertices);

		GraphMtrx(std::size_t expectedSize);

		GraphMtrx(const GraphMtrx<Data>& gm);

		GraphMtrx(GraphMtrx<Data>&& gm) noexcept;


	public:
		[[nodiscard]] std::size_t Vertices() const noexcept override;

		[[nodiscard]] std::size_t Edges() const noexcept override;

		void RemoveVertex(Data& v1) override;

		std::size_t DegreeOf(const Data& v1) const override;

		void RemoveEdge(Data& v1, Data& v2) override;

		void AddVertex(Data& v1) override;

		void AddVertex(Data&& v1) noexcept override;

		void AddEdge(const Data& v1, const Data& v2) override;

		void AddEdge(const Data& v1, const Data& v2, double weight) override;

		void AddEdge(const Data& v1, const Data& v2, double weight, bool isDirected) override;

		void AddEdge(const Data& v1, const Data& v2, bool isDirected) override;

		bool AreLinked(const Data& v1, const Data& v2) const override;

		bool AreDirectlyLinked(const Data& v1, const Data& v2) const override;

		double WalkWeight(const Data& v1, const Data& v2) const override;

		[[nodiscard]] bool IsAcyclic() const override;

		[[nodiscard]] bool IsConnected() const override;

		[[nodiscard]] bool IsRegular() const override;

		bool IsIsomorphism(Graph<Data>& g) const override;

		GraphMtrx<Data> Transpose() const override;

		GraphMtrx<Data> Converse() const override;

		GraphMtrx<Data> Reverse() const override;

		Vector<Data> LinksOf(Data& v1) const override;

		// Specific member functions (inherited from MappableContainer)

		using typename MappableContainer<Data>::MapFunctor;

		void Map(MapFunctor f, void *par) override; // Override MappableContainer member
		void MapBreadth(MapFunctor f, void *par) override;

		void MapDepth(MapFunctor f, void *par) override;

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		using typename FoldableContainer<Data>::FoldFunctor;

		void Fold(FoldFunctor f, const void *par, void *acc) const override; // Override FoldableContainer member
		void FoldBreadth(FoldFunctor f, const void *par, void *acc) const override;

		void FoldDepth(FoldFunctor f, const void *par, void *acc) const override;

	};
}

#include "graphmtrx.cpp"

#endif
