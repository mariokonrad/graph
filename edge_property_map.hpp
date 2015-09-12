#ifndef __GRAPH__EDGE_PROPERTY_MAP__HPP__
#define __GRAPH__EDGE_PROPERTY_MAP__HPP__

#include <map>
#include "adj_matrix.hpp"

namespace graph
{

/// This templated provides a property map for vertices
/// of an adjacency matrix.
template <typename T> class edge_property_map
{
public:
	using size_type = adj_matrix::size_type;

private:
	/// Type of the property map.
	using PMap = std::map<adj_matrix::edge_t, T>;

private:
	/// Template which supports the finding and collecting
	/// of edges holding certain property (according to
	/// the predicate).
	template <class Predicate> class collector
	{
	private:
		adj_matrix::edge_list & vec;
		const Predicate & pred;

	public:
		collector(adj_matrix::edge_list & vec, const Predicate & pred)
			: vec(vec)
			, pred(pred)
		{
		}

		void operator()(const typename PMap::value_type & v)
		{
			if (pred(v.second))
				vec.push_back(v.first);
		}
	};

private:
	PMap p; // the properties
	size_type n; // size of the graph / number of vertices

public:
	/// Constructor to initialize the property map according to
	/// the specified adjacency matrix.
	edge_property_map(const adj_matrix & m)
		: n(m.size())
	{
	}

	edge_property_map(const edge_property_map &) = default;

	edge_property_map(edge_property_map &&) = default;

	edge_property_map & operator=(const edge_property_map &) = default;

	edge_property_map & operator=(edge_property_map &&) = default;

	/// Read/Write access to the property.
	T & prop(const adj_matrix::vertex_t & from, const adj_matrix::vertex_t & to)
	{
		return p[adj_matrix::edge_t(from, to)];
	}

	/// Read access to the property.
	const T & prop(const adj_matrix::vertex_t & from, const adj_matrix::vertex_t & to) const
	{
		return p[adj_matrix::edge_t(from, to)];
	}

	/// Read/Write accessor for the the property of the specified
	/// edge. This operator does not check boundaries.
	T & operator[](adj_matrix::edge_t i) { return p[i]; }

	/// Read accessor for the the property of the specified
	/// edge. This operator does not check boundaries.
	const T & operator[](adj_matrix::edge_t i) const { return p[i]; }

	/// Collects edges according to the specified predicate
	/// regarding its property.
	///
	/// \param[out] vec  List of edges, satisfying the predicate.
	/// \param[in]  pred Predicate to satisfy.
	template <class Predicate>
	void collect_if(adj_matrix::edge_list & vec, const Predicate & pred)
	{
		for_each(p.begin(), p.end(), collector<Predicate>(vec, pred));
	}
};
}

#endif
