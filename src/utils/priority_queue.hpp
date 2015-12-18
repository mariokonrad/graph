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

#ifndef __UTILS__PRIORITY_QUEUE__HPP__
#define __UTILS__PRIORITY_QUEUE__HPP__

#include <algorithm>
#include <limits>
#include <vector>

namespace utils
{
/// Priority queue
///
/// Uses a std::vector<T> as unerlying contanier.
///
/// The interface is very similar to std::priority_queue with some
/// extensions:
/// - access to the underlying container for iterative purposes (begin,
///   end, cbegin, cend)
/// - access to the container for finding elements (find_if)
/// - feature to update a specific place within the container, while
///   maintaining the constraints of a priority queue.
///
/// Features not provided:
/// - configurable container
/// - swap
///
/// \tparam T The data type to manage.
/// \tparam Compare Type of the comparison functionality, must be
///   default constructible.
///
template <class T, class Compare = std::less<T>> class priority_queue
{
public:
	using const_reference = const T &;
	using container = std::vector<T>;
	using size_type = typename container::size_type;
	using const_iterator = typename container::const_iterator;

	/// \{
	/// Construction of the queue using (copying) existing data.
	///
	/// \param[in] cmp The comparison functor
	/// \param[in] d A container to initialize the queue, may contain data
	priority_queue(Compare cmp, const container & d)
		: comp(cmp)
		, data(d)
	{
		std::make_heap(std::begin(data), std::end(data), comp);
	}

	/// Default constructor. Also provides to override default parameters.
	/// Ability to move an existing container into the queue.
	///
	/// \param[in] cmp The comparison functor
	/// \param[in] d A container to initialize the queue, may contain data
	explicit priority_queue(const Compare & cmp = Compare{}, container && d = container{})
		: comp(cmp)
		, data(d)
	{
		std::make_heap(std::begin(data), std::end(data), comp);
	}

	priority_queue(const priority_queue &) = default;
	priority_queue(priority_queue &&) noexcept = default;
	/// \}

	/// \{
	~priority_queue() {}
	/// \}

	/// \{
	priority_queue & operator=(const priority_queue &) = default;
	priority_queue & operator=(priority_queue &&) noexcept = default;
	/// \}

	/// \{
	size_type size() const { return data.size(); }
	bool empty() const { return data.empty(); }
	/// \}

	/// \{
	const_iterator begin() const { return data.begin(); }
	const_iterator end() const { return data.end(); }
	const_iterator cbegin() const { return data.begin(); }
	const_iterator cend() const { return data.end(); }
	/// \}

	/// \{
	/// Constructs items in the queue.
	///
	/// Complexity: O(log n)
	template <class... Args> void emplace(Args &&... args)
	{
		data.emplace_back(std::forward<Args...>(args)...);
		std::push_heap(std::begin(data), std::end(data), comp);
	}

	/// Pushes a new value into the queue.
	///
	/// Complexity: O(log n)
	void push(const_reference t)
	{
		data.push_back(t);
		std::push_heap(std::begin(data), std::end(data), comp);
	}

	/// Pushes a new value into the queue.
	///
	/// Complexity: O(log n)
	void push(T && t)
	{
		data.push_back(std::move(t));
		std::push_heap(std::begin(data), std::end(data), comp);
	}
	/// \}

	/// \{
	const_reference top() const { return data.front(); }

	/// Pops the top value from the queue.
	///
	/// Complexity: O(log n)
	void pop()
	{
		std::pop_heap(std::begin(data), std::end(data), comp);
		data.pop_back();
	}
	/// \}

	/// \{
	/// Re-creates the heap.
	///
	/// Complexity: O(log n) (same as std::make_heap)
	void update() { std::make_heap(std::begin(data), std::end(data), comp); }

	/// Update of a specific value within the container. The heap will
	/// be created newly.
	///
	/// Complexity: O(log n) (same as std::make_heap)
	///
	/// \param[in] i Index at which position the element should be updated.
	/// \param[in] t The data to write to the specified index. The old
	///   value at the specified index will be overwritten.
	void update(const_iterator i, const_reference t)
	{
		if (i >= data.cend())
			return;
		data[std::distance(data.cbegin(), i)] = t;
		update();
	}
	/// \}

private:
	Compare comp;
	container data;
};
}

#endif
