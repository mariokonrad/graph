#include "adjmatrix.hpp"
#include <algorithm>
#include <cassert>

namespace graph
{

bool operator<(const adjmatrix::edge_t & a, const adjmatrix::edge_t & b)
{
	if (a.from < b.from)
		return true;
	if (a.from == b.from)
		return (a.to < b.to);
	return false;
}

adjmatrix::edge_t::edge_t(vertex_t from, vertex_t to) noexcept : from(from), to(to) {}

adjmatrix::edge_t::edge_t(const std::initializer_list<vertex_t> v)
	: from(*v.begin())
	, to(*(v.begin() + 1))
{
	assert(v.size() == 2);
}

adjmatrix::vertex_t adjmatrix::edge_index(vertex_t from, vertex_t to) const noexcept
{
	return from + to * n;
}

/// Constructor to set the size of the matrix and initialize it
/// with no edges.
///
/// \param[in] n Size of the matrix.
adjmatrix::adjmatrix(vertex_t n)
	: m(n * n, 0)
	, n(n)
{
	assert(n > 0);
}

adjmatrix::adjmatrix(vertex_t n, std::initializer_list<edge_t> edges)
	: adjmatrix(n)
{
	assert(n > 0);
	for (auto const & e : edges)
		add(e.from, e.to);
}

/// Returns the size of the matrix (number of vertices).
adjmatrix::vertex_t adjmatrix::size() const noexcept { return n; }

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
bool adjmatrix::add(vertex_t from, vertex_t to, bool bidirectional, vertex_value_t value)
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
bool adjmatrix::remove(vertex_t from, vertex_t to, bool bidirectional)
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
adjmatrix::vertex_value_t & adjmatrix::edge(vertex_t from, vertex_t to)
{
	return m[edge_index(from, to)];
}

/// Accessor for edges. This method provides read only access
/// to the matrix and is not boundary checked.
///
/// Complexity: O(1)
adjmatrix::vertex_value_t adjmatrix::edge(vertex_t from, vertex_t to) const
{
	return m[edge_index(from, to)];
}

/// Returns a list of vertices. This function is for convinience only.
///
/// Complexity: O(n)
adjmatrix::vertex_list adjmatrix::vertices() const
{
	vertex_list v(size());
	for (vertex_t i = 0; i < n; ++i)
		v[i] = i;
	return v;
}

/// Returns a list of neighbors of v
///
/// Complexity: O(n)
adjmatrix::vertex_list adjmatrix::neighbors_of(vertex_t v) const
{
	vertex_list result;
	for (vertex_t to = 0; to < n; ++to) {
		if (to != v) {
			if (edge(v, to)) {
				result.push_back(to);
			}
		}
	}
	return result;
}

/// Returns a list of edges defined by the matrix.
///
/// Complexity: O(n^2)
adjmatrix::edge_list adjmatrix::edges() const
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
adjmatrix::vertex_t adjmatrix::num_incoming(vertex_t to) const
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
adjmatrix::vertex_t adjmatrix::num_outgoing(vertex_t from) const
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
adjmatrix::vertex_t adjmatrix::num_edges() const noexcept
{
	return std::count(m.begin(), m.end(), 1);
}
}
