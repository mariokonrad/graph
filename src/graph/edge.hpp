#ifndef __GRAPH__EDGE__HPP__
#define __GRAPH__EDGE__HPP__

#include <vector>
#include <graph/vertex.hpp>

namespace graph
{
/// Type for the edge, connection two vertices.
///
/// Objects of this struct are immutable.
///
/// \note This structure is not what is stored within the adjacency matrix,
///       it is a representation of an edge for easier handling
///       outside the adjacency matrix.
///
/// \note Objects of `edge` do not store any information about their
///       type. An object of this struct represents always an unidirectional
///       edge. The enumeration of types is located within this struct
///       as a logical grouping.
///
struct edge {
	/// Enuemrates all possible types of edges.
	enum class type {
		uni, ///< unidirectional
		bi ///< bidirectional
	};

	const vertex from; ///< Starting vertex of the edge.
	const vertex to; ///< Ending vertex of the edge.

	constexpr edge(vertex from, vertex to) noexcept : from(from), to(to) {}

	edge(const edge &) noexcept = default;
	edge(edge &&) noexcept = default;

	edge & operator=(const edge &) = default;
	edge & operator=(edge &&) noexcept = default;

	constexpr edge reverse() const { return {to, from}; }

	/// Operator less, necessary to use edges in maps.
	///
	/// Precedence: from, to
	///
	/// \todo Implement this function as `constexpr`. Sadly GCC 4.9 does not
	///       support relaxed `constexpr` requirements, even with `-std=c++1y`.
	friend bool operator<(const edge & a, const edge & b)
	{
		if (a.from < b.from)
			return true;
		if (a.from == b.from)
			return a.to < b.to;
		return false;
	}

	/// Comparison operator for equality.
	constexpr friend bool operator==(const edge & a, const edge & b)
	{
		return (&a == &b) || ((a.from == b.from) && (a.to == b.to));
	}

	/// Comparison operator for inequality.
	constexpr friend bool operator!=(const edge & a, const edge & b) { return !(a == b); }
};

/// Container type for a list of edges.
using edge_list = std::vector<edge>;
}

#endif
