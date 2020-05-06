
#ifndef LIST_HPP
# define LIST_HPP

# include "utils.hpp"

namespace	ft
{
	namespace	__detail
	{
		struct _List_node_base
		{
			_List_node_base*	_M_next;
			_List_node_base*	_M_prev;

			static void
			swap(_List_node_base& __x, _List_node_base& __y)
			{
				if (__x._M_next != &__x)
				{
					if (__y._M_next != &__y)
						{
							ft::swap(__x._M_next,__y._M_next);
							ft::swap(__x._M_prev,__y._M_prev);
							__x._M_next->_M_prev = __x._M_prev->_M_next = &__x;
							__y._M_next->_M_prev = __y._M_prev->_M_next = &__y;
						}
					else
						{
							__y._M_next = __x._M_next;
							__y._M_prev = __x._M_prev;
							__y._M_next->_M_prev = __y._M_prev->_M_next = &__y;
							__x._M_next = __x._M_prev = &__x;
						}
				}
				else if ( __y._M_next != &__y )
				{
					__x._M_next = __y._M_next;
					__x._M_prev = __y._M_prev;
					__x._M_next->_M_prev = __x._M_prev->_M_next = &__x;
					__y._M_next = __y._M_prev = &__y;
				}
			}

			void
			_M_transfer(_List_node_base* const __first,
						_List_node_base* const __last)
			{
				if (this != __last)
				{
					// Remove [first, last) from its old position.
					__last->_M_prev->_M_next	= this;
					__first->_M_prev->_M_next = __last;
					this->_M_prev->_M_next		= __first;

					// Splice [first, last) into its new position.
					_List_node_base* const __tmp = this->_M_prev;
					this->_M_prev								= __last->_M_prev;
					__last->_M_prev							= __first->_M_prev;
					__first->_M_prev						 = __tmp;
				}
			}

			void
			_M_reverse(void)
			{
				_List_node_base* __tmp = this;
				do
				{
					std::swap(__tmp->_M_next, __tmp->_M_prev);

					// Old next node is now prev.
					__tmp = __tmp->_M_prev;
				}
				while (__tmp != this);
			}

			void
			_M_hook(_List_node_base* const __position)
			{
				this->_M_next = __position;
				this->_M_prev = __position->_M_prev;
				__position->_M_prev->_M_next = this;
				__position->_M_prev = this;
			}

			void
			_M_unhook(void)
			{
				_List_node_base* const __next_node = this->_M_next;
				_List_node_base* const __prev_node = this->_M_prev;
				__prev_node->_M_next = __next_node;
				__next_node->_M_prev = __prev_node;
			}
		};
	}

	template <typename _Tp>
		struct _List_node : public __detail::_List_node_base
		{
			_Tp		_M_data;

			_Tp*
			_M_valptr(void)
			{
				return std::__addressof(_M_data);
			}

			_Tp const*
			_M_valptr(void) const
			{
				return std::__addressof(_M_data);
			}
		};

	template<typename _Tp>
		struct _List_iterator
		{
			typedef _List_iterator<_Tp>				_Self;
			typedef _List_node<_Tp>					_Node;

			typedef __gnu_cxx::ptrdiff_t						difference_type;
			typedef ft::bidirectional_iterator_tag	iterator_category;
			typedef _Tp								value_type;
			typedef _Tp*							pointer;
			typedef _Tp&							reference;

			__detail::_List_node_base*	_M_node;

			_List_iterator() : _M_node() {}

			explicit
			_List_iterator(__detail::_List_node_base* __x)
			: _M_node(__x)
			{}

			_Self
			_M_const_cast(void) const
			{
				return (*this);
			}

			reference
			operator*	(void) const
			{
				return (*static_cast<_Node*>(_M_node)->_M_valptr());
			}

			pointer
			operator->	(void) const
			{
				return (static_cast<_Node*>(_M_node)->_M_valptr());
			}

			_Self&
			operator++	(void)
			{
				_M_node = _M_node->_M_next;
				return (*this);
			}

			_Self
			operator++	(int)
			{
				_Self	__tmp;
				
				__tmp = *this;
				_M_node = _M_node->_M_next;
				return (__tmp);
			}

			_Self&
			operator--	(void)
			{
				_M_node = _M_node->_M_prev;
				return (*this);
			}

			_Self
			operator--	(int)
			{
				_Self	__tmp;
				
				__tmp = *this;
				_M_node = _M_node->_M_prev;
				return (__tmp);
			}

