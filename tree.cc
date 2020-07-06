// RB tree utilities implementation -*- C++ -*-

// Copyright (C) 2003-2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.	This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.	If not, see
// <http://www.gnu.org/licenses/>.

/*
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.	Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.	It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.	Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.	It is provided "as is" without express or implied warranty.
 *
 *
 */

#ifndef TREE_CC
# define TREE_CC
# include "binary_tree.hpp"

namespace ft
{

	static _bin_tree_node_base*
	local_bin_tree_increment(_bin_tree_node_base* x) throw ()
	{
		if (x->_M_right != 0)
			{
				x = x->_M_right;
				while (x->_M_left != 0)
					x = x->_M_left;
			}
		else
			{
				_bin_tree_node_base* y = x->_M_parent;
				while (x == y->_M_right)
					{
						x = y;
						y = y->_M_parent;
					}
				if (x->_M_right != y)
					x = y;
			}
		return x;
	}

	_bin_tree_node_base*
	_bin_tree_increment(_bin_tree_node_base* x) throw ()
	{
		return local_bin_tree_increment(x);
	}

	const _bin_tree_node_base*
	_bin_tree_increment(const _bin_tree_node_base* x) throw ()
	{
		return local_bin_tree_increment(const_cast<_bin_tree_node_base*>(x));
	}

	static _bin_tree_node_base*
	local_bin_tree_decrement(_bin_tree_node_base* x) throw ()
	{
		if (x->_M_color == _S_red
				&& x->_M_parent->_M_parent == x)
			x = x->_M_right;
		else if (x->_M_left != 0)
			{
				_bin_tree_node_base* y = x->_M_left;
				while (y->_M_right != 0)
					y = y->_M_right;
				x = y;
			}
		else
			{
				_bin_tree_node_base* y = x->_M_parent;
				while (x == y->_M_left)
					{
						x = y;
						y = y->_M_parent;
					}
				x = y;
			}
		return x;
	}

	_bin_tree_node_base*
	_bin_tree_decrement(_bin_tree_node_base* x) throw ()
	{
		return local_bin_tree_decrement(x);
	}

	const _bin_tree_node_base*
	_bin_tree_decrement(const _bin_tree_node_base* x) throw ()
	{
		return local_bin_tree_decrement(const_cast<_bin_tree_node_base*>(x));
	}

	static void
	local_bin_tree_rotate_left(_bin_tree_node_base* const x,
								 _bin_tree_node_base*& root)
	{
		_bin_tree_node_base* const y = x->_M_right;

		x->_M_right = y->_M_left;
		if (y->_M_left !=0)
			y->_M_left->_M_parent = x;
		y->_M_parent = x->_M_parent;

		if (x == root)
			root = y;
		else if (x == x->_M_parent->_M_left)
			x->_M_parent->_M_left = y;
		else
			x->_M_parent->_M_right = y;
		y->_M_left = x;
		x->_M_parent = y;
	}

#if !_GLIBCXX_INLINE_VERSION
	/* Static keyword was missing on _bin_tree_rotate_left.
		 Export the symbol for backward compatibility until
		 next ABI change.	*/
	void
	_bin_tree_rotate_left(_bin_tree_node_base* const x,
					 _bin_tree_node_base*& root)
	{ local_bin_tree_rotate_left (x, root); }
#endif

	static void
	local_bin_tree_rotate_right(_bin_tree_node_base* const x,
					 _bin_tree_node_base*& root)
	{
		_bin_tree_node_base* const y = x->_M_left;

		x->_M_left = y->_M_right;
		if (y->_M_right != 0)
			y->_M_right->_M_parent = x;
		y->_M_parent = x->_M_parent;

		if (x == root)
			root = y;
		else if (x == x->_M_parent->_M_right)
			x->_M_parent->_M_right = y;
		else
			x->_M_parent->_M_left = y;
		y->_M_right = x;
		x->_M_parent = y;
	}

#if !_GLIBCXX_INLINE_VERSION
	/* Static keyword was missing on _bin_tree_rotate_right
		 Export the symbol for backward compatibility until
		 next ABI change.	*/
	void
	_bin_tree_rotate_right(_bin_tree_node_base* const x,
			_bin_tree_node_base*& root)
	{ local_bin_tree_rotate_right (x, root); }
#endif

