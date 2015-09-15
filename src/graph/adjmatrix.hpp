#ifndef __GRAPH__ADJMATRIX__HPP__
#define __GRAPH__ADJMATRIX__HPP__

#include <vector>

namespace graph
{

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
	/// Vertex identifier.
	using vertex_t = int;

	/// Representation of vertices within the matrix
	using vertex_value_t = int;

	static constexpr vertex_value_t no_value = 0;

	/// Type for the edge, connection two vertices.
	struct edge_t {
		const vertex_t from;
		const vertex_t to;

		explicit edge_t(vertex_t from, vertex_t to) noexcept;

		edge_t(const std::initializer_list<vertex_t> v);

		edge_t(const edge_t &) noexcept = default;
		edge_t(edge_t &&) noexcept = default;

		edge_t & operator=(const edge_t &) = default;
		edge_t & operator=(edge_t &&) noexcept = default;

		edge_t reverse() const;

		bool operator<(const edge_t & other) const;
	};

	/// Container type for a list of vertices.
	using vertex_list_t = std::vector<vertex_t>;

	/// Container type for a list of vertices.
	using vertex_value_list_t = std::vector<vertex_value_t>;

	/// Container type for a list of edges.
	using edge_list_t = std::vector<edge_t>;

	/// Internally used to keep track of visited vertices.
	using visited_list_t = std::vector<bool>;

private:
	const vertex_t n; // number of vertices
	std::vector<vertex_value_t> m; // adjacency matrix

private:
	vertex_t edge_index(edge_t e) const noexcept;

public:
	adjmatrix(vertex_t n);
	adjmatrix(vertex_t n, std::initializer_list<edge_t> edges);

	adjmatrix(const adjmatrix &) = default;
	adjmatrix(adjmatrix &&) = default;

	adjmatrix & operator=(const adjmatrix &) = default;
	adjmatrix & operator=(adjmatrix &&) = default;

	vertex_t size() const noexcept;
	vertex_t count_edges() const noexcept;

	bool add(edge_t e, bool bidirectional = false, vertex_value_t value = 1);
	bool add(vertex_t from, vertex_t to, bool bidirectional = false, vertex_value_t value = 1)
	{
		return add({from, to}, bidirectional, value);
	}

	bool remove(edge_t e, bool bidirectional = false);
	bool remove(vertex_t from, vertex_t to, bool bidirectional = false)
	{
		return remove({from, to}, bidirectional);
	}

	vertex_value_t & edge(edge_t e);
	vertex_value_t edge(edge_t e) const;

	vertex_value_t & edge(vertex_t from, vertex_t to) { return edge({from, to}); }
	vertex_value_t edge(vertex_t from, vertex_t to) const { return edge({from, to}); }

	vertex_value_t & operator[](edge_t e);
	const vertex_value_t & operator[](edge_t e) const;

	vertex_list_t vertices() const;
	edge_list_t edges() const;

	vertex_list_t neighbors_of(vertex_t v) const;
	vertex_list_t incoming(vertex_t to) const;
	vertex_list_t outgoing(vertex_t from) const;
};
}

#endif
