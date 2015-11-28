#include "adjmatrix.hpp"
#include <algorithm>
#include <cassert>

namespace graph
{

constexpr adjmatrix::value_type adjmatrix::no_value;
constexpr adjmatrix::value_type adjmatrix::edge_value;

/// Constructor to set the size of the matrix and initialize it
/// with no edges.
///
/// \param[in] n Size of the matrix.
adjmatrix::adjmatrix(size_type n)
	: n(n)
	, m(n * n, no_value)
{
	assert(n > 0);
}

adjmatrix::adjmatrix(size_type n, std::initializer_list<edge> edges)
	: adjmatrix(n)
{
	assert(n > 0);
	for (auto const & e : edges)
		add(e);
}

/// Returns the size of the matrix (number of vertices).
adjmatrix::size_type adjmatrix::size() const noexcept { return n; }

/// Adds an edge to the matrix.
///
/// Complexity: O(1)
///
/// \param[in] e The edge to add
/// \param[in] type Type of edge to add
/// \param[in] value Value for the specified edge
/// \return true on success, false otherwise
///
/// \note This function performs boundary check.
bool adjmatrix::add(edge e, edge::type type, value_type value)
{
	if ((e.from >= n) || (e.to >= n))
		return false;
	get(e) = value;
	if (type == edge::type::bi)
		get(e.reverse()) = value;
	return true;
}

/// Removes an edge from the matrix.
///
/// Complexity: O(1)
///
/// \param[in] e Edge to remove
/// \param[in] type Type of edge to add
/// \return true on success, false otherwise
///
/// \note This function performs boundary check.
bool adjmatrix::remove(edge e, edge::type type)
{
	if ((e.from >= n) || (e.to >= n))
		return false;
	get(e) = no_value;
	if (type == edge::type::bi)
		get(e.reverse()) = no_value;
	return true;
}

/// Accessor for edges. This method provides writing access to
/// the matrix and is not boundary checked.
///
/// \note The call 'get(e)=edge_value' is the same as 'add(e)'.
///
/// Complexity: O(1)
adjmatrix::value_type & adjmatrix::get(edge e) { return m[edge_index(e)]; }

/// Accessor for edges. This method provides read only access
/// to the matrix and is not boundary checked.
///
/// Complexity: O(1)
adjmatrix::value_type adjmatrix::get(edge e) const { return m[edge_index(e)]; }

/// \see get(edge)
adjmatrix::value_type & adjmatrix::operator[](edge e) { return m[edge_index(e)]; }

/// \see get(edge) const
adjmatrix::value_type adjmatrix::operator[](edge e) const { return m[edge_index(e)]; }

/// Returns a list of vertices. This function is for convinience only.
///
/// Complexity: O(n)
vertex_list adjmatrix::vertices() const
{
	vertex_list v(size());
	std::iota(v.begin(), v.end(), 0);
	return v;
}

/// Returns a list of neighbors of `v`
///
/// Complexity: O(n)
vertex_list adjmatrix::neighbors_of(vertex v) const
{
	vertex_list result;
	for (vertex to = 0; to < n; ++to) {
		if (to != v) {
			if (get({v, to})) {
				result.push_back(to);
			}
		}
	}
	return result;
}

/// Returns a list of edges defined by the matrix.
///
/// Complexity: O(n^2)
edge_list adjmatrix::edges() const
{
	edge_list vec;
	for (vertex from = 0; from < n; ++from)
		for (vertex to = 0; to < n; ++to)
			if (get({from, to}))
				vec.emplace_back(from, to);
	return vec;
}

/// Returns a list of nodes from where an edge exists.
///
/// If the specified vertex is invalid, an empty list will return.
///
/// Complexity: O(n)
vertex_list adjmatrix::incoming(vertex to) const
{
	vertex_list v;
	if (to >= n)
		return v;
	for (vertex i = 0; i < n; ++i)
		if (get({i, to}))
			v.push_back(i);
	return v;
}

/// Returns a list of nodes to where an edge exists.
///
/// If the specified vertex is invalid, an empty list will return.
///
/// Complexity: O(n)
vertex_list adjmatrix::outgoing(vertex from) const
{
	vertex_list v;
	if (from >= n)
		return v;
	for (vertex i = 0; i < n; ++i)
		if (get({from, i}))
			v.push_back(from);
	return v;
}

/// Returns the total number of edges within the matrix.
///
/// Complexity: O(n^2)
adjmatrix::size_type adjmatrix::count_edges() const noexcept
{
	return std::count_if(m.begin(), m.end(), [](auto const v) { return v != no_value; });
}
}