			bool
			operator==	(const _Self& __x) const
			{
				return (_M_node == __x._M_node);
			}

			bool
			operator!=	(const _Self& __x) const
			{
				return (_M_node != __x._M_node);
			}
		};

	template<typename _Tp>
		struct _List_const_iterator
		{
			typedef _List_const_iterator<_Tp>		_Self;
			typedef const _List_node<_Tp>			_Node;
			typedef _List_iterator<_Tp>				iterator;

			typedef __gnu_cxx::ptrdiff_t						difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef _Tp								value_type;
			typedef const _Tp*						pointer;
			typedef const _Tp&						reference;

			const __detail::_List_node_base*	_M_node;

			_List_const_iterator() : _M_node() {}

			explicit
			_List_const_iterator(const __detail::_List_node_base* __x)
			: _M_node(__x)
			{}

			_List_const_iterator(const iterator& __x)
			: _M_node(__x._M_node)
			{}

			iterator
			_M_const_cast(void) const
			{
				return (iterator(const_cast<__detail::_List_node_base*>(_M_node)));
			}

			reference
			operator*	(void) const
			{
				return (*(static_cast<_Node*>(_M_node)->_M_valptr()));
			}

			pointer
			operator->	(void) const
			{
				return (static_cast<_Node*>(_M_node)->_M_valptr());
			}

			_Self&
			operator++	(void)
			{
				_M_node = _M_node->_M_next;
				return (*this);
			}

			_Self
			operator++	(int)
			{
				_Self	__tmp;

				__tmp = *this;
				_M_node = _M_node->_M_next;
				return (__tmp);
			}

			_Self&
			operator--	(void)
			{
				_M_node = _M_node->_M_prev;
				return (*this);
			}

			_Self
			operator--	(int)
			{
				_Self	__tmp;
				
				__tmp = *this;
				_M_node = _M_node->_M_prev;
				return (__tmp);
			}

			bool
			operator==	(const _Self& __x) const
			{
				return (_M_node == __x._M_node);
			}

			bool
			operator!=	(const _Self& __x) const
			{
				return (_M_node != __x._M_node);
			}
		};

	template <typename _Tp, typename _Alloc>
		class _List_base
		{
			protected:
				typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
					rebind<_Tp>::other								_Tp_alloc_type;
				typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>	_Tp_alloc_traits;
				typedef typename _Tp_alloc_traits::template
					rebind<_List_node<_Tp> >::other					_Node_alloc_type;
				typedef __gnu_cxx::__alloc_traits<_Node_alloc_type> _Node_alloc_traits;

				static size_t
				_S_distance(const __detail::_List_node_base* __first,
				const __detail::_List_node_base* __last)
				{
					size_t __n = 0;
					while (__first != __last)
					{
						__first = __first->_M_next;
						++__n;
					}
					return (__n);
				}

				__detail::_List_node_base _M_node;

				struct _List_impl
				: public _Node_alloc_type
				{
					__detail::_List_node_base _M_node;

					_List_impl(void)
					: _Node_alloc_type(), _M_node()
					{}

					_List_impl(const _Node_alloc_type& __a)
					: _Node_alloc_type(__a), _M_node()
					{}
				};

				_List_impl	_M_impl;
				
				size_t _M_node_count() const
				{
					return _S_distance(_M_impl._M_node._M_next,
					std::__addressof(_M_impl._M_node));
				}

				typename _Node_alloc_traits::pointer
				_M_get_node(void)
				{
					return (_Node_alloc_traits::allocate(_M_impl, 1));
				}

				void
				_M_put_node(typename _Node_alloc_traits::pointer __p)
				{
					_Node_alloc_traits::deallocate(_M_impl, __p, 1);
				}

				_Node_alloc_type&
				_M_get_Node_allocator(void)
				{
					return (_M_impl);
				}

				const _Node_alloc_type&
				_M_get_Node_allocator(void) const
				{
					return (_M_impl);
				}

			public:
				_List_base()
				: _M_impl()
				{
					_M_init();
				}

				_List_base(const _Node_alloc_type& __a) _GLIBCXX_NOEXCEPT
				: _M_impl(__a)
				{
					_M_init();
				}

				~_List_base(void)
				{
					// clear();
				}

				void
				_M_init() _GLIBCXX_NOEXCEPT
				{
					this->_M_impl._M_node._M_next = &this->_M_impl._M_node;
					this->_M_impl._M_node._M_prev = &this->_M_impl._M_node;
				}
		};

