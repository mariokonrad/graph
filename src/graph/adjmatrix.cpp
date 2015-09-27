#include "adjmatrix.hpp"
#include <algorithm>
#include <cassert>

namespace graph
{

constexpr adjmatrix::vertex_value_t adjmatrix::no_value;

bool adjmatrix::edge_t::operator==(const edge_t & other) const
{
	return (this == &other) || ((from == other.from) && (to == other.to));
}

bool adjmatrix::edge_t::operator!=(const edge_t & other) const { return !(*this == other); }

bool adjmatrix::edge_t::operator<(const adjmatrix::edge_t & other) const
{
	if (from < other.from)
		return true;
	if (from == other.from)
		return (to < other.to);
	return false;
}

adjmatrix::edge_t::edge_t(vertex_t from, vertex_t to) noexcept : from(from), to(to) {}

adjmatrix::edge_t adjmatrix::edge_t::reverse() const { return {to, from}; }

adjmatrix::edge_t::edge_t(const std::initializer_list<vertex_t> v)
	: from(*v.begin())
	, to(*(v.begin() + 1))
{
	assert(v.size() == 2);
}

adjmatrix::vertex_t adjmatrix::edge_index(edge_t e) const noexcept { return e.from + e.to * n; }

/// Constructor to set the size of the matrix and initialize it
/// with no edges.
///
/// \param[in] n Size of the matrix.
adjmatrix::adjmatrix(vertex_t n)
	: n(n)
	, m(n * n, no_value)
{
	assert(n > 0);
}

adjmatrix::adjmatrix(vertex_t n, std::initializer_list<edge_t> edges)
	: adjmatrix(n)
{
	assert(n > 0);
	for (auto const & e : edges)
		add(e);
}

/// Returns the size of the matrix (number of vertices).
adjmatrix::vertex_t adjmatrix::size() const noexcept { return n; }

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
bool adjmatrix::add(edge_t e, edge_type type, vertex_value_t value)
{
	if ((e.from >= n) || (e.to >= n))
		return false;
	edge(e) = value;
	if (type == edge_type::bi)
		edge(e.reverse()) = value;
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
bool adjmatrix::remove(edge_t e, edge_type type)
{
	if ((e.from >= n) || (e.to >= n))
		return false;
	edge(e) = no_value;
	if (type == edge_type::bi)
		edge(e.reverse()) = no_value;
	return true;
}

/// Accessor for edges. This method provides writing access to
/// the matrix and is not boundary checked.
///
/// \note The call 'edge(e)=1' is the same as 'add(e)'.
///
/// Complexity: O(1)
adjmatrix::vertex_value_t & adjmatrix::edge(edge_t e) { return m[edge_index(e)]; }

/// Accessor for edges. This method provides read only access
/// to the matrix and is not boundary checked.
///
/// Complexity: O(1)
adjmatrix::vertex_value_t adjmatrix::edge(edge_t e) const { return m[edge_index(e)]; }

adjmatrix::vertex_value_t & adjmatrix::operator[](adjmatrix::edge_t e)
{
	return m[edge_index(e)];
}

const adjmatrix::vertex_value_t & adjmatrix::operator[](adjmatrix::edge_t e) const
{
	return m[edge_index(e)];
}

/// Returns a list of vertices. This function is for convinience only.
///
/// Complexity: O(n)
adjmatrix::vertex_list_t adjmatrix::vertices() const
{
	vertex_list_t v(size());
	std::iota(v.begin(), v.end(), 0);
	return v;
}

/// Returns a list of neighbors of v
///
/// Complexity: O(n)
adjmatrix::vertex_list_t adjmatrix::neighbors_of(vertex_t v) const
{
	vertex_list_t result;
	for (vertex_t to = 0; to < n; ++to) {
		if (to != v) {
			if (edge({v, to})) {
				result.push_back(to);
			}
		}
	}
	return result;
}

/// Returns a list of edges defined by the matrix.
///
/// Complexity: O(n^2)
adjmatrix::edge_list_t adjmatrix::edges() const
{
	edge_list_t vec;
	for (vertex_t from = 0; from < n; ++from)
		for (vertex_t to = 0; to < n; ++to)
			if (edge({from, to}))
				vec.emplace_back(from, to);
	return vec;
}

/// Returns a list of nodes from where an edge exists.
///
/// Complexity: O(n)
adjmatrix::vertex_list_t adjmatrix::incoming(vertex_t to) const
{
	vertex_list_t v;
	if (to >= n)
		return v;
	for (vertex_t i = 0; i < n; ++i)
		if (edge({i, to}))
			v.push_back(i);
	return v;
}

/// Returns a list of nodes to where an edge exists.
///
/// Complexity: O(n)
adjmatrix::vertex_list_t adjmatrix::outgoing(vertex_t from) const
{
	vertex_list_t v;
	if (from >= n)
		return v;
	for (vertex_t i = 0; i < n; ++i)
		if (edge({from, i}))
			v.push_back(from);
	return v;
}

/// Returns the total number of edges within the matrix.
///
/// Complexity: O(n^2)
adjmatrix::vertex_t adjmatrix::count_edges() const noexcept
{
	return std::count_if(m.begin(), m.end(), [](auto const v) { return v != no_value; });
}
}
