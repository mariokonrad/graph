#ifndef __GRAPH__ADJ_MATRIX__HPP__
#define __GRAPH__ADJ_MATRIX__HPP__

#include <vector>
#include <algorithm>

namespace graph
{

/// This class represents a graph, implemented as adjacency matrix
/// and provides simple accessors to the graph.
/// It is possible to add unidirectional edges, but they get treated
/// idividually.
/// Properties for vertices and/or edges are not possible.
class adj_matrix
{
public:
	using size_type = size_t;

	/// Type of the vertex to identify it within the graph.
	using vertex_t = size_type;

	/// Type for the edge, connection two vertices.
	using edge_t = std::pair<vertex_t, vertex_t>;

	/// Container type for a list of vertices.
	using vertex_list = std::vector<vertex_t>;

	/// Container type for a list of edges.
	using edge_list = std::vector<edge_t>;

	/// Internally used to keep track of visited vertices.
	using visited_list = std::vector<bool>;

private:
	/// Type for the matrix itself.
	using Matrix = std::vector<int>;

private:
	Matrix m; // adjacency matrix
	size_type n; // number of vertices

private:
	/// Returns the index of the edge within the list.
	inline size_type edge_index(vertex_t from, vertex_t to) const { return from + to * n; }

public:
	/// Constructor to set the size of the matrix and initialize it
	/// with no edges.
	///
	/// \param[in] n Size of the matrix.
	adj_matrix(size_type n)
		: m(n * n, 0)
		, n(n)
	{
	}

	/// Copy constructor. The entire matrix is copied.
	adj_matrix(const adj_matrix &) = default;

	adj_matrix(adj_matrix &&) = default;

	adj_matrix & operator=(const adj_matrix &) = default;

	adj_matrix & operator=(adj_matrix &&) = default;

	/// Returns the size of the matrix (number of vertices).
	inline size_type size(void) const { return n; }

	/// Adds an edge to the matrix.
	///
	/// Complexity: O(1)
	///
	/// \param[in] from  Starting vertex of the edge.
	/// \param[in] to    Ending vertex of the edge.
	/// \return true on success, false otherwise
	inline bool add(vertex_t from, vertex_t to)
	{
		if ((from >= n) || (to >= n))
			return false;
		edge(from, to) = 1;
		return true;
	}

	/// Removes an edge from the matrix.
	///
	/// Complexity: O(1)
	///
	/// \param[in] from  Starting vertex of the edge.
	/// \param[in] to    Ending vertex of the edge.
	inline bool remove(vertex_t from, vertex_t to)
	{
		if ((from >= n) || (to >= n))
			return false;
		edge(from, to) = 0;
		return true;
	}

	/// Accessor for edges. This method provides writing access to
	/// the matrix and is not boundary checked.
	///
	/// \note The call 'edge(a,b)=1' is the same as 'add(a,b)'.
	///
	/// Complexity: O(1)
	inline int & edge(vertex_t from, vertex_t to) { return m[edge_index(from, to)]; }

	/// Accessor for edges. This method provides read only access
	/// to the matrix and is not boundary checked.
	///
	/// Complexity: O(1)
	inline int edge(vertex_t from, vertex_t to) const { return m[edge_index(from, to)]; }

	/// Returns a list of edges defined by the matrix.
	///
	/// Complexity: O(n^2)
	edge_list edges() const
	{
		edge_list vec;
		for (vertex_t from = 0; from < n; ++from)
			for (vertex_t to = 0; to < n; ++to)
				if (edge(from, to))
					vec.push_back(edge_t(from, to));
		return vec;
	}

	/// Returns the number of incoming edges for the specified
	/// vertex. If a non-existant vertex ist specified the result
	/// is always 0.
	///
	/// Complexity: O(n)
	size_type num_incoming(vertex_t to) const
	{
		if (to >= n)
			return 0;
		size_type cnt = 0;
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
	size_type num_outgoing(vertex_t from) const
	{
		if (from >= n)
			return 0;
		size_type cnt = 0;
		for (vertex_t i = 0; i < n; ++i)
			if (edge(from, i))
				++cnt;
		return cnt;
	}

	/// Returns the total number of edges within the matrix.
	///
	/// Complexity: O(n^2)
	inline size_type num_edges(void) const { return std::count(m.begin(), m.end(), 1); }
};
}

#endif