	template<typename _Val>
		inline bool
		operator==	(const _List_iterator<_Val>& __x,
				 	const _List_const_iterator<_Val>& __y)
		{
			return (__x._M_node == __y._M_node);
		}

	template<typename _Val>
		inline bool
		operator!=	(const _List_iterator<_Val>& __x,
				 const _List_const_iterator<_Val>& __y)
		{
			return (__x._M_node != __y._M_node);
		}

//	template <class T, class Alloc>
	template <typename T, typename Alloc = std::allocator<T> >
	class	list : public _List_base<T, Alloc>
	{
		public:
			typedef T											value_type;
			typedef std::allocator<value_type>					allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::_List_iterator<T>						iterator;
			typedef ft::_List_const_iterator<const T>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;


			explicit list (const allocator_type& alloc = allocator_type());
			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <typename InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			list (const list& x);

			~list(void);

			list& operator= (const list& x);

			iterator begin(void);
			const_iterator begin(void) const;

			iterator end(void);
			const_iterator end(void) const;

			reverse_iterator rbegin(void);
			const_reverse_iterator rbegin(void) const;

			reverse_iterator rend(void);
			const_reverse_iterator rend(void) const;

			bool empty(void) const;

			size_type size(void) const;

			size_type max_size(void) const;

			reference front(void);
			const_reference front(void) const;

			reference back(void);
			const_reference back(void) const;

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last);
			void assign (size_type n, const value_type& val);

			void push_front (const value_type& val);

			void pop_front (void);

			void push_back (const value_type& val);

			void pop_back (void);

