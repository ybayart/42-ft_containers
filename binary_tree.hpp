
#include "utils.hpp"

namespace ft
{
	struct _bin_tree_node_base
	{
		typedef _bin_tree_node_base*		_base_ptr;
		typedef const _bin_tree_node_base*	_const_base_ptr;

		_base_ptr	_M_parent;
		_base_ptr	_M_left;
		_base_ptr	_M_right;

		static _base_ptr
		_S_min(_base_ptr x)
		{
			while (x->_M_left != NULL)
				x = x->_M_left;
			return (x);
		}

		static _const_base_ptr
		_S_min(_const_base_ptr x)
		{
			while (x->_M_left != NULL)
				x = x->_M_left;
			return (x);
		}

		static _base_ptr
		_S_max(_base_ptr x)
		{
			while (x->_M_right != NULL)
				x = x->_M_right;
			return (x);
		}

		static _const_base_ptr
		_S_max(_const_base_ptr x)
		{
			while (x->_M_right != NULL)
				x = x->_M_right;
			return (x);
		}
	};

	template <typename T>
	struct _bin_tree_node : public _bin_tree_node_base
	{
		typedef _bin_tree_node<T>*	_link_type;

		T	_M_value_field;

		T*
		_M_valptr (void)
		{
			return (&(_M_value_field));
		}

		const T*
		_M_valptr (void) const
		{
			return (&(_M_value_field));
		}
	};

	template <typename T>
	struct _bin_tree_iterator
	{
		typedef T	value_type;
		typedef T&	reference;
		typedef T*	pointer;

		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t						difference_type;

		typedef _bin_tree_iterator<T>			_self;
		typedef _bin_tree_node_base::_base_ptr	_base_ptr;
		typedef _bin_tree_node<T>*				_link_type;

		_bin_tree_iterator (void)
		: _M_node()
		{}

		explicit
		_bin_tree_iterator(_base_ptr x)
		: _M_node(x)
		{}

		reference
		operator*	(void) const
		{
			return (*(static_cast<_link_type>(_M_node)->_M_valptr()));
		}

		pointer
		operator->	(void) const
		{
			return (static_cast<_link_type> (_M_node)->_M_valptr());
		}

		_self&
		operator++	(void)
		{
			_M_node = _bin_tree_increment(_M_node);
			return (*this);
		}

		_self
		operator++	(int)
		{
			_self tmp = *this;
			_M_node = _bin_tree_increment(_M_node);
			return (tmp);
		}

		_self&
		operator--	(void)
		{
			_M_node = _bin_tree_decrement(_M_node);
			return (*this);
		}

		_self
		operator--	(int)
		{
			_self tmp = *this;
			_M_node = _bin_tree_decrement(_M_node);
			return (tmp);
		}

		bool
		operator==	(const _self& x) const
		{
			return (_M_node == x._M_node);
		}

		bool
		operator!=	(const _self& x) const
		{
			return (_M_node != x._M_node);
		}

		_base_ptr	_M_node;
	};

	template<typename T>
	struct _bin_tree_const_iterator
	{
		typedef T			value_type;
		typedef const T&	reference;
		typedef const T*	pointer;

		typedef _bin_tree_iterator<T>	iterator;

		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t						difference_type;

		typedef _bin_tree_const_iterator<T>				_self;
		typedef _bin_tree_node_base::_const_base_ptr	_base_ptr;
		typedef const _bin_tree_node<T>*				_link_type;

		_bin_tree_const_iterator (void)
		: _M_node()
		{}

		explicit
		_bin_tree_const_iterator(_base_ptr x)
		: _M_node(x)
		{}

		_bin_tree_const_iterator(const iterator& it)
		: _M_node(it._M_node)
		{}

		iterator
		_M_const_cast (void) const
		{
			return (iterator(const_cast<typename iterator::_base_ptr>(_M_node)));
		}

		reference
		operator*	(void) const
		{
			return (*(static_cast<_link_type>(_M_node)->_M_valptr())); }

		pointer
		operator->	(void) const
		{
			return (static_cast<_link_type>(_M_node)->_M_valptr());
		}

