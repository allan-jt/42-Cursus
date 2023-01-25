/* ************************************************************************** */
/*																			  */
/*   Project:	ft_containers                             :::      ::::::::   */
/*   File:		rbt.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 by athekkep 		           #+#    #+#             */
/*   Updated: 2023/01/19 by athekkep                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
#define RBT_HPP

#include "rbt_node.hpp"
#include "../containers/vector.hpp"
#include "../iterators/rbt_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utilities/pair.hpp"

#define ZERO	0
#define ONE		1

#define	RBT_TYPE	RBT<value_type, key_compare, allocator_type>
#define RBT_ITER	ft::rbt_iterator
#define REV_ITER	ft::reverse_iterator

namespace ft {

template<class Value, class Compare, class Alloc> class RBT {
	public:
/* 		Types_________________________________________________________________*/
		typedef	Value			value_type;
		typedef Compare			key_compare;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;

		typedef RBTNode<Value>									Node;
		typedef Node*											pointer;
		typedef	const Node*										const_pointer;
		typedef Node&											reference;
		typedef const Node&										const_reference;
		typedef typename Alloc::template rebind<Node>::other	allocator_type;

		typedef typename RBT_ITER<Value, Node>			iterator;
		typedef REV_ITER<iterator>						reverse_iterator;
		typedef typename RBT_ITER<const Value, Node>	const_iterator;
		typedef REV_ITER<const_iterator>				const_reverse_iterator;
	
	private:
/* 		Attributes____________________________________________________________*/
		pointer			_root;
		pointer			_end_node;
		key_compare		_comp;
		allocator_type	_alloc;
		size_type		_size;

	public:
/* 		Constructors, destructors, & assignment operator overload_____________*/		
		explicit RBT(const key_compare &comp,
					 const allocator_type &alloc = allocator_type()) 
			: _comp(comp), _alloc(alloc), _size(ZERO) {_init_end_node();}

		RBT(const RBT &copy) : _comp(copy._comp), _alloc(allocator_type()) {
			_init_end_node();
			*this = copy;
		}

		RBT &operator=(const RBT &x) {
			if (this != &x) {
				clear();
				_size = x._size;
				_copy_nodes(x._root, _root);
				_adjust_end_node();
			}
			return *this;
		}

		~RBT() {
			clear();
			_delete_node(_end_node);
		}

/* 		Iterators_____________________________________________________________*/
		iterator		begin() {return iterator(_root->get_min_by_val());}
		const_iterator	begin() const {
			return const_iterator(_root->get_min_by_val());
		}

		iterator		end() 		{return iterator(_end_node);}
		const_iterator	end() const	{return const_iterator(_end_node);}

		reverse_iterator		rbegin() {return reverse_iterator(end());}
		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator		rend() {return reverse_iterator(begin());}
		const_reverse_iterator	rend() const {
			return const_reverse_iterator(begin());
		}

/* 		Capacity______________________________________________________________*/
		bool		empty() const		{return _size == ZERO;}
		size_type	size() const		{return _size;}
		size_type	max_size() const	{return _alloc.max_size();}

/* 		Modifiers_____________________________________________________________*/
		void clear() {
			_delete_all_nodes(_root);
			_root = _end_node;
			_size = ZERO;
		}

		void	erase(iterator position) {_delete(position.base());}
		void	erase(iterator first, iterator last) {
			ft::vector<typename iterator::value_type> values(first, last);
			for (size_t i = ZERO; i < values.size(); i++)
				_delete_val(values[i]);
		}
	
		iterator insert(iterator position, const value_type& val) {
			pointer	pos_node = position.base();
			pointer parent = pos_node->get_parent();

			bool belongs_left = parent && _comp(val, parent->get_value()) 
				&& pos_node->is_left_child();
			bool belongs_right = parent && _comp(parent->get_value(), val) 
				&& pos_node->is_right_child();
			
			if (!is_end(pos_node) && (belongs_left || belongs_right))
				return iterator(_insert_value(val, pos_node).first);
			return iterator(_insert_value(val, _root).first);
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last) { 
			while (first != last)
				_insert_value(*first++, _root);
		}

		ft::pair<iterator, bool>	insert(const value_type& val) {
			ft::pair<pointer, bool> ret = _insert_value(val, _root);
			return ft::pair<iterator, bool>(iterator(ret.first), ret.second);
		}

		void	swap(RBT &rbt) {
			std::swap(_root, rbt._root);
			std::swap(_end_node, rbt._end_node);
			std::swap(_size, rbt._size);
		}

