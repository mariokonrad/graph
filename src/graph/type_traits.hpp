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

#ifndef __GRAPH__TYPE_TRAITS__HPP__
#define __GRAPH__TYPE_TRAITS__HPP__

// This file and its content is needed as long as concepts are not
// part of the language.

#include <type_traits>
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
		std::declval<const U>().at(std::declval<edge>()) == typename U::value_type{},
		std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `integral_type at(edge) const`
template <class T> class has_f_integral_type_at
{
private:
	template <typename U>
	static auto test(int)
		-> decltype(std::declval<const U>().at(std::declval<edge>()), std::true_type{});
	template <typename> static std::false_type test(...);

	// Return type of function `at(edge) const`
	using Result = decltype(std::declval<const T>().at(std::declval<edge>()));

public:
	enum {
		value = std::is_same<decltype(test<T>(0)), std::true_type>::value
			&& std::is_integral<Result>::value
	};
};

/// Checks for member function `vertex_list vertices() const`
template <class T> class has_f_vertices
{
private:
	template <typename U>
	static auto test(int)
		-> decltype(std::declval<const U>().vertices() == vertex_list{}, std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `vertex_list outgoing(vertex) const`
template <class T> class has_f_outgoing
{
private:
	template <typename U>
	static auto test(int)
		-> decltype(std::declval<const U>().outgoing(std::declval<vertex>()) == vertex_list{},
			std::true_type{});
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
		std::declval<const U>().find(std::declval<edge>()) == typename U::const_iterator{},
		std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `void remove(edge)`
template <class T> class has_f_remove
{
private:
	template <typename U>
	static auto test(int)
		-> decltype(std::declval<U>().remove(std::declval<edge>()), std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `size_type count_incoming(vertex) const`
template <class T,
	typename = typename std::enable_if<detail::has_t_size_type<T>::value, void>::type>
class has_f_count_incoming
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		std::declval<const U>().count_incoming(std::declval<vertex>()), std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

/// Checks for member function `size_type count_edges() const`
template <class T,
	typename = typename std::enable_if<detail::has_t_size_type<T>::value, void>::type>
class has_f_count_edges
{
private:
	template <typename U>
	static auto test(int) -> decltype(std::declval<const U>().count_edges(), std::true_type{});
	template <typename> static std::false_type test(...);

public:
	enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};
}
/// \endcond
}

#endif
