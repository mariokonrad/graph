#ifndef __GRAPH__ADJ_MATRIX__HPP__
#define __GRAPH__ADJ_MATRIX__HPP__

#include <vector>
#include <algorithm>
#include <cassert>

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
class adj_matrix
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

		explicit edge_t(vertex_t from, vertex_t to) noexcept : from(from), to(to) {}

		edge_t(const std::initializer_list<vertex_t> v)
			: from(*v.begin())
			, to(*(v.begin() + 1))
		{
			assert(v.size() == 2);
		}

		edge_t(const edge_t &) noexcept = default;
		edge_t(edge_t &&) noexcept = default;

		edge_t & operator=(const edge_t &) = default;
		edge_t & operator=(edge_t &&) noexcept = default;

		friend bool operator<(const edge_t & a, const edge_t & b)
		{
			if (a.from < b.from)
				return true;
			if (a.from == b.from)
				return (a.to < b.to);
			return false;
		}
	};

	/// Container type for a list of vertices.
	using vertex_list = std::vector<vertex_t>;

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
	/// Returns the index of the edge within the list.
	vertex_t edge_index(vertex_t from, vertex_t to) const { return from + to * n; }

public:
	/// Constructor to set the size of the matrix and initialize it
	/// with no edges.
	///
	/// \param[in] n Size of the matrix.
	adj_matrix(vertex_t n)
		: m(n * n, 0)
		, n(n)
	{
		assert(n > 0);
	}

	adj_matrix(vertex_t n, std::initializer_list<edge_t> edges)
		: adj_matrix(n)
	{
		assert(n > 0);
		for (auto const & e : edges)
			add(e.from, e.to);
	}

	/// Copy constructor. The entire matrix is copied.
	adj_matrix(const adj_matrix &) = default;

	adj_matrix(adj_matrix &&) = default;

	adj_matrix & operator=(const adj_matrix &) = default;

	adj_matrix & operator=(adj_matrix &&) = default;

	/// Returns the size of the matrix (number of vertices).
	vertex_t size() const { return n; }

	/// Adds an edge to the matrix.
	///
	/// Complexity: O(1)
	///
	/// \param[in] from Starting vertex of the edge.
	/// \param[in] to Ending vertex of the edge.
	/// \param[in] bidirectional Flag to add bidirectional edge
	/// \param[in] value Value for the specified edge
	/// \return true on success, false otherwise
	///
	/// \note This function performs boundary check.
	bool add(vertex_t from, vertex_t to, bool bidirectional = false, vertex_value_t value = 1)
	{
		if ((from >= n) || (to >= n))
			return false;
		edge(from, to) = value;
		if (bidirectional)
			edge(to, from) = value;
		return true;
	}

	/// Removes an edge from the matrix.
	///
	/// Complexity: O(1)
	///
	/// \param[in] from Starting vertex of the edge.
	/// \param[in] bidirectional Flag to remove bidirectional edge
	/// \param[in] to Ending vertex of the edge.
	/// \return true on success, false otherwise
	///
	/// \note This function performs boundary check.
	bool remove(vertex_t from, vertex_t to, bool bidirectional = false)
	{
		if ((from >= n) || (to >= n))
			return false;
		edge(from, to) = 0;
		if (bidirectional)
			edge(to, from) = 0;
		return true;
	}

	/// Accessor for edges. This method provides writing access to
	/// the matrix and is not boundary checked.
	///
	/// \note The call 'edge(a,b)=1' is the same as 'add(a,b)'.
	///
	/// Complexity: O(1)
	vertex_value_t & edge(vertex_t from, vertex_t to) { return m[edge_index(from, to)]; }

	/// Accessor for edges. This method provides read only access
	/// to the matrix and is not boundary checked.
	///
	/// Complexity: O(1)
	vertex_value_t edge(vertex_t from, vertex_t to) const { return m[edge_index(from, to)]; }

	/// Returns a list of edges defined by the matrix.
	///
	/// Complexity: O(n^2)
	edge_list edges() const
	{
		edge_list vec;
		for (vertex_t from = 0; from < n; ++from)
			for (vertex_t to = 0; to < n; ++to)
				if (edge(from, to))
					vec.emplace_back(from, to);
		return vec;
	}

	/// Returns the number of incoming edges for the specified
	/// vertex. If a non-existant vertex ist specified the result
	/// is always 0.
	///
	/// Complexity: O(n)
	vertex_t num_incoming(vertex_t to) const
	{
		if (to >= n)
			return 0;
		vertex_t cnt = 0;
		for (vertex_t i = 0; i < n; ++i)
			if (edge(i, to))
				++cnt;
		return cnt;
	}

	/// Returns the number of outgoing edges for the specified
	/// vertex. If a non-existant vertex ist specified the result
	/// is always 0.
	///
	/// Complexity: O(n)
	vertex_t num_outgoing(vertex_t from) const
	{
		if (from >= n)
			return 0;
		vertex_t cnt = 0;
		for (vertex_t i = 0; i < n; ++i)
			if (edge(from, i))
				++cnt;
		return cnt;
	}

	/// Returns the total number of edges within the matrix.
	///
	/// Complexity: O(n^2)
	vertex_t num_edges() const { return std::count(m.begin(), m.end(), 1); }
};
}

#endif
