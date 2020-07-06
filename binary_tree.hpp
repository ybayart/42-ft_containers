
#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

namespace ft
{
	enum _bin_tree_color { _S_red = false, _S_black = true };

	struct _bin_tree_node_base
	{
		typedef _bin_tree_node_base* _Base_ptr;
		typedef const _bin_tree_node_base* _Const_Base_ptr;

		_bin_tree_color	_M_color;
		_Base_ptr		_M_parent;
		_Base_ptr		_M_left;
		_Base_ptr		_M_right;

		static _Base_ptr
		_S_minimum(_Base_ptr x)
		{
			while (x->_M_left != 0)
				x = x->_M_left;
			return (x);
		}

		static _Const_Base_ptr
		_S_minimum(_Const_Base_ptr x)
		{
			while (x->_M_left != 0)
				x = x->_M_left;
			return (x);
		}

		static _Base_ptr
		_S_maximum(_Base_ptr x)
		{
			while (x->_M_right != 0)
				x = x->_M_right;
			return (x);
		}

		static _Const_Base_ptr
		_S_maximum(_Const_Base_ptr x)
		{
			while (x->_M_right != 0)
				x = x->_M_right;
			return (x);
		}
	};

	template<typename Val>
		struct _bin_tree_node : public _bin_tree_node_base
		{
			typedef _bin_tree_node<Val>* _Link_type;

			Val _MValue_field;

			Val*
			_MValptr()
			{
				return (&_MValue_field);
			}

			const Val*
			_MValptr() const
			{
				return (&_MValue_field);
			}
		};

	_bin_tree_node_base*
	_bin_tree_increment(_bin_tree_node_base* x) throw ();

	const _bin_tree_node_base*
	_bin_tree_increment(const _bin_tree_node_base* x) throw ();

	_bin_tree_node_base*
	_bin_tree_decrement(_bin_tree_node_base* x) throw ();

	const _bin_tree_node_base*
	_bin_tree_decrement(const _bin_tree_node_base* x) throw ();

	template<typename _Tp>
		struct _bin_tree_iterator
		{
			typedef _Tp	value_type;
			typedef _Tp& reference;
			typedef _Tp* pointer;

			typedef bidirectional_iterator_tag 		iterator_category;
			typedef ptrdiff_t						difference_type;

			typedef _bin_tree_iterator<_Tp>			_Self;
			typedef _bin_tree_node_base::_Base_ptr	_Base_ptr;
			typedef _bin_tree_node<_Tp>*			_Link_type;

			_bin_tree_iterator()
			: _M_node() {}

			explicit
			_bin_tree_iterator(_Base_ptr x)
			: _M_node(x) {}

			reference
			operator*() const
			{
				return (*static_cast<_Link_type>(_M_node)->_MValptr());
			}

			pointer
			operator->() const
			{
				return (static_cast<_Link_type> (_M_node)->_MValptr());
			}

			_Self&
			operator++()
			{
				_M_node = _bin_tree_increment(_M_node);
				return (*this);
			}

			_Self
			operator++(int)
			{
				_Self tmp = *this;
				_M_node = _bin_tree_increment(_M_node);
				return (tmp);
			}

			_Self&
			operator--()
			{
				_M_node = _bin_tree_decrement(_M_node);
				return (*this);
			}

			_Self
			operator--(int)
			{
				_Self tmp = *this;
				_M_node = _bin_tree_decrement(_M_node);
				return (tmp);
			}

			bool
			operator==(const _Self& x) const
			{
				return (_M_node == x._M_node);
			}

			bool
			operator!=(const _Self& x) const
			{
				return (_M_node != x._M_node);
			}

			_Base_ptr _M_node;
	};

	template<typename _Tp>
		struct _bin_tree_const_iterator
		{
			typedef _Tp			value_type;
			typedef const _Tp&	reference;
			typedef const _Tp*	pointer;

			typedef _bin_tree_iterator<_Tp>		iterator;

			typedef bidirectional_iterator_tag	iterator_category;
			typedef ptrdiff_t					difference_type;

			typedef _bin_tree_const_iterator<_Tp>			_Self;
			typedef _bin_tree_node_base::_Const_Base_ptr	_Base_ptr;
			typedef const _bin_tree_node<_Tp>*				_Link_type;

			_bin_tree_const_iterator()
			: _M_node() {}

			explicit
			_bin_tree_const_iterator(_Base_ptr x)
			: _M_node(x) {}

			_bin_tree_const_iterator(const iterator& it)
			: _M_node(it._M_node) {}

			iterator
			_M_const_cast() const
			{
				return (iterator(const_cast<typename iterator::_Base_ptr>(_M_node)));
			}

			reference
			operator*() const
			{
				return (*static_cast<_Link_type>(_M_node)->_MValptr());
			}

			pointer
			operator->() const
			{
				return (static_cast<_Link_type>(_M_node)->_MValptr()); }

			_Self&
			operator++()
			{
				_M_node = _bin_tree_increment(_M_node);
				return (*this);
			}