	void
	_bin_tree_insert_and_rebalance(const bool					insert_left,
																_bin_tree_node_base* x,
																_bin_tree_node_base* p,
																_bin_tree_node_base& header) throw ()
	{
		_bin_tree_node_base *& root = header._M_parent;

		// Initialize fields in new node to insert.
		x->_M_parent = p;
		x->_M_left = 0;
		x->_M_right = 0;
		x->_M_color = _S_red;

		// Insert.
		// Make new node child of parent and maintain root, leftmost and
		// rightmost nodes.
		// N.B. First node is always inserted left.
		if (insert_left)
			{
				p->_M_left = x; // also makes leftmost = x when p == &header

				if (p == &header)
				{
						header._M_parent = x;
						header._M_right = x;
				}
				else if (p == header._M_left)
					header._M_left = x; // maintain leftmost pointing to min node
			}
		else
			{
				p->_M_right = x;

				if (p == header._M_right)
					header._M_right = x; // maintain rightmost pointing to max node
			}
		// Rebalance.
		while (x != root
		 && x->_M_parent->_M_color == _S_red)
			{
	_bin_tree_node_base* const xpp = x->_M_parent->_M_parent;

	if (x->_M_parent == xpp->_M_left)
		{
			_bin_tree_node_base* const y = xpp->_M_right;
			if (y && y->_M_color == _S_red)
				{
		x->_M_parent->_M_color = _S_black;
		y->_M_color = _S_black;
		xpp->_M_color = _S_red;
		x = xpp;
				}
			else
				{
		if (x == x->_M_parent->_M_right)
			{
				x = x->_M_parent;
				local_bin_tree_rotate_left(x, root);
			}
		x->_M_parent->_M_color = _S_black;
		xpp->_M_color = _S_red;
		local_bin_tree_rotate_right(xpp, root);
				}
		}
	else
		{
			_bin_tree_node_base* const y = xpp->_M_left;
			if (y && y->_M_color == _S_red)
				{
		x->_M_parent->_M_color = _S_black;
		y->_M_color = _S_black;
		xpp->_M_color = _S_red;
		x = xpp;
				}
			else
				{
		if (x == x->_M_parent->_M_left)
			{
				x = x->_M_parent;
				local_bin_tree_rotate_right(x, root);
			}
		x->_M_parent->_M_color = _S_black;
		xpp->_M_color = _S_red;
		local_bin_tree_rotate_left(xpp, root);
				}
		}
			}
		root->_M_color = _S_black;
	}

