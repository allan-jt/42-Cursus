/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		rbt_node.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/15 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_NODE_HPP
#define RBT_NODE_HPP

#include <memory>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <utility>
#include <functional>

#define RED		0
#define BLACK	1

namespace ft {

template<class T> class RBTNode {
	public:
/* 		Types_________________________________________________________________*/
		typedef	T			value_type;
		typedef T*			pointer;
		typedef	const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef RBTNode<T>	Node;
		typedef Node*		node_ptr;
	
	private:
/*		Attributes____________________________________________________________*/	
		value_type	_value;
		int			_color;
		node_ptr	_parent;
		node_ptr	_left;
		node_ptr	_right;
		bool		_end;
	
	public:
/* 		Constructors, destructors, & assignment operator overload_____________*/	
		RBTNode(value_type value, int color = RED, node_ptr parent = NULL,
			node_ptr left = NULL, node_ptr right = NULL) 
			: _value(value), _color(color), _parent(parent),
			  _left(left), _right(right), _end(false) {}

		RBTNode(const RBTNode &copy) : _value(copy._value) {*this = copy;}

		RBTNode &operator= (const RBTNode &rhs) {
			if (this != &rhs) {
				_color = rhs._color;
				_parent = rhs._parent;
				_left = rhs._left;
				_right = rhs._right;
				_end = rhs._end;
			}
			return *this;
		}

/*		Characteristics_______________________________________________________*/
		bool	is_end()	{return _end;}
		bool	is_black()	{return _color == BLACK;}
		bool	is_red()	{return _color == RED;}
		
		bool	has_black_children() {
			return (!_right || _right->is_black()) 
				&& (!_left || _left->is_black());
		}

		bool	is_right_child() {
			return (_parent && _parent->get_right() == this);
		}

		bool	is_left_child()	{
			return (_parent && _parent->get_left() == this);
		}

/*		Getters_______________________________________________________________*/
		int				get_color()			{return _color;}
		reference		get_value() 		{return _value;}
		const_reference	get_value() const 	{return _value;}
		node_ptr		&get_parent()		{return _parent;}
		node_ptr		&get_left()			{return _left;}	
		node_ptr		&get_right()		{return _right;}

		node_ptr	get_sibling() {	
			return (is_right_child() ? _parent->get_left() 	:
					is_left_child()	 ? _parent->get_right() : NULL);
		}

		node_ptr	get_uncle() {
			return (_parent ? _parent->get_sibling() : NULL);
		}

		node_ptr	get_next_by_val() {
			if (_right)
				return _right->get_min_by_val();
			node_ptr temp = this;
			while (temp->_parent && temp != temp->_parent->_left)
				temp = temp->_parent;
			return temp->_parent;
		}
		
		node_ptr	get_prev_by_val() {
			if (_left)
				return _left->get_max_by_val();
			node_ptr temp = this;
			while (temp->_parent && temp != temp->_parent->_right)
				temp = temp->_parent;
			return temp->_parent;
		}

		node_ptr	get_max_by_val() {
			node_ptr current = this;
			while (current && current->_right 
				&& !current->_right->is_end())
				current = current->_right;
			return current;
		}

		node_ptr	get_min_by_val() {
			node_ptr current = this;
			while (current && current->_left
				&& !current->_left->is_end())
				current = current->_left;
			return current;
		}

/*		Setters_______________________________________________________________*/
		template<class allocator>
		void	set_value(value_type &value, allocator alloc) {
			int			tmp_color = _color;
			node_ptr	tmp_parent = _parent;
			node_ptr	tmp_left = _left;
			node_ptr	tmp_right = _right;
			bool		tmp_end = _end;
		
			alloc.destroy(this);
			alloc.construct(this, value);
			_color = tmp_color;
			_parent = tmp_parent;
			_left = tmp_left;
			_right = tmp_right;
			_end = tmp_end;	
		}
		
		void	set_parent(node_ptr parent)	{_parent = parent;}
		
		void	set_left(node_ptr left) {
			if ((_left = left) != NULL)
				left->_parent = this;
		}

		void	set_right(node_ptr right) {
			if ((_right = right) != NULL)
				right->_parent = this;
		}

		void	set_end(bool end)		{_end = end;}
		void	set_color(int color)	{_color = color;}
		void	recolor()				{_color = is_black() ? RED : BLACK;}
};

};

#endif