/* 		Operations____________________________________________________________*/
		iterator	find(const value_type &val) {
			pointer temp = get_node(val, _root);
			return (temp ? iterator(temp) : end());
		}

		const_iterator	find(const value_type &val) const {
			pointer temp = get_node(val, _root);
			return (temp ? const_iterator(temp) : end());
		}

		size_type	count(const value_type &val) const {
			return (get_node(val, _root) ? ONE : ZERO);
		}

		iterator	lower_bound(const value_type &val) {
			return iterator(_get_closest_val(val));
		}

		const_iterator	lower_bound(const value_type &val) const {
			return const_iterator(_get_closest_val(val));
		}

		iterator	upper_bound(const value_type &val) {
			pointer closest = _get_closest_val(val);
			
			if (_values_equal(val, closest->get_value()))
				return ++iterator(closest);
			return iterator(closest);
		}

		const_iterator	upper_bound(const value_type &val) const {
			pointer closest = _get_closest_val(val);
				
			if (_values_equal(val, closest->get_value()))
				return ++const_iterator(closest);
			return const_iterator(closest);
		}

/* 		Others________________________________________________________________*/		
		value_type	&get_value(const value_type &val) {
			pointer	node = get_node(val, _root);

			_check_valid_node(node);
			return node->get_value();
		}

		pointer	get_node(const value_type &val, pointer start) const {
			pointer cur = start ? start : _root;

			while (!is_end(cur) && !_values_equal(val, cur->get_value())) {
				cur = _comp(val, cur->get_value()) ? 
					cur->get_left() : cur->get_right();
			}
			return (!is_end(cur) && _values_equal(val, cur->get_value()) ? 
						cur : NULL);
		}
		
		bool	delete_value(value_type val) {
			return _delete_val(val);
		}

		bool	is_equal(const RBT &x) const {
			if (_size != x._size)
				return false;
			return _are_nodes_equal(_root, x._root);
		}

	private:
/* 		Insertion_____________________________________________________________*/
		ft::pair<pointer, bool>	_insert_value(const value_type& val, 
			pointer place) {
			
			pointer parent = NULL;
			while (!is_end(place)) {
				parent = place;
				if (_comp(val, place->get_value())) { 
					place = place->get_left();
				} else if (_comp(place->get_value(), val)) {
					place = place->get_right();
				} else
					return ft::make_pair(place, false);
			}
			return ft::make_pair(_insert_val_at(val, parent), true);
		}

		pointer	_insert_val_at(const value_type& val, pointer parent) {
			_check_max_size_exceeded();
			pointer new_node = _create_node(val);
			_size++;

			if (!parent)
				_root = new_node;
			else if (_comp(val, parent->get_value()))
				parent->set_left(new_node);
			else
				parent->set_right(new_node);

			_balance(new_node, parent);
			_adjust_end_node(new_node);
			return new_node;
		}

		void	_balance(pointer node, pointer parent) {		
			pointer uncle, grandfather;
			while (is_red(parent)) {
				uncle = node->get_uncle();
				if (is_black(uncle))
					return _rotate(node);

				grandfather = parent->get_parent();
				parent->set_color(BLACK);
				uncle->set_color(BLACK);
				if (_root != grandfather)
					grandfather->set_color(RED);
				node = grandfather;
				parent = grandfather->get_parent();
			}
			_root->set_color(BLACK);
		}