		_self&
		operator++	(void)
		{
			_M_node = _bin_tree_increment(_M_node);
			return (*this);
		}

		_self
		operator++	(int)
		{
			_self tmp = *this;
			_M_node = _bin_tree_increment(_M_node);
			return (tmp);
		}

		_self&
		operator--	(void)
		{
			_M_node = _bin_tree_decrement(_M_node);
			return (*this);
		}

		_self
		operator--	(int)
		{
			_self tmp = *this;
			_M_node = _bin_tree_decrement(_M_node);
			return (tmp);
		}

		bool
		operator==	(const _self& x) const
		{
			return (_M_node == x._M_node);
		}

		bool
		operator!=	(const _self& x) const
		{
			return (_M_node != x._M_node);
		}

		_base_ptr	_M_node;
	};

	template<typename Val>
	inline bool
	operator==	(const _bin_tree_iterator<Val>& x,
				const _bin_tree_const_iterator<Val>& y)
	{
		return (x._M_node == y._M_node);
	}

	template<typename Val>
	inline bool
	operator!=	(const _bin_tree_iterator<Val>& x,
				const _bin_tree_const_iterator<Val>& y)
	{
		return (x._M_node != y._M_node);
	}

	template
	<
		typename Key,
		typename T,
		typename KeyOfValue,
		typename Compare,
		typename Alloc = std::allocator<T> >
	class _bin_tree
	{
		typedef typename Alloc::template
			rebind<T>::other					_node_allocator;
		typedef _node_allocator					_alloc_traits;

		protected:
			typedef _bin_tree_node_base*		_base_ptr;
			typedef const _bin_tree_node_base*	_const_base_ptr;
			typedef _bin_tree_node<T>*			_link_type;
			typedef const _bin_tree_node<T>*	_const_link_type;
		
		private:
			struct _alloc_node
			{
				_alloc_node(_bin_tree& t)
				: _M_t(t)
				{}

				template <typename Arg>
				_link_type
				operator()	(const Arg& arg) const
				{
					return (_M_t._M_create_node(arg));
				}

				private:
					_bin_tree& _M_t;
			};

		public:
			typedef Key					key_type;
			typedef T					value_type;
			typedef value_type*			pointer;
			typedef const value_type*	const_pointer;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef size_t				size_type;
			typedef ptrdiff_t			difference_type;
			typedef Alloc				allocator_type;

			_node_allocator
			_M_get_node_allocator (void)
			{
				return (*static_cast<_node_allocator*>(&this->_M_impl));
			}

			const _node_allocator
			_M_get_node_allocator (void) const
			{
				return (*static_cast<const _node_allocator*>(&this->_M_impl));
			}

			allocator_type
			get_allocator (void) const
			{
				return (allocator_type(_M_get_node_allocator()));
			}

		protected:
			_link_type
			_M_get_node (void)
			{
				return (Alloc().allocate(1));
			}

			void
			_M_put_node (_link_type p)
			{
				Alloc().deallocate(p, 1);
			}

			void
			_M_construct_node (_link_type node, const value_type& x)
			{
				try
				{
					get_allocator().construct(node->_M_valptr(), x);
				}
				catch (std::exception& e)
				{
					_M_put_node(node);
					throw;
				}
			}

			_link_type
			_M_create_node(const value_type& x)
			{
				_link_type	tmp = _M_get_node();
				_M_construct_node(tmp, x);
				return (tmp);
			}

			void
			_M_destroy_node (_link_type p)
			{
				get_allocator().destroy(p->_M_valptr());
			}

			void
			_M_drop_node(_link_type p)
			{
				_M_destroy_node(p);
				_M_put_node(p);
			}

			template <typename NodeGen>
			_link_type
			_M_clone_node (_const_link_type x, NodeGen& node_gen)
			{
				_link_type	tmp = node_gen(*(x)->_M_valptr());
				tmp->_M_left = NULL;
				tmp->_M_right = NULL;
				return (tmp);
			}

