#ifndef __GRAPH__PROPERTY_MAP__HPP__
#define __GRAPH__PROPERTY_MAP__HPP__

#include <map>
#include <stdexcept>
#include <algorithm>
#include "adjmatrix.hpp"

namespace graph
{

namespace detail
{
/// This template provides a property map for graph related
/// entities (edges, vertices) of an adjacency matrix.
///
/// Uses a std::map to store the mapping.
///
template <class T, class Container> class property_map
{
public:
	using Element = typename Container::value_type;

private:
	const adjmatrix::size_type n; // size of the graph / number of vertices
	std::map<Element, T> properties; // the properties

public:
	/// Constructor to initialize the property map according to
	/// the specified adjacency matrix.
	property_map(const adjmatrix & m)
		: n(m.size())
	{
	}

	property_map(const property_map &) = default;
	property_map(property_map &&) = default;

	property_map & operator=(const property_map &) = default;
	property_map & operator=(property_map &&) = default;

	/// Returns true if a property for the specified element exists, otherwise
	/// it returns false.
	bool exists(const Element & i) const { return properties.find(i) != properties.end(); }

	/// Read/Write access to an existing property.
	/// This method checks boundaries and throws an exception if
	/// the entry does not exist.
	T & prop(const Element & i)
	{
		if (!exists(i))
			throw std::out_of_range{"element not in map"};
		return properties[i];
	}

	/// Read access to an existing property.
	/// This method checks boundaries and throws an exception if
	/// the entry does not exist.
	const T & prop(const Element & i) const
	{
		auto const it = properties.find(i);
		if (it == properties.end())
			throw std::out_of_range{"element not in map"};
		return it->second;
	}

	/// Read/Write accessor for the the property of the specified entry.
	/// This operator does not check boundaries.
	T & operator[](const Element & i) { return properties[i]; }

	/// Read accessor for the the property of the specified entry.
	/// This operator does not check boundaries.
	const T & operator[](const Element & i) const { return properties[i]; }

	/// Collects entities according to the specified predicate
	/// regarding its property.
	///
	/// \param[in] pred Predicate to satisfy.
	/// \return List of edges, satisfying the predicate.
	template <class Predicate> Container collect_if(Predicate pred) const
	{
		Container result;
		for_each(properties.begin(), properties.end(), [&result, pred](const auto & v) {
			if (pred(v.second))
				result.push_back(v.first);
		});
		return result;
	}
};
}

/// Maps configurable property to a list of edges.
template <class T> using edge_property_map = detail::property_map<T, adjmatrix::edge_list>;

/// Maps configurable property to a list of vertices.
template <class T> using vertex_property_map = detail::property_map<T, adjmatrix::vertex_list>;
}

#endif