/* 		Deletion______________________________________________________________*/
//		medium.com/analytics-vidhya/deletion-in-red-black-rb-tree-92301e1474ea

		bool _delete_val(const value_type& val) {
			pointer node_to_delete = get_node(val, NULL);
			if (node_to_delete) {
				_delete(node_to_delete);
				return true;
			}
			return false;
		}

		void	_delete(pointer to_delete) {
			pointer replacement = !is_end(to_delete->get_right()) ? 
				to_delete->get_right()->get_min_by_val() : to_delete;
					
			_size--;
			_swap_node_position(replacement, to_delete);
			if (replacement->is_red() || replacement == _root) {
				_remove_node(replacement);
				_root->set_color(BLACK);
				return _adjust_end_node();
			}
		
			replacement->set_end(true);
			pointer double_black = replacement;
			while (double_black) {
				if (case_one(double_black)) {
					exec_case_one(double_black);
				} else if (case_two(double_black)) {
					exec_case_two(double_black);
				} else if (case_six(double_black)) {
					exec_case_six(double_black);
				} else if (case_four(double_black)) {
					exec_case_four(double_black);
				} else if (case_five(double_black)) {
					exec_case_five(double_black);
				} else if (case_three(double_black)) {
					exec_case_three(double_black);
				}
			}
			_root->set_color(BLACK);
			_adjust_end_node();
		}

		void	_remove_node(pointer &node) {
			pointer left_child = node->get_left();
			pointer right_child = node->get_right();
			
			if (left_child)
				_transplant(node, left_child);
			else
				_transplant(node, right_child);
			_delete_node(node);
		}

	//	Case 1: Node is red leaf node___________________________________________	
		bool	case_one(pointer double_black) {
			return (double_black->is_red() 
				&& is_end(double_black->get_left())
				&& is_end(double_black->get_right()));
		}

		void	exec_case_one(pointer &double_black) {
			if (double_black->is_end())
				_remove_node(double_black);
		}

	//	Case 2: Node is root____________________________________________________
		bool	case_two(pointer double_black) {return (double_black == _root);}

		void	exec_case_two(pointer &double_black) { 
			_root->set_color(BLACK);
			if (double_black->is_end())
				_remove_node(double_black);
			double_black = NULL;
		}

	//	Case 3: Sibling black, sibling's children black_________________________
		bool	case_three(pointer double_black) {
			pointer	sibling = double_black->get_sibling();
			return (sibling->is_black() && sibling->has_black_children());	
		}

		void	exec_case_three(pointer &double_black) {
			pointer parent = double_black->get_parent();

			double_black->get_sibling()->set_color(RED);
			if (double_black->is_end()) {
				_remove_node(double_black);
				double_black = NULL;
			}
				
			if (parent->is_red()) {
				double_black = NULL;
				return parent->set_color(BLACK);
			}	
			double_black = parent;
		}

	//	Case 4: Node's sibling is red___________________________________________
		bool	case_four(pointer double_black) {
			return (is_red(double_black->get_sibling()));
		}

		void	exec_case_four(pointer &double_black) {
			pointer	parent = double_black->get_parent();
			pointer	sibling = double_black->get_sibling();
			int 	sib_color = sibling->get_color();

			sibling->set_color(parent->get_color());
			parent->set_color(sib_color);
			double_black->is_left_child() ? _left_rotate(parent) : 
											_right_rotate(parent);
		}

	//	Case 5: Sibling black, sibling far child black, sibling near child red__
		bool	case_five(pointer double_black) {
			pointer sibling = double_black->get_sibling();
			pointer near_child, far_child;

			if (!sibling)
				return false;
			if (double_black->is_left_child()) {
				near_child = sibling->get_left();
				far_child = sibling->get_right();
			} else {
				near_child = sibling->get_right();
				far_child = sibling->get_left();
			}

			return (sibling->is_black() && is_black(far_child)
										&& is_red(near_child));
		}

		void	exec_case_five(pointer &double_black) {
			pointer sibling = double_black->get_sibling();
			pointer near_child = double_black->is_left_child() ?
				sibling->get_left() : sibling->get_right();
			
			near_child->set_color(sibling->get_color());
			sibling->set_color(RED);
			double_black->is_right_child() ? _left_rotate(sibling) : 
											 _right_rotate(sibling);
			exec_case_six(double_black);
		}

	//	Case 6: Sibling black, sibling far child red____________________________
		bool	case_six(pointer double_black) {
			pointer sibling = double_black->get_sibling();
			if (!sibling)
				return false;
			pointer far_child = double_black->is_left_child() ?
				sibling->get_right() : sibling->get_left();
			return (sibling->is_black() && is_red(far_child));
		}
		
		void	exec_case_six(pointer &double_black) {
			pointer	parent = double_black->get_parent();
			pointer	sibling = double_black->get_sibling();
			int 	sib_color = sibling->get_color();
			pointer sib_far_child = double_black->is_left_child() ?
				sibling->get_right() : sibling->get_left();
	
			sibling->set_color(parent->get_color());
			parent->set_color(sib_color);
			double_black->is_left_child() ? _left_rotate(parent) : 
											_right_rotate(parent);
			double_black->set_color(BLACK);
			sib_far_child->set_color(BLACK);
			if (double_black->is_end())
				_remove_node(double_black);
			double_black = NULL;
		}