			template <typename Key_compare>
			struct _bin_tree_impl : public _node_allocator
			{
				Key_compare				_M_key_compare;
				_bin_tree_node_base		_M_header;
				size_type				_M_node_count;

				_bin_tree_impl (void)
				: _node_allocator(), _M_key_compare(), _M_header(), _M_node_count(0)
				{
					_M_initialize();
				}

				_bin_tree_impl(const Key_compare& cmp, const _node_allocator& a)
				: _node_allocator(a), _M_key_compare(cmp), _M_header(), _M_node_count(0)
				{
					_M_initialize();
				}

				void
				_M_reset (void)
				{
					this->_M_header._M_parent = NULL;
					this->_M_header._M_left = &(this->_M_header);
					this->_M_header._M_right = &(this->_M_header);
					this->_M_node_count = 0;
				}

				private:
					void
					_M_initialize (void)
					{
						this->_M_header._M_parent = NULL;
						this->_M_header._M_left = &(this->_M_header);
						this->_M_header._M_right = &(this->_M_header);
					}
			};

			_bin_tree_impl<Compare>	_M_impl;

			protected:
				_base_ptr&
				_M_root (void)
				{
					return (this->_M_impl._M_header._M_parent);
				}

				_const_base_ptr&
				_M_root (void) const
				{
					return (this->_M_impl._M_header._M_parent);
				}

				_base_ptr&
				_M_leftmost (void)
				{
					return (this->_M_impl._M_header._M_left);
				}

				_const_base_ptr&
				_M_leftmost (void) const
				{
					return (this->_M_impl._M_header._M_left);
				}

				_base_ptr&
				_M_rightmost (void)
				{
					return (this->_M_impl._M_header._M_right);
				}

				_const_base_ptr&
				_M_rightmost (void) const
				{
					return (this->_M_impl._M_header._M_right);;
				}

				_link_type
				_M_begin (void)
				{
					return (static_cast<_link_type>(this->_M_impl._M_header._M_parent));
				}

				_const_link_type
				_M_begin (void) const
				{
					return (static_cast<_const_link_type>(this->_M_impl._M_header._M_parent));
				}

				_base_ptr
				_M_end (void)
				{
					return (&(this->_M_impl._M_header));
				}

				_const_base_ptr
				_M_end (void) const
				{
					return (&(this->_M_impl._M_header));
				}

				static const_reference
				_S_value (_const_link_type x)
				{
					return (*(x->_M_valptr()));
				}

				static const Key&
				_S_key (_const_link_type x)
				{
					return (KeyOfValue()(_S_value(x)));
				}

				static _link_type
				_S_left (_base_ptr x)
				{
					return (static_cast<_link_type>(x->_M_left));
				}

				static _const_link_type
				_S_left (_const_base_ptr x)
				{
					return (static_cast<_const_link_type>(x->_M_left));
				}

				static _link_type
				_S_right (_base_ptr x)
				{
					return (static_cast<_link_type>(x->_M_right));
				}

				static _const_link_type
				_S_right (_const_base_ptr x)
				{
					return (static_cast<_const_link_type>(x->_M_right));
				}

				static const_reference
				_S_value(_const_base_ptr x)
				{
					return (*(static_cast<_const_link_type>(x)->_M_valptr()));
				}

				static const Key&
				_S_key(_const_base_ptr x)
				{
					return (KeyOfValue()(_S_value(x)));
				}

				static _base_ptr
				_S_minimum(_base_ptr x)
				{
					return (_bin_tree_node_base::_S_min(x));
				}

				static _const_base_ptr
				_S_minimum(_const_base_ptr x)
				{
					return (_bin_tree_node_base::_S_min(x));
				}

				static _base_ptr
				_S_maximum(_base_ptr x)
				{
					return (_bin_tree_node_base::_S_max(x));
				}

				static _const_base_ptr
				_S_maximum(_const_base_ptr x)
				{
					return (_bin_tree_node_base::_S_max(x));
				}

				void
				_M_erase(_link_type x);

