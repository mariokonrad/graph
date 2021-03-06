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

#ifndef GRAPH__ADJMATRIX__HPP
#define GRAPH__ADJMATRIX__HPP

#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>
#include <graph/edge.hpp>

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
	using size_type = vertex;

	/// Representation of vertices within the matrix
	using value_type = int;

	/// Default values for states within the adjacency matrix.
	enum : value_type {
		/// Indicates no edge between vertices.
		no_value = 0,

		/// Indicates an edge between vertices.
		edge_value = 1,
	};

private:
	const size_type n; // number of vertices
	std::vector<value_type> m; // adjacency matrix

	/// Computes the index of the specified edge within the adjacency matrix,
	/// which is implemented as std::vector.
	vertex edge_index(edge e) const noexcept { return e.from + e.to * n; }

public:
	/// \{
	/// Constructor to set the size of the matrix and initialize it
	/// with no edges.
	///
	/// \param[in] n Size of the matrix.
	adjmatrix(size_type n)
		: n(n)
		, m(n * n, no_value)
	{
		assert(n > 0);
	}

	adjmatrix(size_type n, std::initializer_list<edge> edges)
		: adjmatrix(n)
	{
		assert(n > 0);
		for (auto const & e : edges)
			add(e);
	}

	adjmatrix(const adjmatrix &) = default;
	adjmatrix(adjmatrix &&) = default;
	/// \}

	/// \{
	adjmatrix & operator=(const adjmatrix &) = default;
	adjmatrix & operator=(adjmatrix &&) = default;
	/// \}

	/// \{
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
	bool add(edge e, edge::type type = edge::type::uni, value_type value = edge_value)
	{
		if ((e.from >= n) || (e.to >= n))
			return false;
		at(e) = value;
		if (type == edge::type::bi)
			at(e.reverse()) = value;
		return true;
	}

	/// \see add()
	bool add(vertex from, vertex to, edge::type type = edge::type::uni,
		value_type value = edge_value)
	{
		return add({from, to}, type, value);
	}
	/// \}

	/// \{
	/// Removes an edge from the matrix.
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
		at(e) = no_value;
		if (type == edge::type::bi)
			at(e.reverse()) = no_value;
		return true;
	}

	/// \see remove()
	bool remove(vertex from, vertex to, edge::type type = edge::type::uni)
	{
		return remove({from, to}, type);
	}
	/// \}

	/// \{
	/// Accessor for edges. This method provides writing access to
	/// the matrix and is not boundary checked.
	///
	/// \note The call 'at(e)=edge_value' is the same as 'add(e)'.
	///
	/// Complexity: O(1)
	value_type & at(edge e) { return m[edge_index(e)]; }

	/// Accessor for edges. This method provides read only access
	/// to the matrix and is not boundary checked.
	///
	/// Complexity: O(1)
	value_type at(edge e) const { return m[edge_index(e)]; }

	/// Convenience function. See \see at(edge)
	value_type & at(vertex from, vertex to) { return at({from, to}); }

	/// Convenience function. See \see at(edge) const
	value_type at(vertex from, vertex to) const { return at({from, to}); }

	/// Accessor for edges, uses index operator.
	value_type & operator[](edge e) { return m[edge_index(e)]; }

	/// Accessor for edges, uses index operator.
	value_type operator[](edge e) const { return m[edge_index(e)]; }
	/// \}

	/// \{
	/// Returns the size of the matrix (number of vertices).
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
		for (vertex from = 0; from < n; ++from)
			if (at({from, to}))
				++num;
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
		for (vertex from = 0; from < n; ++from)
			if (at({from, to}))
				v.push_back(from);
		return v;
	}

	/// Returns the number of outgoing edges of the specified vertex.
	///
	/// If the specified vertex is invalid the function returns 0.
	///
	/// Complexity: O(n)
	size_type count_outgoing(vertex from) const
	{
		if (from >= n)
			return 0;
		size_type num = 0;
		for (vertex to = 0; to < n; ++to)
			if (at({from, to}))
				++num;
		return num;
	}

	/// Returns a list of nodes to where an edge exists.
	///
	/// If the specified vertex is invalid, an empty list will return.
	///
	/// Complexity: O(n)
	vertex_list outgoing(vertex from) const
	{
		vertex_list v;
		if (from >= n)
			return v;
		for (vertex to = 0; to < n; ++to)
			if (at({from, to}))
				v.push_back(to);
		return v;
	}
	/// \}

	/// \{
	/// Returns the total number of edges within the matrix.
	///
	/// Complexity: O(n^2)
	size_type count_edges() const noexcept
	{
		return std::count_if(m.begin(), m.end(), [](auto const v) { return v != no_value; });
	}

	/// Returns a list of edges defined by the matrix.
	///
	/// Complexity: O(n^2)
	edge_list edges() const
	{
		edge_list vec;
		for (vertex from = 0; from < n; ++from)
			for (vertex to = 0; to < n; ++to)
				if (at({from, to}))
					vec.emplace_back(from, to);
		return vec;
	}
	/// \}
};
}

#endif