/* 		Rotations_____________________________________________________________*/
		void	_rotate(pointer &node) { // node is rotation point's grandchild
			pointer parent = node->get_parent();
			pointer grandparent = parent->get_parent();

			if (_is_upward_slope(node, parent, grandparent)) {
				_right_rotate(grandparent);
				parent->recolor();
				grandparent->recolor();
			} else if (_is_down_slope(node, parent, grandparent)) {
				_left_rotate(grandparent);
				parent->recolor();
				grandparent->recolor();
			} else if (_is_right_arrow(node, parent, grandparent)) {
				_double_right_left_rotate(grandparent);
				node->recolor();
				grandparent->recolor();
			} else if (_is_left_arrow(node, parent, grandparent)) {
				_double_left_right_rotate(grandparent);
				node->recolor();
				grandparent->recolor();
			}
			_root->set_color(BLACK);	// In case rotations made _root red
		}
		
		void	_left_rotate(pointer &node) {
			pointer grandparent = node;
			pointer parent = node->get_right();
			pointer left_child = parent ? parent->get_left() : NULL;

		//	Link the three key nodes: grandparent, parent & left child
			_transplant(grandparent, parent);
			parent->set_left(grandparent);
			grandparent->set_right(left_child);
		}

		void	_right_rotate(pointer &node) {
			pointer grandparent = node;
			pointer parent = node->get_left();
			pointer right_child = parent ? parent->get_right() : NULL;

		//	Link the three key nodes: grandparent, parent & right child
			_transplant(grandparent, parent);
			parent->set_right(grandparent);
			grandparent->set_left(right_child);	
		}

		void	_double_left_right_rotate(pointer &node) {
			_left_rotate(node->get_left());
			_right_rotate(node);
		}

		void	_double_right_left_rotate(pointer &node) {
			_right_rotate(node->get_right());
			_left_rotate(node);
		}

		bool	_is_upward_slope(pointer node1, pointer node2, pointer node3) {
		//	Testing for '/' shape
			return (node1 == node2->get_left() && node2 == node3->get_left());
		}

		bool	_is_down_slope(pointer node1, pointer node2, pointer node3) {
		//	Testing for '\' shape
			return (node1 == node2->get_right() && node2 == node3->get_right());
		}

		bool	_is_right_arrow(pointer node1, pointer node2, pointer node3) {
		//	Testing for '>' shape
			return (node1 == node2->get_left() && node2 == node3->get_right());
		}

		bool	_is_left_arrow(pointer node1, pointer node2, pointer node3) {
		//	Testing for '<' shape
			return (node1 == node2->get_right() && node2 == node3->get_left());
		}

/* 		Errors________________________________________________________________*/
		void	_check_max_size_exceeded() const {
			if (_size >= max_size())
				throw std::length_error("Error: Maximum size exceeded");
		}

		void	_check_valid_node(pointer node) const {
			if (is_end(node))
				throw std::out_of_range("Error: No such key exists");
		}

/* 		Comparisons___________________________________________________________*/
		bool _values_equal(const value_type &lhs, const value_type &rhs) const {
			return (!_comp(lhs, rhs) && !_comp(rhs, lhs));
		}

		bool	_are_nodes_equal(pointer node1, pointer node2) const {
			if (is_end(node1) && is_end(node2))
				return true;
			if (is_end(node1) || is_end(node2))
				return false;
			return _values_equal(node1->get_value(), node2->get_value())
				&& _are_nodes_equal(node1->get_left(), node2->get_left())
				&& _are_nodes_equal(node1->get_right(), node2->get_right());
		}

