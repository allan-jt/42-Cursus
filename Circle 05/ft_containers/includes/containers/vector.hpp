/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		vector.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/21 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <exception>
#include <stdexcept>

#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"
#include "../type_traits/is_integral.hpp"
#include "../type_traits/enable_if.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../iterators/vector_iterator.hpp"

// NUMERICAL
#define	ZERO			0
#define	ONE				1
#define GROWTH_FACTOR	2

// MISCELLANEOUS
#define ENABLE_IF		ft::enable_if
#define NOT_INTEGRAL	!ft::is_integral<InputIterator>::value
#define VEC_TYPE		vector<T, Alloc>

namespace ft { 
template< class T, class Alloc = std::allocator<T> > class vector {
	public:
/* 		Types_________________________________________________________________*/
		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef value_type			&reference;
		typedef const value_type	&const_reference;		
		typedef value_type			*pointer;
		typedef const value_type	*const_pointer;
		typedef ptrdiff_t 			difference_type;
		typedef size_t				size_type;
		
		typedef typename ft::vector_iterator<T>			iterator;
		typedef typename ft::vector_iterator<const T>	const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	
	private:
/* 		Attributes____________________________________________________________*/
		pointer			_start;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

	public:
/* 		Constructors, destructors, & assignment operator overload_____________*/
		explicit vector(const allocator_type &alloc = allocator_type()) {
			_init(ZERO, alloc);
		}

		explicit vector(size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type()) {
			
			_init(n, alloc);
			_construct(ZERO, _size, val);
		}

		template< class InputIterator >
		vector(InputIterator first, InputIterator last,
			const allocator_type &alloc = allocator_type(),
				typename ENABLE_IF<NOT_INTEGRAL>::type* = NULL) {
			_init(std::distance(first, last), alloc);
			_construct(ZERO, first, last);
		}
		
		vector(const vector &x) {			
			_init(x.size(), x.get_allocator());
			_construct(ZERO, x.begin(), x.end());
		}

		~vector() {_delete_all();}
		
		vector &operator=(const vector &x) {
			if (this != &x) {
				assign(x.begin(), x.end());
			}
			return *this;
		}

/* 		Iterators_____________________________________________________________*/
		iterator		begin() 		{return iterator(_start);}
		const_iterator	begin() const 	{return const_iterator(_start);}
		iterator		end() 			{return iterator(_start + _size);}
		const_iterator	end() const 	{return const_iterator(_start + _size);}

		reverse_iterator		rbegin() {return reverse_iterator(end());}
		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(end());
		}
		reverse_iterator		rend() {return reverse_iterator(begin());}
		const_reverse_iterator	rend() const {
			return const_reverse_iterator(begin());
		}

/* 		Capacity______________________________________________________________*/
		size_type 	size() const 		{return _size;}
		size_type 	max_size() const 	{return _alloc.max_size();}
		size_type 	capacity() const 	{return _capacity;}
		bool		empty() const 		{return _size == ZERO;}
		
		void	reserve(size_type n) {
			if (n <= _capacity)
				return;
			_check_max_size_exceeded(n);
			
			size_type orig_size = _size;
			size_type double_capacity = _capacity * GROWTH_FACTOR;
			size_type new_capacity = std::max(n,
				std::min(double_capacity, max_size()));
			
			pointer	_new_start = _alloc.allocate(new_capacity);
			if (_start)
				std::uninitialized_copy(begin(), end(), _new_start);
			_delete_all();
			_capacity = new_capacity;
			_size = orig_size;
			_start = _new_start;
		}

/* 		Element access________________________________________________________*/
		allocator_type		get_allocator() const 			{return _alloc;}
		reference 			operator[](size_type n) 		{return _start[n];}
		const_reference		operator[](size_type n) const	{return _start[n];}
		
		reference	at(size_type n) {
			_check_arr_size_exceeded(n);
			return _start[n];
		}
		const_reference	at(size_type n) const {
			_check_arr_size_exceeded(n);
			return _start[n];
		}

		reference			front() 		{return *_start;}
		const_reference		front() const 	{return *_start;}
		reference			back() 			{return *(_start + _size - ONE);}
		const_reference		back() const	{return *(_start + _size - ONE);}
		pointer				data()			{return empty() ? NULL : _start;}
		const_pointer		data() const	{return empty() ? NULL : _start;}

/* 		Modifiers_____________________________________________________________*/
		void	resize(size_type n, value_type val = value_type()) {
			if (n < _size) {
				_destroy(n, _size);
			} else if (n > _size) {
				reserve(n);
				_construct(_size, n, val);
			}
			_size = n;	
		}

		void	pop_back() {_alloc.destroy(_start + --_size);}
		void	push_back(const value_type &val) {
			reserve(_size + ONE);
			_alloc.construct(_start + _size++, val);
		}

		void	swap(vector &x) {
			std::swap(_start, x._start);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
		}

		void	clear() {resize(ZERO);}
		
		void	assign(size_type n, const value_type &val) {
			clear();
			reserve(n);
			_construct(ZERO, _size = n, val);
		}

