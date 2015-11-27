#ifndef __GRAPH__ADJMATRIX__HPP__
#define __GRAPH__ADJMATRIX__HPP__

#include <vector>

namespace graph
{
/// Vertex identifier. Also used as index within adjacency matrices.
using vertex = int;

/// Type for the edge, connection two vertices.
struct edge {
	enum class type {
		uni, ///< unidirectional
		bi ///< bidirectional
	};

	const vertex from;
	const vertex to;

	constexpr edge(vertex from, vertex to) noexcept : from(from), to(to) {}

	edge(const std::initializer_list<vertex> v);

	edge(const edge &) noexcept = default;
	edge(edge &&) noexcept = default;

	edge & operator=(const edge &) = default;
	edge & operator=(edge &&) noexcept = default;

	constexpr edge reverse() const { return edge(to, from); }

	bool operator<(const edge & other) const;
};

constexpr bool operator==(const edge & a, const edge & b)
{
	return (&a == &b) || ((a.from == b.from) && (a.to == b.to));
}

constexpr bool operator!=(const edge & a, const edge & b) { return !(a == b); }

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
	using vertex_list = std::vector<vertex>;

	/// Container type for a list of vertices.
	using value_list = std::vector<value_type>;

	/// Container type for a list of edges.
	using edge_list = std::vector<edge>;

	/// Internally used to keep track of visited vertices.
	using visited_list = std::vector<bool>;

	/// Indicates no edge between vertices.
	static constexpr value_type no_value = 0;

	/// Indicates an edge between vertices.
	static constexpr value_type edge_value = 1;

private:
	const size_type n; // number of vertices
	std::vector<value_type> m; // adjacency matrix

	vertex edge_index(edge e) const noexcept;

public:
	adjmatrix(size_type n);
	adjmatrix(size_type n, std::initializer_list<edge> edges);

	adjmatrix(const adjmatrix &) = default;
	adjmatrix(adjmatrix &&) = default;

	adjmatrix & operator=(const adjmatrix &) = default;
	adjmatrix & operator=(adjmatrix &&) = default;

	size_type size() const noexcept;
	size_type count_edges() const noexcept;

	bool add(edge e, edge::type type = edge::type::uni, value_type value = edge_value);
	bool add(vertex from, vertex to, edge::type type = edge::type::uni,
		value_type value = edge_value)
	{
		return add({from, to}, type, value);
	}

	bool remove(edge e, edge::type type = edge::type::uni);
	bool remove(vertex from, vertex to, edge::type type = edge::type::uni)
	{
		return remove({from, to}, type);
	}

	value_type & get(edge e);
	value_type get(edge e) const;

	/// convenience function
	value_type & get(vertex from, vertex to) { return get({from, to}); }

	/// convenience function
	value_type get(vertex from, vertex to) const { return get({from, to}); }

	value_type & operator[](edge e);
	value_type operator[](edge e) const;

	vertex_list vertices() const;
	edge_list edges() const;

	vertex_list neighbors_of(vertex v) const;
	vertex_list incoming(vertex to) const;
	vertex_list outgoing(vertex from) const;
};
}

#endif