			_Self
			operator++(int)
			{
				_Self tmp = *this;
				_M_node = _bin_tree_increment(_M_node);
				return (tmp);
			}

			_Self&
			operator--()
			{
				_M_node = _bin_tree_decrement(_M_node);
				return (*this);
			}

			_Self
			operator--(int)
			{
				_Self tmp = *this;
				_M_node = _bin_tree_decrement(_M_node);
				return (tmp);
			}

			bool
			operator==(const _Self& x) const
			{
				return (_M_node == x._M_node);
			}

			bool
			operator!=(const _Self& x) const
			{
				return (_M_node != x._M_node);
			}

			_Base_ptr _M_node;
		};

	template<typename Val>
		inline bool
		operator==(const _bin_tree_iterator<Val>& x,
					const _bin_tree_const_iterator<Val>& y)
		{
			return (x._M_node == y._M_node);
		}

	template<typename Val>
		inline bool
		operator!=(const _bin_tree_iterator<Val>& x,
					const _bin_tree_const_iterator<Val>& y)
		{
			return (x._M_node != y._M_node);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc = std::allocator<Val> >
		class _bin_tree
		{
			typedef typename _Alloc::template
				rebind<_bin_tree_node<Val> >::other _Node_allocator;

			typedef _Node_allocator _Alloc_traits;

		protected:
			typedef _bin_tree_node_base* 		_Base_ptr;
			typedef const _bin_tree_node_base* 	_Const_Base_ptr;
			typedef _bin_tree_node<Val>* 		_Link_type;
			typedef const _bin_tree_node<Val>*	_Const_Link_type;

		private:
			struct _Reuse_or_alloc_node
			{
				_Reuse_or_alloc_node(_bin_tree& t)
				: _M_root(t._M_root()), _M_nodes(t._M_rightmost()), _M_t(t)
				{
					if (_M_root)
					{
						_M_root->_M_parent = 0;

						if (_M_nodes->_M_left)
							_M_nodes = _M_nodes->_M_left;
					}
					else
						_M_nodes = 0;
				}

				~_Reuse_or_alloc_node()
				{
					_M_t._M_erase(static_cast<_Link_type>(_M_root));
				}

				template<typename Arg>
					_Link_type
					operator()(const Arg& arg)
					{
						_Link_type node = static_cast<_Link_type>(_M_extract());
						if (node)
						{
							_M_t._M_destroy_node(node);
							_M_t._M_construct_node(node, arg);
							return (node);
						}
						return (_M_t._M_create_node(arg));
					}

				private:
				_Base_ptr
				_M_extract (void)
				{
					if (!_M_nodes)
						return _M_nodes;

					_Base_ptr node = _M_nodes;
					_M_nodes = _M_nodes->_M_parent;
					if (_M_nodes)
					{
						if (_M_nodes->_M_right == node)
						{
							_M_nodes->_M_right = 0;

							if (_M_nodes->_M_left)
							{
								_M_nodes = _M_nodes->_M_left;

								while (_M_nodes->_M_right)
									_M_nodes = _M_nodes->_M_right;

								if (_M_nodes->_M_left)
									_M_nodes = _M_nodes->_M_left;
							}
						}
						else
							_M_nodes->_M_left = 0;
					}
					else
						_M_root = 0;

					return node;
				}

				_Base_ptr _M_root;
				_Base_ptr _M_nodes;
				_bin_tree& _M_t;
			};

			struct _Alloc_node
			{
				_Alloc_node(_bin_tree& t)
				: _M_t(t)
				{}

				template<typename Arg>
					_Link_type
					operator()(const Arg& arg) const
					{
						return (_M_t._M_create_node(arg));
					}

				private:
				_bin_tree& _M_t;
			};

				public:
					typedef Key 				key_type;
					typedef Val 				value_type;
					typedef value_type* 			pointer;
					typedef const value_type* 		const_pointer;
					typedef value_type& 			reference;
					typedef const value_type& 		const_reference;
					typedef size_t 				size_type;
					typedef ptrdiff_t 			difference_type;
					typedef _Alloc 				allocator_type;

					_Node_allocator&
					_M_get_Node_allocator()
					{ return *static_cast<_Node_allocator*>(&this->_M_impl); }
					
					const _Node_allocator&
					_M_get_Node_allocator() const
					{ return *static_cast<const _Node_allocator*>(&this->_M_impl); }

					allocator_type
					get_allocator() const
					{ return allocator_type(_M_get_Node_allocator()); }

				protected:
					_Link_type
					_M_get_node()
					{ return _M_get_Node_allocator().allocate(1); }

					void
					_M_put_node(_Link_type p)
					{ _M_get_Node_allocator().deallocate(p, 1); }

					void
					_M_construct_node(_Link_type node, const value_type& x)
					{
						try
						{
							get_allocator().construct(node->_MValptr(), x);
						}
						catch(std::exception &e)
						{
							_M_put_node(node);
							throw;
						}
					}

			_Link_type
			_M_create_node(const value_type& x)
			{
	_Link_type tmp = _M_get_node();
	_M_construct_node(tmp, x);
	return tmp;
			}

			void
			_M_destroy_node(_Link_type p)
			{ get_allocator().destroy(p->_MValptr()); }

			void
			_M_drop_node(_Link_type p)
			{
	_M_destroy_node(p);
	_M_put_node(p);
			}

			template<typename _NodeGen>
	_Link_type
	_M_clone_node(_Const_Link_type x, _NodeGen& node_gen)
	{
		_Link_type tmp = node_gen(*x->_MValptr());
		tmp->_M_color = x->_M_color;
		tmp->_M_left = 0;
		tmp->_M_right = 0;
		return tmp;
	}

		protected:
			// Unused _Is_pod_comparator is kept as it is part of mangled name.
			template<typename KeyCompare>
				struct _bin_tree_impl : public _Node_allocator
				{
		KeyCompare		_MKeyCompare;
		_bin_tree_node_base 	_M_header;
		size_type 		_M_node_count; // Keeps track of size of tree.

		_bin_tree_impl()
		: _Node_allocator(), _MKeyCompare(), _M_header(),
			_M_node_count(0)
		{ _M_initialize(); }

		_bin_tree_impl(const KeyCompare& comp, const _Node_allocator& a)
		: _Node_allocator(a), _MKeyCompare(comp), _M_header(),
			_M_node_count(0)
		{ _M_initialize(); }

		void
		_M_reset()
		{
			this->_M_header._M_parent = 0;
			this->_M_header._M_left = &this->_M_header;
			this->_M_header._M_right = &this->_M_header;
			this->_M_node_count = 0;
		}

	private:
		void
		_M_initialize()
		{
			this->_M_header._M_color = _S_red;
			this->_M_header._M_parent = 0;
			this->_M_header._M_left = &this->_M_header;
			this->_M_header._M_right = &this->_M_header;
		}			
	};

			_bin_tree_impl<Compare> _M_impl;

		protected:
			_Base_ptr&
			_M_root()
			{ return this->_M_impl._M_header._M_parent; }

			_Const_Base_ptr
			_M_root() const
			{ return this->_M_impl._M_header._M_parent; }

			_Base_ptr&
			_M_leftmost()
			{ return this->_M_impl._M_header._M_left; }

			_Const_Base_ptr
			_M_leftmost() const
			{ return this->_M_impl._M_header._M_left; }

			_Base_ptr&
			_M_rightmost()
			{ return this->_M_impl._M_header._M_right; }

			_Const_Base_ptr
			_M_rightmost() const
			{ return this->_M_impl._M_header._M_right; }

			_Link_type
			_M_begin()
			{ return static_cast<_Link_type>(this->_M_impl._M_header._M_parent); }

			_Const_Link_type
			_M_begin() const
			{
	return static_cast<_Const_Link_type>
		(this->_M_impl._M_header._M_parent);
			}

			_Base_ptr
			_M_end()
			{ return &this->_M_impl._M_header; }

			_Const_Base_ptr
			_M_end() const
			{ return &this->_M_impl._M_header; }

			static const_reference
			_SValue(_Const_Link_type x)
			{ return *x->_MValptr(); }

			static const Key&
			_SKey(_Const_Link_type x)
			{ return KeyOfValue()(_SValue(x)); }

			static _Link_type
			_S_left(_Base_ptr x)
			{ return static_cast<_Link_type>(x->_M_left); }

			static _Const_Link_type
			_S_left(_Const_Base_ptr x)
			{ return static_cast<_Const_Link_type>(x->_M_left); }

			static _Link_type
			_S_right(_Base_ptr x)
			{ return static_cast<_Link_type>(x->_M_right); }

			static _Const_Link_type
			_S_right(_Const_Base_ptr x)
			{ return static_cast<_Const_Link_type>(x->_M_right); }

			static const_reference
			_SValue(_Const_Base_ptr x)
			{ return *static_cast<_Const_Link_type>(x)->_MValptr(); }

			static const Key&
			_SKey(_Const_Base_ptr x)
			{ return KeyOfValue()(_SValue(x)); }

			static _Base_ptr
			_S_minimum(_Base_ptr x)
			{ return _bin_tree_node_base::_S_minimum(x); }

			static _Const_Base_ptr
			_S_minimum(_Const_Base_ptr x)
			{ return _bin_tree_node_base::_S_minimum(x); }

			static _Base_ptr
			_S_maximum(_Base_ptr x)
			{ return _bin_tree_node_base::_S_maximum(x); }

			static _Const_Base_ptr
			_S_maximum(_Const_Base_ptr x)
			{ return _bin_tree_node_base::_S_maximum(x); }

		public:
			typedef _bin_tree_iterator<value_type>			 iterator;
			typedef _bin_tree_const_iterator<value_type> const_iterator;

			typedef std::reverse_iterator<iterator>			 reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			pair<_Base_ptr, _Base_ptr>
			_M_get_insert_unique_pos(const key_type& k);

			pair<_Base_ptr, _Base_ptr>
			_M_get_insert_equal_pos(const key_type& k);

			pair<_Base_ptr, _Base_ptr>
			_M_get_insert_hint_unique_pos(const_iterator pos,
						const key_type& k);

			pair<_Base_ptr, _Base_ptr>
			_M_get_insert_hint_equal_pos(const_iterator pos,
					 const key_type& k);

		private:
			template<typename _NodeGen>
	iterator
	_M_insert_(_Base_ptr x, _Base_ptr y,
			 const value_type& v, _NodeGen&);

			// _GLIBCXX_RESOLVE_LIB_DEFECTS
			// 233. Insertion hints in associative containers.
			iterator
			_M_insert_lower(_Base_ptr y, const value_type& v);

			iterator
			_M_insert_equal_lower(const value_type& x);

			template<typename _NodeGen>
	_Link_type
	_M_copy(_Const_Link_type x, _Base_ptr p, _NodeGen&);

			_Link_type
			_M_copy(_Const_Link_type x, _Base_ptr p)
			{
	_Alloc_node an(*this);
	return _M_copy(x, p, an);
			}

			void
			_M_erase(_Link_type x);

			iterator
			_M_lower_bound(_Link_type x, _Base_ptr y,
				 const Key& k);

			const_iterator
			_M_lower_bound(_Const_Link_type x, _Const_Base_ptr y,
				 const Key& k) const;

			iterator
			_M_upper_bound(_Link_type x, _Base_ptr y,
				 const Key& k);

			const_iterator
			_M_upper_bound(_Const_Link_type x, _Const_Base_ptr y,
				 const Key& k) const;

		public:
			// allocation/deallocation
			_bin_tree() { }

			_bin_tree(const Compare& comp,
				 const allocator_type& a = allocator_type())
			: _M_impl(comp, _Node_allocator(a)) { }

			_bin_tree(const _bin_tree& x)
			: _M_impl(x._M_impl._MKeyCompare,
					_Alloc_traits::_S_select_on_copy(x._M_get_Node_allocator()))
			{
	if (x._M_root() != 0)
		{
			_M_root() = _M_copy(x._M_begin(), _M_end());
			_M_leftmost() = _S_minimum(_M_root());
			_M_rightmost() = _S_maximum(_M_root());
			_M_impl._M_node_count = x._M_impl._M_node_count;
		}
			}

			~_bin_tree()
			{ _M_erase(_M_begin()); }

			_bin_tree&
			operator=(const _bin_tree& x);

			// Accessors.
			Compare
			key_comp() const
			{ return _M_impl._MKeyCompare; }

			iterator
			begin()
			{ return iterator(this->_M_impl._M_header._M_left); }

			const_iterator
			begin() const
			{ return const_iterator(this->_M_impl._M_header._M_left); }

			iterator
			end()
			{ return iterator(&this->_M_impl._M_header); }

			const_iterator
			end() const
			{ return const_iterator(&this->_M_impl._M_header); }

			reverse_iterator
			rbegin()
			{ return reverse_iterator(end()); }

			const_reverse_iterator
			rbegin() const
			{ return const_reverse_iterator(end()); }

			reverse_iterator
			rend()
			{ return reverse_iterator(begin()); }

			const_reverse_iterator
			rend() const
			{ return const_reverse_iterator(begin()); }

			bool
			empty() const
			{ return _M_impl._M_node_count == 0; }

			size_type
			size() const 
			{ return _M_impl._M_node_count; }

			size_type
			max_size() const
			{ return _M_get_Node_allocator().max_size(); }

			void
			swap(_bin_tree& t);

			// Insert/erase.
			pair<iterator, bool>
			_M_insert_unique(const value_type& x);

			iterator
			_M_insert_equal(const value_type& x);

			template<typename _NodeGen>
	iterator
	_M_insert_unique_(const_iterator pos, const value_type& x,
				_NodeGen&);

			iterator
			_M_insert_unique_(const_iterator pos, const value_type& x)
			{
	_Alloc_node an(*this);
	return _M_insert_unique_(pos, x, an);
			}

			template<typename _NodeGen>
	iterator
	_M_insert_equal_(const_iterator pos, const value_type& x,
			 _NodeGen&);
			iterator
			_M_insert_equal_(const_iterator pos, const value_type& x)
			{
	_Alloc_node an(*this);
	return _M_insert_equal_(pos, x, an);
			}

			template<typename _InputIterator>
				void
				_M_insert_unique(_InputIterator first, _InputIterator last);

			template<typename _InputIterator>
				void
				_M_insert_equal(_InputIterator first, _InputIterator last);

		private:
			void
			_M_erase_aux(const_iterator position);

			void
			_M_erase_aux(const_iterator first, const_iterator last);

		public:
			void
			erase(iterator position)
			{ _M_erase_aux(position); }

			void
			erase(const_iterator position)
			{ _M_erase_aux(position); }
			size_type
			erase(const key_type& x);

			void
			erase(iterator first, iterator last)
			{ _M_erase_aux(first, last); }

			void
			erase(const_iterator first, const_iterator last)
			{ _M_erase_aux(first, last); }
			void
			erase(const key_type* first, const key_type* last);

			void
			clear()
			{
				_M_erase(_M_begin());
	_M_impl._M_reset();
			}

			// Set operations.
			iterator
			find(const key_type& k);

			const_iterator
			find(const key_type& k) const;

			size_type
			count(const key_type& k) const;

			iterator
			lower_bound(const key_type& k)
			{ return _M_lower_bound(_M_begin(), _M_end(), k); }

			const_iterator
			lower_bound(const key_type& k) const
			{ return _M_lower_bound(_M_begin(), _M_end(), k); }

			iterator
			upper_bound(const key_type& k)
			{ return _M_upper_bound(_M_begin(), _M_end(), k); }

			const_iterator
			upper_bound(const key_type& k) const
			{ return _M_upper_bound(_M_begin(), _M_end(), k); }

			pair<iterator, iterator>
			equal_range(const key_type& k);

			pair<const_iterator, const_iterator>
			equal_range(const key_type& k) const;

			// Debugging.
			bool
			rb_verify() const;

		};

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		inline bool
		operator==(const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& x,
				 const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& y)
		{
			return x.size() == y.size()
			 && std::equal(x.begin(), x.end(), y.begin());
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		inline bool
		operator<(const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& x,
				const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& y)
		{
			return std::lexicographicalCompare(x.begin(), x.end(), 
						y.begin(), y.end());
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		inline bool
		operator!=(const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& x,
				 const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& y)
		{ return !(x == y); }

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		inline bool
		operator>(const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& x,
				const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& y)
		{ return y < x; }

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		inline bool
		operator<=(const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& x,
				 const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& y)
		{ return !(y < x); }

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		inline bool
		operator>=(const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& x,
				 const _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& y)
		{ return !(x < y); }

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		inline void
		swap(_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& x,
	 _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>& y)
		{ x.swap(y); }

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>&
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		operator=(const _bin_tree& x)
		{
			if (this != &x)
	{
		// Note that Key may be a constant type.

		_Reuse_or_alloc_node roan(*this);
		_M_impl._M_reset();
		_M_impl._MKeyCompare = x._M_impl._MKeyCompare;
		if (x._M_root() != 0)
			{
				_M_root() = _M_copy(x._M_begin(), _M_end(), roan);
				_M_leftmost() = _S_minimum(_M_root());
				_M_rightmost() = _S_maximum(_M_root());
				_M_impl._M_node_count = x._M_impl._M_node_count;
			}
	}

			return *this;
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		template<typename _NodeGen>
			typename _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::iterator
			_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
			_M_insert_(_Base_ptr x, _Base_ptr p,
		 const Val& v,
		 _NodeGen& node_gen)
			{
	bool insert_left = (x != 0 || p == _M_end()
						|| _M_impl._MKeyCompare(KeyOfValue()(v),
							_SKey(p)));

	_Link_type z = node_gen(v);

	_bin_tree_insert_and_rebalance(insert_left, z, p,
							this->_M_impl._M_header);
	++_M_impl._M_node_count;
	return iterator(z);
			}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::iterator
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_insert_lower(_Base_ptr p, const Val& v)
		{
			bool insert_left = (p == _M_end()
					|| !_M_impl._MKeyCompare(_SKey(p),
									 KeyOfValue()(v)));

			_Link_type z = _M_create_node(v);

			_bin_tree_insert_and_rebalance(insert_left, z, p,
						this->_M_impl._M_header);
			++_M_impl._M_node_count;
			return iterator(z);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::iterator
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_insert_equal_lower(const Val& v)
		{
			_Link_type x = _M_begin();
			_Base_ptr y = _M_end();
			while (x != 0)
	{
		y = x;
		x = !_M_impl._MKeyCompare(_SKey(x), KeyOfValue()(v)) ?
					_S_left(x) : _S_right(x);
	}
			return _M_insert_lower(y, v);
		}

	template<typename Key, typename Val, typename _KoV,
		 typename Compare, typename _Alloc>
		template<typename _NodeGen>
			typename _bin_tree<Key, Val, _KoV, Compare, _Alloc>::_Link_type
			_bin_tree<Key, Val, _KoV, Compare, _Alloc>::
			_M_copy(_Const_Link_type x, _Base_ptr p, _NodeGen& node_gen)
			{
	// Structural copy. x and p must be non-null.
	_Link_type top = _M_clone_node(x, node_gen);
	top->_M_parent = p;

	try
		{
			if (x->_M_right)
				top->_M_right = _M_copy(_S_right(x), top, node_gen);
			p = top;
			x = _S_left(x);

			while (x != 0)
				{
		_Link_type y = _M_clone_node(x, node_gen);
		p->_M_left = y;
		y->_M_parent = p;
		if (x->_M_right)
			y->_M_right = _M_copy(_S_right(x), y, node_gen);
		p = y;
		x = _S_left(x);
				}
		}
	catch(std::exception &e)
		{
			_M_erase(top);
			throw;
		}
	return top;
			}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		void
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_erase(_Link_type x)
		{
			// Erase without rebalancing.
			while (x != 0)
	{
		_M_erase(_S_right(x));
		_Link_type y = _S_left(x);
		_M_drop_node(x);
		x = y;
	}
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue,
					Compare, _Alloc>::iterator
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_lower_bound(_Link_type x, _Base_ptr y,
			 const Key& k)
		{
			while (x != 0)
	if (!_M_impl._MKeyCompare(_SKey(x), k))
		y = x, x = _S_left(x);
	else
		x = _S_right(x);
			return iterator(y);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue,
					Compare, _Alloc>::const_iterator
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_lower_bound(_Const_Link_type x, _Const_Base_ptr y,
			 const Key& k) const
		{
			while (x != 0)
	if (!_M_impl._MKeyCompare(_SKey(x), k))
		y = x, x = _S_left(x);
	else
		x = _S_right(x);
			return const_iterator(y);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue,
					Compare, _Alloc>::iterator
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_upper_bound(_Link_type x, _Base_ptr y,
			 const Key& k)
		{
			while (x != 0)
	if (_M_impl._MKeyCompare(k, _SKey(x)))
		y = x, x = _S_left(x);
	else
		x = _S_right(x);
			return iterator(y);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue,
					Compare, _Alloc>::const_iterator
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_upper_bound(_Const_Link_type x, _Const_Base_ptr y,
			 const Key& k) const
		{
			while (x != 0)
	if (_M_impl._MKeyCompare(k, _SKey(x)))
		y = x, x = _S_left(x);
	else
		x = _S_right(x);
			return const_iterator(y);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		pair<typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::iterator,
	 typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::iterator>
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		equal_range(const Key& k)
		{
			_Link_type x = _M_begin();
			_Base_ptr y = _M_end();
			while (x != 0)
	{
		if (_M_impl._MKeyCompare(_SKey(x), k))
			x = _S_right(x);
		else if (_M_impl._MKeyCompare(k, _SKey(x)))
			y = x, x = _S_left(x);
		else
			{
				_Link_type xu(x);
				_Base_ptr yu(y);
				y = x, x = _S_left(x);
				xu = _S_right(xu);
				return pair<iterator,
							iterator>(_M_lower_bound(x, y, k),
						_M_upper_bound(xu, yu, k));
			}
	}
			return pair<iterator, iterator>(iterator(y),
							iterator(y));
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		pair<typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::const_iterator,
	 typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::const_iterator>
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		equal_range(const Key& k) const
		{
			_Const_Link_type x = _M_begin();
			_Const_Base_ptr y = _M_end();
			while (x != 0)
	{
		if (_M_impl._MKeyCompare(_SKey(x), k))
			x = _S_right(x);
		else if (_M_impl._MKeyCompare(k, _SKey(x)))
			y = x, x = _S_left(x);
		else
			{
				_Const_Link_type xu(x);
				_Const_Base_ptr yu(y);
				y = x, x = _S_left(x);
				xu = _S_right(xu);
				return pair<const_iterator,
							const_iterator>(_M_lower_bound(x, y, k),
						_M_upper_bound(xu, yu, k));
			}
	}
			return pair<const_iterator, const_iterator>(const_iterator(y),
							const_iterator(y));
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		void
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		swap(_bin_tree& t)
		{
			if (_M_root() == 0)
	{
		if (t._M_root() != 0)
			{
				_M_root() = t._M_root();
				_M_leftmost() = t._M_leftmost();
				_M_rightmost() = t._M_rightmost();
				_M_root()->_M_parent = _M_end();
				_M_impl._M_node_count = t._M_impl._M_node_count;
				
				t._M_impl._M_reset();
			}
	}
			else if (t._M_root() == 0)
	{
		t._M_root() = _M_root();
		t._M_leftmost() = _M_leftmost();
		t._M_rightmost() = _M_rightmost();
		t._M_root()->_M_parent = t._M_end();
		t._M_impl._M_node_count = _M_impl._M_node_count;
		
		_M_impl._M_reset();
	}
			else
	{
		std::swap(_M_root(),t._M_root());
		std::swap(_M_leftmost(),t._M_leftmost());
		std::swap(_M_rightmost(),t._M_rightmost());
		
		_M_root()->_M_parent = _M_end();
		t._M_root()->_M_parent = t._M_end();
		std::swap(this->_M_impl._M_node_count, t._M_impl._M_node_count);
	}
			// No need to swap header's color as it does not change.
			std::swap(this->_M_impl._MKeyCompare, t._M_impl._MKeyCompare);

			_Alloc_traits::_S_on_swap(_M_get_Node_allocator(),
				t._M_get_Node_allocator());
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		pair<typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::_Base_ptr,
	 typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::_Base_ptr>
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_get_insert_unique_pos(const key_type& k)
		{
			typedef pair<_Base_ptr, _Base_ptr> _Res;
			_Link_type x = _M_begin();
			_Base_ptr y = _M_end();
			bool comp = true;
			while (x != 0)
	{
		y = x;
		comp = _M_impl._MKeyCompare(k, _SKey(x));
		x = comp ? _S_left(x) : _S_right(x);
	}
			iterator j = iterator(y);
			if (comp)
	{
		if (j == begin())
			return _Res(x, y);
		else
			--j;
	}
			if (_M_impl._MKeyCompare(_SKey(j._M_node), k))
	return _Res(x, y);
			return _Res(j._M_node, 0);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		pair<typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::_Base_ptr,
	 typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::_Base_ptr>
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_get_insert_equal_pos(const key_type& k)
		{
			typedef pair<_Base_ptr, _Base_ptr> _Res;
			_Link_type x = _M_begin();
			_Base_ptr y = _M_end();
			while (x != 0)
	{
		y = x;
		x = _M_impl._MKeyCompare(k, _SKey(x)) ?
					_S_left(x) : _S_right(x);
	}
			return _Res(x, y);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		pair<typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::iterator, bool>
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_insert_unique(const Val& v)
		{
			typedef pair<iterator, bool> _Res;
			pair<_Base_ptr, _Base_ptr> res
	= _M_get_insert_unique_pos(KeyOfValue()(v));

			if (res.second)
	{
		_Alloc_node an(*this);
		return _Res(_M_insert_(res.first, res.second,
				 v, an),
					true);
	}

			return _Res(iterator(res.first), false);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::iterator
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_insert_equal(const Val& v)
		{
			pair<_Base_ptr, _Base_ptr> res
	= _M_get_insert_equal_pos(KeyOfValue()(v));
			_Alloc_node an(*this);
			return _M_insert_(res.first, res.second,
			v, an);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		pair<typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::_Base_ptr,
				 typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::_Base_ptr>
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_get_insert_hint_unique_pos(const_iterator position,
					const key_type& k)
		{
			iterator pos = position._M_const_cast();
			typedef pair<_Base_ptr, _Base_ptr> _Res;

			// end()
			if (pos._M_node == _M_end())
	{
		if (size() > 0
				&& _M_impl._MKeyCompare(_SKey(_M_rightmost()), k))
			return _Res(0, _M_rightmost());
		else
			return _M_get_insert_unique_pos(k);
	}
			else if (_M_impl._MKeyCompare(k, _SKey(pos._M_node)))
	{
		// First, try before...
		iterator before = pos;
		if (pos._M_node == _M_leftmost()) // begin()
			return _Res(_M_leftmost(), _M_leftmost());
		else if (_M_impl._MKeyCompare(_SKey((--before)._M_node), k))
			{
				if (_S_right(before._M_node) == 0)
		return _Res(0, before._M_node);
				else
		return _Res(pos._M_node, pos._M_node);
			}
		else
			return _M_get_insert_unique_pos(k);
	}
			else if (_M_impl._MKeyCompare(_SKey(pos._M_node), k))
	{
		// ... then try after.
		iterator after = pos;
		if (pos._M_node == _M_rightmost())
			return _Res(0, _M_rightmost());
		else if (_M_impl._MKeyCompare(k, _SKey((++after)._M_node)))
			{
				if (_S_right(pos._M_node) == 0)
		return _Res(0, pos._M_node);
				else
		return _Res(after._M_node, after._M_node);
			}
		else
			return _M_get_insert_unique_pos(k);
	}
			else
	// Equivalent keys.
	return _Res(pos._M_node, 0);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		template<typename _NodeGen>
			typename _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::iterator
			_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
			_M_insert_unique_(const_iterator position,
			const Val& v,
			_NodeGen& node_gen)
		{
			pair<_Base_ptr, _Base_ptr> res
	= _M_get_insert_hint_unique_pos(position, KeyOfValue()(v));

			if (res.second)
	return _M_insert_(res.first, res.second,
				v,
				node_gen);
			return iterator(res.first);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		pair<typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::_Base_ptr,
				 typename _bin_tree<Key, Val, KeyOfValue,
				 Compare, _Alloc>::_Base_ptr>
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_get_insert_hint_equal_pos(const_iterator position, const key_type& k)
		{
			iterator pos = position._M_const_cast();
			typedef pair<_Base_ptr, _Base_ptr> _Res;

			// end()
			if (pos._M_node == _M_end())
	{
		if (size() > 0
				&& !_M_impl._MKeyCompare(k, _SKey(_M_rightmost())))
			return _Res(0, _M_rightmost());
		else
			return _M_get_insert_equal_pos(k);
	}
			else if (!_M_impl._MKeyCompare(_SKey(pos._M_node), k))
	{
		// First, try before...
		iterator before = pos;
		if (pos._M_node == _M_leftmost()) // begin()
			return _Res(_M_leftmost(), _M_leftmost());
		else if (!_M_impl._MKeyCompare(k, _SKey((--before)._M_node)))
			{
				if (_S_right(before._M_node) == 0)
		return _Res(0, before._M_node);
				else
		return _Res(pos._M_node, pos._M_node);
			}
		else
			return _M_get_insert_equal_pos(k);
	}
			else
	{
		// ... then try after.	
		iterator after = pos;
		if (pos._M_node == _M_rightmost())
			return _Res(0, _M_rightmost());
		else if (!_M_impl._MKeyCompare(_SKey((++after)._M_node), k))
			{
				if (_S_right(pos._M_node) == 0)
		return _Res(0, pos._M_node);
				else
		return _Res(after._M_node, after._M_node);
			}
		else
			return _Res(0, 0);
	}
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		template<typename _NodeGen>
			typename _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::iterator
			_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
			_M_insert_equal_(const_iterator position,
					 const Val& v,
					 _NodeGen& node_gen)
			{
	pair<_Base_ptr, _Base_ptr> res
		= _M_get_insert_hint_equal_pos(position, KeyOfValue()(v));

	if (res.second)
		return _M_insert_(res.first, res.second,
					v,
					node_gen);

	return _M_insert_equal_lower(v);
			}

	template<typename Key, typename Val, typename _KoV,
					 typename _Cmp, typename _Alloc>
		template<class _II>
			void
			_bin_tree<Key, Val, _KoV, _Cmp, _Alloc>::
			_M_insert_unique(_II first, _II last)
			{
	_Alloc_node an(*this);
	for (; first != last; ++first)
		_M_insert_unique_(end(), *first, an);
			}

	template<typename Key, typename Val, typename _KoV,
					 typename _Cmp, typename _Alloc>
		template<class _II>
			void
			_bin_tree<Key, Val, _KoV, _Cmp, _Alloc>::
			_M_insert_equal(_II first, _II last)
			{
	_Alloc_node an(*this);
	for (; first != last; ++first)
		_M_insert_equal_(end(), *first, an);
			}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		void
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_erase_aux(const_iterator position)
		{
			_Link_type y =
	static_cast<_Link_type>(_bin_tree_rebalance_for_erase
				(const_cast<_Base_ptr>(position._M_node),
				 this->_M_impl._M_header));
			_M_drop_node(y);
			--_M_impl._M_node_count;
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		void
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		_M_erase_aux(const_iterator first, const_iterator last)
		{
			if (first == begin() && last == end())
	clear();
			else
	while (first != last)
		erase(first++);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::size_type
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		erase(const Key& x)
		{
			pair<iterator, iterator> p = equal_range(x);
			const size_type old_size = size();
			erase(p.first, p.second);
			return old_size - size();
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		void
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		erase(const Key* first, const Key* last)
		{
			while (first != last)
	erase(*first++);
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue,
					Compare, _Alloc>::iterator
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		find(const Key& k)
		{
			iterator j = _M_lower_bound(_M_begin(), _M_end(), k);
			return (j == end()
				|| _M_impl._MKeyCompare(k,
					_SKey(j._M_node))) ? end() : j;
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue,
					Compare, _Alloc>::const_iterator
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		find(const Key& k) const
		{
			const_iterator j = _M_lower_bound(_M_begin(), _M_end(), k);
			return (j == end()
				|| _M_impl._MKeyCompare(k, 
					_SKey(j._M_node))) ? end() : j;
		}

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		typename _bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::size_type
		_bin_tree<Key, Val, KeyOfValue, Compare, _Alloc>::
		count(const Key& k) const
		{
			pair<const_iterator, const_iterator> p = equal_range(k);
			const size_type n = std::distance(p.first, p.second);
			return n;
		}

	unsigned int
	_bin_tree_black_count(const _bin_tree_node_base* node,
											 const _bin_tree_node_base* root) throw ();

	template<typename Key, typename Val, typename KeyOfValue,
					 typename Compare, typename _Alloc>
		bool
		_bin_tree<Key,Val,KeyOfValue,Compare,_Alloc>::rb_verify() const
		{
			if (_M_impl._M_node_count == 0 || begin() == end())
	return _M_impl._M_node_count == 0 && begin() == end()
				 && this->_M_impl._M_header._M_left == _M_end()
				 && this->_M_impl._M_header._M_right == _M_end();

			unsigned int len = _bin_tree_black_count(_M_leftmost(), _M_root());
			for (const_iterator it = begin(); it != end(); ++it)
	{
		_Const_Link_type x = static_cast<_Const_Link_type>(it._M_node);
		_Const_Link_type L = _S_left(x);
		_Const_Link_type R = _S_right(x);

		if (x->_M_color == _S_red)
			if ((L && L->_M_color == _S_red)
		|| (R && R->_M_color == _S_red))
				return false;

		if (L && _M_impl._MKeyCompare(_SKey(x), _SKey(L)))
			return false;
		if (R && _M_impl._MKeyCompare(_SKey(R), _SKey(x)))
			return false;

		if (!L && !R && _bin_tree_black_count(x, _M_root()) != len)
			return false;
	}

			if (_M_leftmost() != _bin_tree_node_base::_S_minimum(_M_root()))
	return false;
			if (_M_rightmost() != _bin_tree_node_base::_S_maximum(_M_root()))
	return false;
			return true;
		}

}

#endif

#include "tree.cc"