		template< class InputIterator >
		void assign(InputIterator first, InputIterator last,
			typename ENABLE_IF<NOT_INTEGRAL>::type* = NULL) {
			size_type new_size = std::distance(first, last);
			clear();
			reserve(new_size);
			_construct(ZERO, first, last);
			_size = new_size;
		}

		iterator	insert(iterator position, const value_type &val) {
			size_t pos_idx = std::distance(begin(), position);

			insert(position, ONE, val);
			return begin() + pos_idx;
		}

		void	insert(iterator position, size_type n, const value_type &val) {
			if (n == ZERO)
				return;
			size_t new_size = _size + n;
			size_t pos_idx = std::distance(begin(), position);

			reserve(new_size);
			_move(_start + pos_idx, end().base(), _start + new_size);
			_construct(pos_idx, pos_idx + n, val);
			_size = new_size;
		}

		template<class InputIterator>
		void 	insert(iterator position, InputIterator first,
				InputIterator last,
				typename ENABLE_IF<NOT_INTEGRAL>::type* = NULL) {

			if (first == last)
				return;
			size_t new_size = _size + std::distance(first, last);
			size_t pos_idx = std::distance(begin(), position);

			reserve(new_size);
			_move(_start + pos_idx, end().base(), _start + new_size);
			_construct(pos_idx, first, last);
			_size = new_size;
		}
		
		iterator	erase(iterator position) {
			if (position == end())
				return end();
			return erase(position, position + ONE);
		}

		iterator	erase(iterator first, iterator last) {
			if (first == last)
				return last;		
			size_type 	num_of_elem = std::distance(first, last);
			size_type 	pos_idx = std::distance(begin(), first);
			pointer		insert_point = _start + pos_idx;
	
			_destroy(pos_idx, pos_idx + num_of_elem);
			_move(insert_point + num_of_elem, end().base(), insert_point);
			_size -= num_of_elem;
			return iterator(insert_point);
		}
	
	private:
/* 		Utils_________________________________________________________________*/			
		void	_init(size_type size, allocator_type alloc) {
			_alloc = alloc;
			if ((_size = _capacity = size) == ZERO) {
				_start = NULL;
				return;
			}
			_check_max_size_exceeded(_size);
			_start = _alloc.allocate(_size);
		}

		void	_delete_all() {
			if (_capacity == ZERO)
				return;
			clear();
			_alloc.deallocate(_start, _capacity);
			_start = NULL;
			_capacity = ZERO;
		}

		void	_destroy(size_t start, size_t end) {
			for (size_t i = start; i < end; i++)
				_alloc.destroy(_start + i);
		}

		void	_construct(size_t start, size_t end, const value_type &val) {
			for (size_t i = start; i < end; i++)
				_alloc.construct(_start + i, val);
		}

		template<class InputIterator>
		void	_construct(size_t pos, InputIterator start, InputIterator end,
			typename ENABLE_IF<NOT_INTEGRAL>::type* = NULL) {
			std::uninitialized_copy(start, end, begin() + pos);
		}

		void	_move(pointer first, pointer last, pointer result) {
			result < first	? _copy(first, last, result) 
							: _copy_back(first, last, result);
		}

		void	_copy(pointer first, pointer last, pointer result) {
			size_type	idx = ZERO;
			while (first != last) {
				_alloc.construct(result + idx++, *first++);
				_alloc.destroy(first - ONE);
			}	
		}
		
		void	_copy_back(pointer first, pointer last,	pointer result) {
			size_type	idx = std::distance(first, last);
			for(size_t end = ONE; end <= idx; end++) {
				_alloc.construct(result - end, *(last - end));
				_alloc.destroy(last - end);
			}
		}

/* 		Errors________________________________________________________________*/
		void	_check_max_size_exceeded(size_type length) const {
			if (length > max_size())
				throw std::length_error("Error: Maximum size exceeded");
		}

		void	_check_arr_size_exceeded(size_type index) const {
			if (index >= _size)
				throw std::out_of_range("Error: Vector size exceeded");
		}
};

/*	Non-member function overloads_____________________________________________*/
template<class T, class Alloc>
bool	operator== (const VEC_TYPE &lhs, const VEC_TYPE &rhs) {
	return 	(lhs.size() == rhs.size()) &&
			(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class T, class Alloc>
bool	operator!= (const VEC_TYPE &lhs, const VEC_TYPE &rhs) {
	return !(lhs == rhs);
}

template<class T, class Alloc>
bool	operator< (const VEC_TYPE &lhs, const VEC_TYPE &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(),
										rhs.begin(), rhs.end());
}

template<class T, class Alloc>
bool	operator<= (const VEC_TYPE &lhs, const VEC_TYPE &rhs) {
	return !(rhs < lhs);
}

template<class T, class Alloc>
bool	operator> (const VEC_TYPE &lhs, const VEC_TYPE &rhs) {
	return rhs < lhs;
}

template<class T, class Alloc>
bool	operator>= (const VEC_TYPE &lhs, const VEC_TYPE &rhs) {
	return !(lhs < rhs);
}

template<class T, class Alloc>
void	swap(const VEC_TYPE &x, const VEC_TYPE &y) {x.swap(y);}

};

#endif