/* 		Swapper_______________________________________________________________*/
		void	_transplant(pointer &replace, pointer replacement) {				
			if (replace->is_right_child())
				return replace->get_parent()->set_right(replacement);
			else if (replace->is_left_child())
				return replace->get_parent()->set_left(replacement);
		//	If replace is root:
			_root = replacement;
			if (replacement)
				replacement->set_parent(NULL);
		}
		
		void	_replace_parent_child(pointer p, pointer c, pointer replace) {
			if (p == NULL) {
				_root = replace;
				return replace->set_parent(NULL);
			}
			p->get_left() == c ? p->set_left(replace) : p->set_right(replace);
		}

		void	_parental_swap(pointer node1, pointer node2) {
			pointer parent1 = node1->get_parent();
			pointer left1 = node1->get_left();
			pointer right1 = node1->get_right();
			int		color1 = node1->get_color();

			pointer parent2 = node2->get_parent();
			pointer left2 = node2->get_left();
			pointer right2 = node2->get_right();
			int		color2 = node2->get_color();

			if (parent1 == node2) {
				_replace_parent_child(parent2, node2, node1);
				node2->set_left(left1);
				node2->set_right(right1);
				if (right2 == node1) {
					node1->set_left(left2);
					node1->set_right(node2);
				} else {
					node1->set_left(node2);
					node1->set_right(right2);
				}
			} else {
				_replace_parent_child(parent1, node1, node2);
				node1->set_left(left2);
				node1->set_right(right2);
				if (right1 == node2) {
					node2->set_left(left1);
					node2->set_right(node1);
				} else {
					node2->set_left(node1);
					node2->set_right(right1);
				}
			}

			node1->set_color(color2);
			node2->set_color(color1);
		}

		void	_non_parent_swap(pointer node1, pointer node2) {
			pointer parent1 = node1->get_parent();
			pointer left1 = node1->get_left();
			pointer right1 = node1->get_right();
			int		color1 = node1->get_color();

			pointer parent2 = node2->get_parent();
			pointer left2 = node2->get_left();
			pointer right2 = node2->get_right();
			int		color2 = node2->get_color();

			_replace_parent_child(parent1, node1, node2);
			_replace_parent_child(parent2, node2, node1);
			node1->set_right(right2);
			node1->set_left(left2);
			node2->set_right(right1);
			node2->set_left(left1);
			node1->set_color(color2);
			node2->set_color(color1);
		}

		void	_swap_node_position(pointer &node1, pointer &node2) {
			if (node1 == node2 || !_root)
				return;			
			if (node1->get_parent() == node2 || node2->get_parent() == node1)
				_parental_swap(node1, node2);
			else
				_non_parent_swap(node1, node2);
			std::swap(node1, node2);
		}

/* 		Utils_________________________________________________________________*/	
		pointer	_create_node(const value_type &val = value_type()) {
			pointer new_node = _alloc.allocate(ONE);
			_alloc.construct(new_node, val);
			return new_node;
		}

		void	_init_end_node() {
			_end_node = _create_node();
			_end_node->set_end(true);
			_end_node->set_color(BLACK);
			_root = _end_node;
		}
		
		void	_delete_node(pointer &node) {
			if (!node)
				return;
			if (_end_node->get_parent() == node)
				_end_node->set_parent(NULL);
			_alloc.destroy(node);
			_alloc.deallocate(node, ONE);
			node = NULL;
		}

		void	_delete_all_nodes(pointer &node) {
			if (is_end(node))
				return;
			_delete_all_nodes(node->get_left());
			_delete_all_nodes(node->get_right());
			_delete_node(node);
		}

		void	_copy_nodes(pointer to_copy, pointer &copy) {
			if (is_end(to_copy))
				return;
			copy = _create_node(to_copy->get_value());
			_copy_nodes(to_copy->get_left(), copy->get_left());
			_copy_nodes(to_copy->get_right(), copy->get_right());

			copy->set_color(to_copy->get_color());
			if (copy->get_left())
				copy->get_left()->set_parent(copy);
			if (copy->get_right())
				copy->get_right()->set_parent(copy);
		}

		void	_adjust_end_node() {	// During deletion
			if (!_end_node->get_parent())
				_root->get_max_by_val()->set_right(_end_node);
		}

		void	_adjust_end_node(pointer new_node) {	// During insertion
			pointer old_max = _end_node->get_parent();

			if (old_max && _comp(new_node->get_value(), old_max->get_value()))
				return;
			if (old_max && old_max->get_right() == _end_node)
				old_max->set_right(NULL);
			if (old_max && old_max->get_left() == _end_node)
				old_max->set_left(NULL);
			new_node->set_right(_end_node);
		}

		pointer	_get_closest_val(const value_type &val) const {
			pointer cur = _root, closest = _root;

			while (!is_end(cur)) {	
				value_type cur_val = cur->get_value();
				if (_comp(cur_val, val)) {
					cur = cur->get_right();
				} else if (_comp(val, cur_val)) {
					closest = cur;
					cur = cur->get_left();
				} else {
					closest = cur;
					break;
				}
			}
			return (_comp(closest->get_value(), val) ? _end_node : closest);
		}

		bool	is_end(pointer node) const {return (!node || node->is_end());}
		bool	is_red(pointer node) {return !is_black(node);}
		bool	is_black(pointer node)  {
			return is_end(node) || node->is_black();
		}
};

};

#endif