			iterator insert (iterator position, const value_type& val);
			void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);

			void swap (list& x);

			void resize (size_type n, value_type val = value_type());

			void clear(void);

			void splice (iterator position, list& x);
			void splice (iterator position, list& x, iterator i);
			void splice (iterator position, list& x, iterator first, iterator last);

			void remove (const value_type& val);

			template <class Predicate>
			void remove_if (Predicate pred);
			
			void unique(void);
			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred);

			void merge (list& x);
			template <class Compare>
			void merge (list& x, Compare comp);

			void sort(void);
			template <class Compare>
			void sort (Compare comp);

			void reverse(void);

			void swap (list<T,Alloc>& x, list<T,Alloc>& y);

		private:
			typedef _List_base<T, Alloc>				_Base;
			typedef typename _Base::_Tp_alloc_type		_Tp_alloc_type;
			typedef typename _Base::_Tp_alloc_traits	_Tp_alloc_traits;
			typedef typename _Base::_Node_alloc_type	_Node_alloc_type;
			typedef typename _Base::_Node_alloc_traits	_Node_alloc_traits;

		protected:
			// Note that pointers-to-_Node's can be ctor-converted to
			// iterator types.
			typedef _List_node<T>				 _Node;

			using _Base::_M_impl;
			using _Base::_M_put_node;
			using _Base::_M_get_node;
			using _Base::_M_get_Node_allocator;

			/**
			 *	@param	__args	An instance of user data.
			 *
			 *	Allocates space for a new node and constructs a copy of
			 *	@a __args in it.
			 */
			_Node*
			_M_create_node(const value_type& __x)
			{
				_Node* __p = this->_M_get_node();
				try
				{
					_Tp_alloc_type __alloc(_M_get_Node_allocator());
					__alloc.construct(__p->_M_valptr(), __x);
				}
				catch(std::exception& e)
				{
					_M_put_node(__p);
					throw;
				}
				return (__p);
			}

			void
			_M_insert(iterator __position, const value_type& __x)
			{
				_Node* __tmp = _M_create_node(__x);
				__tmp->_M_hook(__position._M_node);
			}

			void
			_M_erase(iterator __position) _GLIBCXX_NOEXCEPT
			{
				__position._M_node->_M_unhook();
				_Node* __n = static_cast<_Node*>(__position._M_node);
				_Tp_alloc_type(_M_get_Node_allocator()).destroy(__n->_M_valptr());
				_M_put_node(__n);
			}

			void
			_M_init(size_type n, const value_type& val, std::__true_type)
			{
				for (; n; --n)
					push_back(val);
			}

			template <typename InputIterator>
			void
			_M_init(InputIterator first, InputIterator last, std::__false_type)
			{
				for (;first != last;++first)
					push_back(*first);
			}

			void
			_M_fill(size_type n, const value_type& val)
			{
				iterator	it;

				it = begin();
				for (; it != end() && n > 0; ++it, --n)
					*it = val;
				if (n > 0)
					insert(end(), n, val);
				else
					erase(it, end());
			}
	};

	template <class T, class Alloc>
	inline bool
	operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

	template <class T, class Alloc>
	inline bool
	operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

	template <class T, class Alloc>
	inline bool
	operator<	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

	template <class T, class Alloc>
	inline bool
	operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

	template <class T, class Alloc>
	inline bool
	operator>	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

	template <class T, class Alloc>
	inline bool
	operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

	template<class T, class Alloc>
	inline void
	swap(list<T, Alloc>& x, list<T, Alloc>& y)
	{
		x.swap(y);
	}


	template <typename T, typename Alloc>
	list<T, Alloc>::list (const allocator_type& alloc)
	: _Base(alloc)
	{}

	template <typename T, typename Alloc>
	list<T, Alloc>::list (size_type n, const value_type& val, const allocator_type& alloc)
	: _Base(alloc)
	{
		_M_init(n, val, std::__true_type());
	}

	template <typename T, typename Alloc>
	template <typename InputIterator>
	list<T, Alloc>::list (InputIterator first, InputIterator last, const allocator_type& alloc)
	: _Base(_Node_alloc_type(alloc))
	{
		typedef typename std::__is_integer<InputIterator>::__type _Integral;
		_M_init(first, last, _Integral());
	}

	template <typename T, typename Alloc>
	list<T, Alloc>::list (const list& src)
	: _Base(_Node_alloc_traits::
		_S_select_on_copy(src._M_get_Node_allocator()))
	{
		_M_init(src.begin(), src.end(), std::__false_type());
	}

	template <typename T, typename Alloc>
	list<T, Alloc>::~list (void)
	{}

	template <typename T, typename Alloc>
	list<T, Alloc>&
	list<T, Alloc>::operator=	(const list& rhs)
	{
		if (this != std::__addressof(rhs))
			_M_init(rhs.begin(), rhs.end(), std::__false_type());
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::iterator
	list<T, Alloc>::begin (void)
	{
		return (iterator(this->_M_impl._M_node._M_next));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_iterator
	list<T, Alloc>::begin(void) const
	{
		return (const_iterator(this->_M_impl._M_node._M_next));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::iterator
	list<T, Alloc>::end (void)
	{
		return (iterator(&this->_M_impl._M_node));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_iterator
	list<T, Alloc>::end(void) const
	{
		return (const_iterator(&this->_M_impl._M_node));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::reverse_iterator
	list<T, Alloc>::rbegin (void)
	{
		return (reverse_iterator(this->end()));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_reverse_iterator
	list<T, Alloc>::rbegin(void) const
	{
		return (const_reverse_iterator(this->end()));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::reverse_iterator
	list<T, Alloc>::rend (void)
	{
		return (reverse_iterator(this->start()));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_reverse_iterator
	list<T, Alloc>::rend(void) const
	{
		return (const_reverse_iterator(this->start()));
	}

	template <typename T, typename Alloc>
	bool
	list<T, Alloc>::empty(void) const
	{
		return (this->_M_impl._M_node._M_next == &this->_M_impl._M_node);
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::size_type
	list<T, Alloc>::size(void) const
	{
		return (this->_M_node_count());
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::size_type
	list<T, Alloc>::max_size(void) const
	{
		return (_Node_alloc_traits::max_size(_M_get_Node_allocator()));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::reference
	list<T, Alloc>::front(void)
	{
		return (*begin());
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_reference
	list<T, Alloc>::front(void) const
	{
		return (*begin());
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::reference
	list<T, Alloc>::back(void)
	{
		iterator __tmp = end();
		--__tmp;
		return *__tmp;
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_reference
	list<T, Alloc>::back(void) const
	{
		iterator __tmp = end();
		--__tmp;
		return *__tmp;
	}

	template <typename T, typename Alloc>
	template <class InputIterator>
	void
	list<T, Alloc>::assign (InputIterator first, InputIterator last)
	{
		_M_init(first, last, std::__false_type());
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::assign (size_type n, const value_type& val)
	{
		_M_fill(n, val);
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::push_front (const value_type& val)
	{
		this->_M_insert(begin(), val);
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::pop_front (void)
	{
		this->_M_erase(begin());
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::push_back (const value_type& val)
	{
		this->_M_insert(end(), val);
	}

	template <typename T, typename Alloc>
	void
	list<T, Alloc>::pop_back (void)
	{	
		this->_M_erase(iterator(this->_M_impl._M_node._M_prev));
	}
}

#endif
