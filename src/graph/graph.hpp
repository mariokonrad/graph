// License: BSD
//
// Copyright (c) 2017, Mario Konrad
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

#ifndef GRAPH__GRAPH__HPP
#define GRAPH__GRAPH__HPP

#include <graph/type_traits.hpp>
#include <graph/vertex.hpp>
#include <graph/edge.hpp>

namespace graph
{
/// Returns number of nodes in the graph.
template <class Graph, typename = typename std::enable_if<
	   detail::has_t_size_type<Graph>::value
	&& detail::has_f_size<Graph>::value,
	void>::type>
typename Graph::size_type size(const Graph & g) noexcept
{
	return g.size();
}

/// Returns the number of incoming edges to the specified vertex.
///
/// If the specified vertex is invalid the function returns 0.
///
/// Complexity: O(n)
template <class Graph, typename
	= typename std::enable_if<detail::has_f_integral_type_at<Graph>::value, void>::type>
typename Graph::size_type count_incoming(const Graph & m, vertex to)
{
	if (to >= size(m))
		return 0;
	typename Graph::size_type num = 0;
	for (vertex from = 0; from < size(m); ++from)
		if (m.at({from, to}))
			++num;
	return num;
}

/// Returns a list of nodes from where an edge exists.
///
/// If the specified vertex is invalid, an empty list will return.
///
/// Complexity: O(n)
template <class Graph, typename
	= typename std::enable_if<detail::has_f_integral_type_at<Graph>::value, void>::type>
vertex_list incoming(const Graph & m, vertex to)
{
	vertex_list v;
	if (to >= size(m))
		return v;
	for (vertex from = 0; from < size(m); ++from)
		if (m.at({from, to}))
			v.push_back(from);
	return v;
}

/// Returns the number of outgoing edges of the specified vertex.
///
/// If the specified vertex is invalid the function returns 0.
///
/// Complexity: O(n)
template <class Graph, typename
	= typename std::enable_if<detail::has_f_integral_type_at<Graph>::value, void>::type>
typename Graph::size_type count_outgoing(const Graph & m, vertex from)
{
	if (from >= size(m))
		return 0;
	typename Graph::size_type num = 0;
	for (vertex to = 0; to < size(m); ++to)
		if (m.at({from, to}))
			++num;
	return num;
}

/// Returns a list of nodes to where an edge exists.
///
/// If the specified vertex is invalid, an empty list will return.
///
/// Complexity: O(n)
template <class Graph, typename
	= typename std::enable_if<detail::has_f_integral_type_at<Graph>::value, void>::type>
vertex_list outgoing(const Graph & m, vertex from)
{
	vertex_list v;
	if (from >= size(m))
		return v;
	for (vertex to = 0; to < size(m); ++to)
		if (m.at({from, to}))
			v.push_back(to);
	return v;
}

/// Returns a list of vertices. This function is for convinience only.
template <class Graph,
	typename = typename std::enable_if<detail::has_f_vertices<Graph>::value, void>::type>
vertex_list vertices(const Graph & m)
{
	return m.vertices();
}

/// Returns the total number of edges within the graph.
template <class Graph,
	typename = typename std::enable_if<detail::has_f_count_edges<Graph>::value, void>::type>
typename Graph::size_type count_edges(const Graph & m) noexcept
{
	return m.count_edges();
}

/// Returns a list of edges defined by the matrix.
template <class Graph,
	typename = typename std::enable_if<detail::has_f_edges<Graph>::value, void>::type>
edge_list edges(const Graph & m)
{
	return m.edges();
}
}

#endif
