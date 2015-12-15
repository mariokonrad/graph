// License: BSD
//
// Copyright (c) 2015, Mario Konrad
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by Mario Konrad.
// 4. Neither the content of this file nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef __GRAPH__ADJLIST__HPP__
#define __GRAPH__ADJLIST__HPP__

#include <algorithm>
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
/// Hits to complexity of member functions is in the form: `O(n + m)`
/// with `n` as number of vertices and `m` as number of edges.
///
class adjlist
{
public:
	using size_type = vertex;

private:
	const size_type n; // number of vertices

	// adjacency list.
	// a std::set is not being used, because it is (usually) not organized as
	// container with consecutive data in memory.
	std::vector<vertex_list> m;

	/// Returns `true` if the specified vertex list contains the specified vertex.
	static inline bool contains(const vertex_list & l, vertex v)
	{
		return std::find(std::begin(l), std::end(l), v) != std::end(l);
	}

	/// Appends the spcified vertex to the list, only if it is not already
	/// in the list.
	static inline void push_back_unique(vertex_list & l, vertex v)
	{
		if (!contains(l, v))
			l.push_back(v);
	}

	static inline void remove_vertex(vertex_list & l, vertex v)
	{
		l.erase(std::remove(std::begin(l), std::end(l), v), std::end(l));
	}

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
		assert(n > 0);
	}

	/// Constructor which takes the number of vertices and an initializer list
	/// of edges to initialize the adjacency list.
	///
	/// \param[in] n Number of vertices, i.e. the size of the graph.
	/// \param[in] edges Edges to initialize the graph with.
	adjlist(size_type n, std::initializer_list<edge> edges)
		: adjlist(n)
	{
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
	/// Complexity: O(m)
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
		push_back_unique(m[e.from], e.to);
		if (type == edge::type::bi)
			push_back_unique(m[e.to], e.from);
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
	/// Complexity: O(m)
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
		remove_vertex(m[e.from], e.to);
		if (type == edge::type::bi)
			remove_vertex(m[e.to], e.from);
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
	/// Complexity: O(m)
	bool at(edge e) const
	{
		return contains(m[e.from], e.to);
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
		return std::count_if(
			std::begin(m), std::end(m), [to](const auto & v) { return contains(v, to); });
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
			if (contains(m[i], to))
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
	/// Complexity: O(1)
	const vertex_list & outgoing(vertex from) const { return m[from]; }
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
