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

#ifndef GRAPH__EDGE__HPP
#define GRAPH__EDGE__HPP

#include <vector>
#include <functional>
#include <graph/vertex.hpp>

namespace graph
{
/// Type for the edge, connection two vertices.
///
/// Objects of this struct are immutable.
///
/// \note This structure is not what is stored within the adjacency matrix,
///       it is a representation of an edge for easier handling
///       outside the adjacency matrix.
///
/// \note Objects of `edge` do not store any information about their
///       type. An object of this struct represents always an unidirectional
///       edge. The enumeration of types is located within this struct
///       as a logical grouping.
///
struct edge {
	/// Enuemrates all possible types of edges.
	enum class type {
		uni, ///< unidirectional
		bi ///< bidirectional
	};

	const vertex from; ///< Starting vertex of the edge.
	const vertex to; ///< Ending vertex of the edge.

	constexpr edge(vertex from, vertex to) noexcept : from(from), to(to) {}

	edge(const edge &) noexcept = default;
	edge(edge &&) noexcept = default;

	edge & operator=(const edge &) = default;
	edge & operator=(edge &&) noexcept = default;

	constexpr edge reverse() const { return {to, from}; }

	/// Operator less, necessary to use edges in maps.
	///
	/// Precedence: from, to
	///
	/// \todo Implement this function as `constexpr`. Sadly GCC 4.9 does not
	///       support relaxed `constexpr` requirements, even with `-std=c++1y`.
	friend bool operator<(const edge & a, const edge & b)
	{
		if (a.from < b.from)
			return true;
		if (a.from == b.from)
			return a.to < b.to;
		return false;
	}

	/// Comparison operator for equality.
	constexpr friend bool operator==(const edge & a, const edge & b)
	{
		return (&a == &b) || ((a.from == b.from) && (a.to == b.to));
	}

	/// Comparison operator for inequality.
	constexpr friend bool operator!=(const edge & a, const edge & b) { return !(a == b); }
};

/// Container type for a list of edges.
using edge_list = std::vector<edge>;

/// Default hash function for edges.
///
/// Please note: it does not claim to be a good hash.
struct edge_hash {
	std::size_t operator()(const graph::edge & e) const
	{
		std::hash<graph::vertex> h;
		return 0xabcdef123 + h(e.from) + (h(e.from) << 4) + (h(e.to) << 3);
	}
};
}

#endif