			public:
				typedef	_bin_tree_iterator<value_type>			iterator;
				typedef _bin_tree_const_iterator<value_type>	const_iterator;
				typedef	ft::reverse_iterator<iterator>			reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

				_bin_tree (void)
				{}

				_bin_tree (const Compare& comp, const allocator_type& a = allocator_type())
				: _M_impl(comp, a)
				{}

				_bin_tree (const _bin_tree& x)
				: _M_impl(x._M_impl._M_key_compare, x._M_get_Node_allocator())
				{
					if (x._M_root() != 0)
					{
						_M_root() = _M_copy(x._M_begin(), _M_end());
						_M_leftmost() = _S_minimum(_M_root());
						_M_rightmost() = _S_maximum(_M_root());
						_M_impl._M_node_count = x._M_impl._M_node_count;
					}
				}

				~_bin_tree (void)
				{
				//	_M_erase(_M_begin());
				}

				iterator
				begin (void)
				{
					return (iterator(this->_M_impl._M_header._M_left));
				}

				const_iterator
				begin (void) const
				{
					return (const_iterator(this->_M_impl._M_header._M_left));
				}

				iterator
				end (void)
				{
					return (iterator(&this->_M_impl._M_header));
				}

				const_iterator
				end (void) const
				{
					return (const_iterator(&this->_M_impl._M_header));
				}

				reverse_iterator
				rbegin (void)
				{
					return (reverse_iterator(end()));
				}

				const_reverse_iterator
				rbegin (void) const
				{
					return (const_reverse_iterator(end()));
				}

				reverse_iterator
				rend (void)
				{
					return (reverse_iterator(begin()));
				}

				const_reverse_iterator
				rend (void) const
				{
					return (const_reverse_iterator(begin()));
				}

				bool
				empty (void) const
				{
					return (_M_impl._M_node_count == 0);
				}

				size_type
				size (void) const
				{
					return (_M_impl._M_node_count);
				}

				size_type
				max_empty (void) const
				{
					return (Alloc().max_size());
				}

				template <typename NodeGen>
				iterator
				_M_insert_(_base_ptr, _base_ptr, const value_type&, NodeGen&);

				pair<_base_ptr, _base_ptr>
				_M_get_insert_unique_pos(const key_type& k)
				{
					typedef pair<_base_ptr, _base_ptr> _res;
					_link_type x = _M_begin();
					_base_ptr y = _M_end();
					bool comp = true;
					while (x != 0)
					{
						y = x;
						comp = _M_impl._M_key_compare(k, _S_key(x));
						x = comp ? _S_left(x) : _S_right(x);
					}
					iterator j = iterator(y);
					if (comp)
					{
						if (j == begin())
							return (_res(x, y));
						else
							--j;
					}
					if (_M_impl._M_key_compare(_S_key(j._M_node), k))
						return _res(x, y);
					return (_res(j._M_node, 0));
				}

				pair<_base_ptr, _base_ptr>
				_M_get_insert_equal_pos(const key_type& k)
				{
					typedef pair<_base_ptr, _base_ptr> _res;
					_link_type x = _M_begin();
					_base_ptr y = _M_end();
					while (x != 0)
					{
						y = x;
						x = _M_impl._M_key_compare(k, _S_key(x)) ?
						_S_left(x) : _S_right(x);
					}
					return (_res(x, y));
				}

