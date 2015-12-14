#ifndef __GRAPH__ADJLIST__HPP__
#define __GRAPH__ADJLIST__HPP__

#include <algorithm>
#include <set>
#include <vector>
#include <cassert>
#include <graph/edge.hpp>

namespace graph
{
/// Represents a graph as adjacency list.
///
/// Properties for vertices and/or edges are not possible.
///
/// Once constructed, the size is constant. It is not possible to
/// grow or shrink.
///
class adjlist
{
public:
	using size_type = vertex;

private:
	const size_type n; // number of vertices

	// adjacency list, using set to prevent duplicates
	std::vector<std::set<vertex>> m;

public:
	/// \{
	/// Constructor to set the size of the graph and initialize it
	/// with no edges.
	///
	/// \param[in] n Size of the graph.
	adjlist(size_type n)
		: n(n)
		, m(n)
	{
	}

	adjlist(size_type n, std::initializer_list<edge> edges)
		: adjlist(n)
	{
		assert(n > 0);
		for (auto const & e : edges)
			add(e);
	}

	adjlist(const adjlist &) = default;
	adjlist(adjlist &&) = default;
	/// \}

	/// \{
	adjlist & operator=(const adjlist &) = default;
	adjlist & operator=(adjlist &&) = default;
	/// \}

	/// \{
	/// Adds an edge to the graph.
	///
	/// Complexity: O(1)
	///
	/// \param[in] e The edge to add
	/// \param[in] type Type of edge to add
	/// \return true on success, false otherwise
	///
	/// \note This function performs boundary check.
	bool add(edge e, edge::type type = edge::type::uni)
	{
		if ((e.from >= n) || (e.to >= n))
			return false;
		m[e.from].insert(e.to);
		if (type == edge::type::bi)
			m[e.to].insert(e.from);
		return true;
	}

	/// \see add()
	bool add(vertex from, vertex to, edge::type type = edge::type::uni)
	{
		return add({from, to}, type);
	}
	/// \}

	/// \{
	/// Removes an edge from the graph.
	///
	/// Complexity: O(1)
	///
	/// \param[in] e Edge to remove
	/// \param[in] type Type of edge to add
	/// \return true on success, false otherwise
	///
	/// \note This function performs boundary check.
	bool remove(edge e, edge::type type = edge::type::uni)
	{
		if ((e.from >= n) || (e.to >= n))
			return false;
		m[e.from].erase(m[e.from].find(e.to));
		if (type == edge::type::bi)
			m[e.to].erase(m[e.to].find(e.from));
		return true;
	}

	/// \see remove()
	bool remove(vertex from, vertex to, edge::type type = edge::type::uni)
	{
		return remove({from, to}, type);
	}
	/// \}

	/// Accessor for edges. This method provides read only access
	/// to the graph and is not boundary checked.
	///
	/// Complexity: O(1)
	bool at(edge e) const
	{
		const auto & v = m[e.from];
		return v.find(e.to) != v.end();
	}

	/// Convenience function. See \see at(edge) const
	bool at(vertex from, vertex to) const { return at({from, to}); }

	/// Accessor for edges, uses index operator.
	bool operator[](edge e) const { return at(e); }
	/// \}

	/// \{
	/// Returns the size of the graph (number of vertices).
	size_type size() const noexcept { return n; }

	/// Returns a list of vertices. This function is for convinience only.
	///
	/// Complexity: O(n)
	vertex_list vertices() const
	{
		vertex_list v(size());
		std::iota(v.begin(), v.end(), 0);
		return v;
	}

	/// Returns the number of incoming edges to the specified vertex.
	///
	/// If the specified vertex is invalid the function returns 0.
	///
	/// Complexity: O(n)
	size_type count_incoming(vertex to) const
	{
		if (to >= n)
			return 0;
		size_type num = 0;
		for (auto const & v : m)
			num += (v.find(to) != v.end()) ? 1 : 0;
		return num;
	}

	/// Returns a list of nodes from where an edge exists.
	///
	/// If the specified vertex is invalid, an empty list will return.
	///
	/// Complexity: O(n)
	vertex_list incoming(vertex to) const
	{
		vertex_list v;
		if (to >= n)
			return v;
		for (vertex i = 0; i < n; ++i)
			if (m[i].find(to) != m[i].end())
				v.push_back(i);
		return v;
	}

	/// Returns the number of outgoing edges of the specified vertex.
	///
	/// If the specified vertex is invalid the function returns 0.
	///
	/// Complexity: O(1)
	size_type count_outgoing(vertex from) const
	{
		if (from >= n)
			return 0;
		return m[from].size();
	}

	/// Returns a list of nodes to where an edge exists.
	///
	/// If the specified vertex is invalid, an empty list will return.
	///
	/// Complexity: O(n)
	vertex_list outgoing(vertex from) const
	{
		auto const & v = m[from];
		return vertex_list(std::begin(v), std::end(v));
	}
	/// \}

	/// \{
	/// Returns the total number of edges within the graph.
	///
	/// Complexity: O(n)
	size_type count_edges() const noexcept
	{
		size_type sum = 0;
		for (auto const & v : m)
			sum += v.size();
		return sum;
	}

	/// Returns a list of edges defined by the graph.
	///
	/// Complexity: O(n + m)
	edge_list edges() const
	{
		edge_list vec;
		for (vertex from = 0; from < n; ++from)
			for (const auto & to : m[from])
				vec.emplace_back(from, to);
		return vec;
	}
	/// \}
};
}

#endif
