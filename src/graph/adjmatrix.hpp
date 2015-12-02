#ifndef __GRAPH__ADJMATRIX__HPP__
#define __GRAPH__ADJMATRIX__HPP__

#include <vector>

namespace graph
{
/// Vertex identifier. Also used as index within adjacency matrices.
using vertex = int;

/// Container type for a list of vertices.
using vertex_list = std::vector<vertex>;

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

/// This class represents a graph, implemented as adjacency matrix
/// and provides simple accessors to the graph.
/// It is possible to add unidirectional edges, but they get treated
/// idividually.
///
/// Properties for vertices and/or edges are not possible.
///
/// Once constructed, the size is constant. It is not possible to
/// grow or shrink.
///
class adjmatrix
{
public:
	using size_type = int;

	/// Representation of vertices within the matrix
	using value_type = int;

	/// Container type for a list of vertices.
	using value_list = std::vector<value_type>;

	/// Internally used to keep track of visited vertices.
	using visited_list = std::vector<bool>;

	/// Indicates no edge between vertices.
	static constexpr value_type no_value = 0;

	/// Indicates an edge between vertices.
	static constexpr value_type edge_value = 1;

private:
	const size_type n; // number of vertices
	std::vector<value_type> m; // adjacency matrix

	/// Computes the index of the specified edge within the adjacency matrix,
	/// which is implemented as std::vector.
	vertex edge_index(edge e) const noexcept { return e.from + e.to * n; }

public:
	/// \{
	adjmatrix(size_type n);
	adjmatrix(size_type n, std::initializer_list<edge> edges);
	adjmatrix(const adjmatrix &) = default;
	adjmatrix(adjmatrix &&) = default;
	/// \}

	/// \{
	adjmatrix & operator=(const adjmatrix &) = default;
	adjmatrix & operator=(adjmatrix &&) = default;
	/// \}

	/// \{
	bool add(edge e, edge::type type = edge::type::uni, value_type value = edge_value);

	bool add(vertex from, vertex to, edge::type type = edge::type::uni,
		value_type value = edge_value)
	{
		return add({from, to}, type, value);
	}
	/// \}

	/// \{
	bool remove(edge e, edge::type type = edge::type::uni);

	bool remove(vertex from, vertex to, edge::type type = edge::type::uni)
	{
		return remove({from, to}, type);
	}
	/// \}

	/// \{
	value_type & get(edge e);
	value_type get(edge e) const;

	/// Convenience function. See \see get(edge)
	value_type & get(vertex from, vertex to) { return get({from, to}); }

	/// Convenience function. See \see get(edge) const
	value_type get(vertex from, vertex to) const { return get({from, to}); }

	value_type & operator[](edge e);
	value_type operator[](edge e) const;
	/// \}

	/// \{
	size_type size() const noexcept;
	vertex_list vertices() const;
	vertex_list neighbors_of(vertex v) const;
	size_type count_incoming(vertex to) const;
	vertex_list incoming(vertex to) const;
	size_type count_outgoing(vertex to) const;
	vertex_list outgoing(vertex from) const;
	/// \}

	/// \{
	size_type count_edges() const noexcept;
	edge_list edges() const;
	/// \}
};
}

#endif