	_bin_tree_node_base*
	_bin_tree_rebalance_for_erase(_bin_tree_node_base* const z,
						 _bin_tree_node_base& header) throw ()
	{
		_bin_tree_node_base *& root = header._M_parent;
		_bin_tree_node_base *& leftmost = header._M_left;
		_bin_tree_node_base *& rightmost = header._M_right;
		_bin_tree_node_base* y = z;
		_bin_tree_node_base* x = 0;
		_bin_tree_node_base* x_parent = 0;

		if (y->_M_left == 0)		 // z has at most one non-null child. y == z.
			x = y->_M_right;		 // x might be null.
		else
			if (y->_M_right == 0)	// z has exactly one non-null child. y == z.
	x = y->_M_left;		// x is not null.
			else
	{
		// z has two non-null children.	Set y to
		y = y->_M_right;	 //	 z's successor.	x might be null.
		while (y->_M_left != 0)
			y = y->_M_left;
		x = y->_M_right;
	}
		if (y != z)
			{
	// relink y in place of z.	y is z's successor
	z->_M_left->_M_parent = y;
	y->_M_left = z->_M_left;
	if (y != z->_M_right)
		{
			x_parent = y->_M_parent;
			if (x) x->_M_parent = y->_M_parent;
			y->_M_parent->_M_left = x;	 // y must be a child of _M_left
			y->_M_right = z->_M_right;
			z->_M_right->_M_parent = y;
		}
	else
		x_parent = y;
	if (root == z)
		root = y;
	else if (z->_M_parent->_M_left == z)
		z->_M_parent->_M_left = y;
	else
		z->_M_parent->_M_right = y;
	y->_M_parent = z->_M_parent;
	std::swap(y->_M_color, z->_M_color);
	y = z;
	// y now points to node to be actually deleted
			}
		else
			{												// y == z
	x_parent = y->_M_parent;
	if (x)
		x->_M_parent = y->_M_parent;
	if (root == z)
		root = x;
	else
		if (z->_M_parent->_M_left == z)
			z->_M_parent->_M_left = x;
		else
			z->_M_parent->_M_right = x;
	if (leftmost == z)
		{
			if (z->_M_right == 0)				// z->_M_left must be null also
				leftmost = z->_M_parent;
			// makes leftmost == _M_header if z == root
			else
				leftmost = _bin_tree_node_base::_S_minimum(x);
		}
	if (rightmost == z)
		{
			if (z->_M_left == 0)				 // z->_M_right must be null also
				rightmost = z->_M_parent;
			// makes rightmost == _M_header if z == root
			else											// x == z->_M_left
				rightmost = _bin_tree_node_base::_S_maximum(x);
		}
			}
		if (y->_M_color != _S_red)
			{
	while (x != root && (x == 0 || x->_M_color == _S_black))
		if (x == x_parent->_M_left)
			{
				_bin_tree_node_base* w = x_parent->_M_right;
				if (w->_M_color == _S_red)
		{
			w->_M_color = _S_black;
			x_parent->_M_color = _S_red;
			local_bin_tree_rotate_left(x_parent, root);
			w = x_parent->_M_right;
		}
				if ((w->_M_left == 0 ||
			 w->_M_left->_M_color == _S_black) &&
			(w->_M_right == 0 ||
			 w->_M_right->_M_color == _S_black))
		{
			w->_M_color = _S_red;
			x = x_parent;
			x_parent = x_parent->_M_parent;
		}
				else
		{
			if (w->_M_right == 0
					|| w->_M_right->_M_color == _S_black)
				{
					w->_M_left->_M_color = _S_black;
					w->_M_color = _S_red;
					local_bin_tree_rotate_right(w, root);
					w = x_parent->_M_right;
				}
			w->_M_color = x_parent->_M_color;
			x_parent->_M_color = _S_black;
			if (w->_M_right)
				w->_M_right->_M_color = _S_black;
			local_bin_tree_rotate_left(x_parent, root);
			break;
		}
			}
		else
			{
				// same as above, with _M_right <-> _M_left.
				_bin_tree_node_base* w = x_parent->_M_left;
				if (w->_M_color == _S_red)
		{
			w->_M_color = _S_black;
			x_parent->_M_color = _S_red;
			local_bin_tree_rotate_right(x_parent, root);
			w = x_parent->_M_left;
		}
				if ((w->_M_right == 0 ||
			 w->_M_right->_M_color == _S_black) &&
			(w->_M_left == 0 ||
			 w->_M_left->_M_color == _S_black))
		{
			w->_M_color = _S_red;
			x = x_parent;
			x_parent = x_parent->_M_parent;
		}
				else
		{
			if (w->_M_left == 0 || w->_M_left->_M_color == _S_black)
				{
					w->_M_right->_M_color = _S_black;
					w->_M_color = _S_red;
					local_bin_tree_rotate_left(w, root);
					w = x_parent->_M_left;
				}
			w->_M_color = x_parent->_M_color;
			x_parent->_M_color = _S_black;
			if (w->_M_left)
				w->_M_left->_M_color = _S_black;
			local_bin_tree_rotate_right(x_parent, root);
			break;
		}
			}
	if (x) x->_M_color = _S_black;
			}
		return y;
	}

	unsigned int
	_bin_tree_black_count(const _bin_tree_node_base* node,
											 const _bin_tree_node_base* root) throw ()
	{
		if (node == 0)
			return 0;
		unsigned int sum = 0;
		do
			{
	if (node->_M_color == _S_black)
		++sum;
	if (node == root)
		break;
	node = node->_M_parent;
			}
		while (1);
		return sum;
	}

} // namespace

#endif
