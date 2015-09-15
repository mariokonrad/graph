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
	/// Type of the vertex to identify it within the graph.
	using vertex_t = int;

	/// Representation of vertices within the matrix
	using vertex_value_t = int;

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

		friend bool operator<(const edge_t & a, const edge_t & b);
	};

	/// Container type for a list of vertices.
	using vertex_list = std::vector<vertex_t>;

	/// Container type for a list of vertices.
	using vertex_value_list = std::vector<vertex_value_t>;

	/// Container type for a list of edges.
	using edge_list = std::vector<edge_t>;

	/// Internally used to keep track of visited vertices.
	using visited_list = std::vector<bool>;

private:
	/// Type for the matrix itself.
	using Matrix = std::vector<vertex_value_t>;

private:
	Matrix m; // adjacency matrix
	const vertex_t n; // number of vertices

private:
	vertex_t edge_index(vertex_t from, vertex_t to) const noexcept;

public:
	adjmatrix(vertex_t n);
	adjmatrix(vertex_t n, std::initializer_list<edge_t> edges);

	adjmatrix(const adjmatrix &) = default;
	adjmatrix(adjmatrix &&) = default;

	adjmatrix & operator=(const adjmatrix &) = default;
	adjmatrix & operator=(adjmatrix &&) = default;

	vertex_t size() const noexcept;

	bool add(vertex_t from, vertex_t to, bool bidirectional = false, vertex_value_t value = 1);

	bool remove(vertex_t from, vertex_t to, bool bidirectional = false);

	vertex_value_t & edge(vertex_t from, vertex_t to);
	vertex_value_t edge(vertex_t from, vertex_t to) const;

	vertex_list vertices() const;
	vertex_list neighbors_of(vertex_t v) const;

	edge_list edges() const;

	vertex_t num_incoming(vertex_t to) const;
	vertex_t num_outgoing(vertex_t from) const;

	vertex_t num_edges() const noexcept;
};

bool operator<(const adjmatrix::edge_t & a, const adjmatrix::edge_t & b);
}

#endif
