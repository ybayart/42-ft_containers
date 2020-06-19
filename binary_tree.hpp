

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
				return (_alloc_traits().allocate(1));
			}

			void
			_M_put_node (_link_type p)
			{
				_alloc_traits().deallocate(p, 1);
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
					throw ();
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
			struct _bin_tree_impl : pubic _node_allocator
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
	};
}
