#ifndef __GRAPH__VERTEX_PROPERTY_MAP__HPP__
#define __GRAPH__VERTEX_PROPERTY_MAP__HPP__

#include <map>
#include "adj_matrix.hpp"

namespace graph
{

/// This templated provides a property map for vertices
/// of an adjacency matrix.
template <typename T> class vertex_property_map
{
public:
	using size_type = adj_matrix::size_type;

private:
	/// Type of the property map.
	using PMap = std::map<adj_matrix::vertex_t, T>;

private:
	/// Template which supports the finding and collecting
	/// of vertices holding certain property (according to
	/// the predicate).
	template <class Predicate> class collector
	{
	private:
		adj_matrix::vertex_list & vec;
		const Predicate & pred;

	public:
		collector(adj_matrix::vertex_list & vec, const Predicate & pred)
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
	vertex_property_map(size_type n)
		: n(n)
	{
	}

	/// Constructor to initialize the property map according to
	/// the specified adjacency matrix.
	vertex_property_map(const vertex_property_map &) = default;

	vertex_property_map(vertex_property_map &&) = default;

	vertex_property_map & operator=(const vertex_property_map &) = default;

	vertex_property_map & operator=(vertex_property_map &&) = default;

	/// Sets the value for the specified vertex.
	/// This method checks boundaries.
	///
	/// \param[in] v    Vertex to set the property for.
	/// \param[in] prop The property to set.
	/// \return true=success, false=vertex does not exist
	bool set(adj_matrix::vertex_t v, const T & prop)
	{
		if (v >= n)
			return false;
		p[v] = prop;
		return true;
	}

	/// Read/Write accessor for the the property of the specified
	/// vertex. This operator does not check boundaries.
	T & operator[](adj_matrix::vertex_t v) { return p[v]; }

	/// Read accessor for the the property of the specified
	/// vertex. This operator does not check boundaries.
	const T & operator[](adj_matrix::vertex_t v) const { return p[v]; }

	/// Collects vertices according to the specified predicate
	/// regarding its property.
	///
	/// \param[out] vec  List of vertices, satisfying the predicate.
	/// \param[in]  pred Predicate to satisfy.
	template <class Predicate>
	void collect_if(adj_matrix::vertex_list & vec, const Predicate & pred)
	{
		for_each(p.begin(), p.end(), collector<Predicate>(vec, pred));
	}
};
}

#endif