				pair<_base_ptr, _base_ptr>
				_M_get_insert_hint_unique_pos(const_iterator pos,
											const key_type& k)
				{
					iterator itpos = pos._M_const_cast();
					typedef pair<_base_ptr, _base_ptr>	_res;
					if (itpos._M_node == _M_end())
					{
						if (size() > 0 && _M_impl._M_key_compare(_S_key(_M_rightmost()), k))
							return (_res(0, _M_rightmost()));
						else
							return (_M_get_insert_unique_pos(k));
					}
					else if (_M_impl._M_key_compare(k, _S_key(itpos._M_node)))
					{
						iterator before = itpos;
						if (pos._M_node == _M_leftmost())
							return (_res(_M_leftmost(), _M_leftmost()));
						else if (_M_impl._M_key_compare(_S_key((--before)._M_node), k))
						{
							if (_S_right(before._M_node) == 0)
								return (_res(0, before._M_node));
							else
								return (_res(itpos._M_node, itpos._M_node));
						}
						else
							return (_M_get_insert_unique_pos(k));
					}
					else if (_M_impl._M_key_compare(_S_key(itpos._M_node), k))
					{
						iterator after = itpos;
						if (pos._M_node == _M_rightmost())
							return (_res(0, _M_rightmost()));
						else if (_M_impl._M_key_compare(k, _S_key((++after)._M_node)))
						{
							if (_S_right(itpos._M_node) == 0)
								return (_res(0, itpos._M_node));
							else
								return (_res(after._M_node, after._M_node));
						}
						else
							return _M_get_insert_unique_pos(k);
					}
					else
						return (_res(itpos._M_node, 0));
				}

				pair<_base_ptr, _base_ptr>
				_M_get_insert_hint_equal_pos(const_iterator pos,
											const key_type& k)
				{
					iterator itpos = pos._M_const_cast();
					typedef pair<_base_ptr, _base_ptr> _res;
					if (pos._M_node == _M_end())
					{
						if (size() > 0 && !_M_impl._M_key_compare(k, _S_key(_M_rightmost())))
							return (_res(0, _M_rightmost()));
						else
							return (_M_get_insert_equal_pos(k));
					}
					else if (!_M_impl._M_key_compare(_S_key(itpos._M_node), k))
					{
						iterator before = itpos;
						if (itpos._M_node == _M_leftmost())
							return (_res(_M_leftmost(), _M_leftmost()));
						else if (!_M_impl._M_key_compare(k, _S_key((--before)._M_node)))
						{
							if (_S_right(before._M_node) == 0)
								return (_res(0, before._M_node));
							else
								return (_res(itpos._M_node, itpos._M_node));
						}
						else
							return (_M_get_insert_equal_pos(k));
					}
					else
					{
						iterator after = itpos;
						if (itpos._M_node == _M_rightmost())
							return (_res(0, _M_rightmost()));
						else if (!_M_impl._M_key_compare(_S_key((++after)._M_node), k))
						{
							if (_S_right(itpos._M_node) == 0)
								return (_res(0, itpos._M_node));
							else
								return (_res(after._M_node, after._M_node));
						}
						else
							return (_res(0, 0));
					}
				}

				pair<typename _bin_tree<Key, T, KeyOfValue, Compare, Alloc>::iterator, bool>
				_M_insert_unique (const T& v)
				{
					typedef pair<iterator, bool> Res;
					pair<_base_ptr, _base_ptr> res = _M_get_insert_unique_pos(KeyOfValue()(v));

					if (res.second)
					{
						_alloc_node	an(*this);
						return (Res(_M_insert_(res.first, res.second, v, an, true)));
					}
					return (iterator(res.first), false);
				}
	};

	template <typename Key, typename T, typename KeyOfValue,
			typename Compare, typename Alloc>
		template <typename NodeGem>
			typename _bin_tree<Key, T, KeyOfValue, Compare, Alloc>::iterator
			_bin_tree<Key, T, KeyOfValue, Compare, Alloc>::
			_M_insert_(_base_ptr x, _base_ptr p,
				 const T& v,
				 NodeGem& node_gen)
			{
				bool insert_left = (x != 0 || p == _M_end()
					|| _M_impl._M_key_compare(KeyOfValue()(v), _S_key(p)));
				_link_type z = node_gen(v);
				_bin_tree_insert_and_rebalance(insert_left, z, p, this->_M_impl._M_header);
				++_M_impl._M_node_count;
				return (iterator(z));
			}

	template <typename Key, typename T, typename KeyOfValue,
					 typename Compare, typename Alloc>
		void
		_bin_tree<Key, T, KeyOfValue, Compare, Alloc>::
		_M_erase(_link_type x)
		{
			while (x != 0)
			{
				_M_erase(_S_right(x));
				_link_type y = _S_left(x);
				_M_drop_node(x);
				x = y;
			}
		}
}
