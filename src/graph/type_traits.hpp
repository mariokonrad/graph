#ifndef __GRAPH__TYPE_TRAITS__HPP__
#define __GRAPH__TYPE_TRAITS__HPP__

#include <graph/edge.hpp>

namespace graph
{
/// \cond DEV
namespace detail
{
// types

/// Checks for type `size_type`
template <class T> class has_t_size_type
{
private:
	template <typename U, typename = typename U::size_type> static std::true_type test(int);
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for type `value_type`
template <class T> class has_t_value_type
{
private:
	template <typename U, typename = typename U::value_type> static std::true_type test(int);
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for type `mapped_type`
template <class T> class has_t_mapped_type
{
private:
	template <typename U, typename = typename U::mapped_type> static std::true_type test(int);
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for type `const_iterator`
template <class T> class has_t_const_iterator
{
private:
	template <typename U, typename = typename U::const_iterator>
	static std::true_type test(int);
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

// member functions

/// Checks for member function `size_type size() const`
template <class T, typename = typename std::enable_if<has_t_size_type<T>::value, void>::type>
class has_f_size
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		std::declval<const U>().size() == typename U::size_type{}, std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `value_type at(edge) const`
template <class T, typename = typename std::enable_if<has_t_value_type<T>::value, void>::type>
class has_f_at
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		std::declval<const U>().at(edge{vertex{}, vertex{}}) == typename U::value_type{},
		std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `vertex_list vertices() const`
template <class T> class has_f_vertices
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		std::declval<const U>().vertices() == vertex_list{},
		std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `vertex_list outgoing(vertex) const`
template <class T> class has_f_outgoing
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		std::declval<const U>().outgoing(vertex{}) == vertex_list{}, std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `const_iterator end() const`
template <class T,
	typename = typename std::enable_if<has_t_const_iterator<T>::value, void>::type>
class has_f_end
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		std::declval<const U>().end() == typename U::const_iterator{}, std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `const_iterator find(edge) const`
template <class T,
	typename = typename std::enable_if<has_t_const_iterator<T>::value, void>::type>
class has_f_find
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		std::declval<const U>().find(edge{vertex{}, vertex{}}) == typename U::const_iterator{},
		std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};
}
/// \endcond
}

#endif
