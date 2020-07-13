/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: YanYan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:24:54 by YanYan            #+#    #+#             */
/*   Updated: 2020/07/13 22:24:55 by YanYan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
# define DEQUE_HPP

# include "utils.hpp"

namespace ft
{
	template<typename _Tp, typename _Ref, typename _Ptr>
		struct _Deque_iterator
		{
			typedef _Deque_iterator<_Tp, _Tp&, _Tp*>				iterator;
			typedef _Deque_iterator<_Tp, const _Tp&, const _Tp*>	const_iterator;
			typedef _Tp*											_Elt_pointer;
			typedef _Tp**											_Map_pointer;

			static size_t _S_buffer_size()
			{
				return (deque_buf_size(sizeof(_Tp)));
			}

			typedef ft::random_access_iterator_tag	iterator_category;
			typedef _Tp								value_type;
			typedef _Ptr							pointer;
			typedef _Ref							reference;
			typedef size_t							size_type;
			typedef ptrdiff_t						 difference_type;
			typedef _Deque_iterator					_Self;

			_Elt_pointer	_M_cur;
			_Elt_pointer	_M_first;
			_Elt_pointer	_M_last;
			_Map_pointer	_M_node;

			_Deque_iterator(_Elt_pointer x, _Map_pointer y)
			: _M_cur(x), _M_first(*y),
				_M_last(*y + _S_buffer_size()), _M_node(y)
			{}

			_Deque_iterator()
			: _M_cur(), _M_first(), _M_last(), _M_node()
			{}

			_Deque_iterator(const iterator& x)
			: _M_cur(x._M_cur), _M_first(x._M_first),
				_M_last(x._M_last), _M_node(x._M_node)
			{}

			iterator
			_M_const_cast() const
			{
				return (iterator(_M_cur, _M_node));
			}

			reference
			operator*() const
			{
				return (*_M_cur);
			}

			pointer
			operator->() const
			{
				return (_M_cur);
			}

			_Self&
			operator++()
			{
				++_M_cur;
				if (_M_cur == _M_last)
				{
					_M_set_node(_M_node + 1);
					_M_cur = _M_first;
				}
				return (*this);
			}

			_Self
			operator++(int)
			{
				_Self tmp = *this;
				++*this;
				return (tmp);
			}

			_Self&
			operator--()
			{
				if (_M_cur == _M_first)
				{
					_M_set_node(_M_node - 1);
					_M_cur = _M_last;
				}
				--_M_cur;
				return (*this);
			}

			_Self
			operator--(int)
			{
				_Self tmp = *this;
				--*this;
				return (tmp);
			}

			_Self&
			operator+=(difference_type n)
			{
				const difference_type offset = n + (_M_cur - _M_first);
				if (offset >= 0 && offset < difference_type(_S_buffer_size()))
					_M_cur += n;
				else
				{
					const difference_type node_offset =
						offset > 0 ? offset / difference_type(_S_buffer_size())
												 : -difference_type((-offset - 1)
										/ _S_buffer_size()) - 1;
					_M_set_node(_M_node + node_offset);
					_M_cur = _M_first + (offset - node_offset
						 * difference_type(_S_buffer_size()));
				}
				return (*this);
			}

			_Self
			operator+(difference_type n) const
			{
				_Self tmp = *this;
				return (tmp += n);
			}

			_Self&
			operator-=(difference_type n)
			{
				return (*this += -n);
			}

			_Self
			operator-(difference_type n) const
			{
				_Self tmp = *this;
				return (tmp -= n);
			}

			reference
			operator[](difference_type n) const
			{
				return (*(*this + n));
			}

			void
			_M_set_node(_Map_pointer new_node)
			{
				_M_node = new_node;
				_M_first = *new_node;
				_M_last = _M_first + difference_type(_S_buffer_size());
			}
		};

	template<typename _Tp, typename _Ref, typename _Ptr>
		inline bool
		operator==(const _Deque_iterator<_Tp, _Ref, _Ptr>& x,
				 const _Deque_iterator<_Tp, _Ref, _Ptr>& y)
		{
			return (x._M_cur == y._M_cur);
		}

	template<typename _Tp, typename _RefL, typename _PtrL,
		 typename _RefR, typename _PtrR>
		inline bool
		operator==(const _Deque_iterator<_Tp, _RefL, _PtrL>& x,
				 const _Deque_iterator<_Tp, _RefR, _PtrR>& y)
		{
			return (x._M_cur == y._M_cur);
		}

	template<typename _Tp, typename _Ref, typename _Ptr>
		inline bool
		operator!=(const _Deque_iterator<_Tp, _Ref, _Ptr>& x,
				 const _Deque_iterator<_Tp, _Ref, _Ptr>& y)
		{
			return (!(x == y));
		}

	template<typename _Tp, typename _RefL, typename _PtrL,
			typename _RefR, typename _PtrR>
		inline bool
		operator!=(const _Deque_iterator<_Tp, _RefL, _PtrL>& x,
				 const _Deque_iterator<_Tp, _RefR, _PtrR>& y)
		{
			return (!(x == y));
		}

	template<typename _Tp, typename _Ref, typename _Ptr>
		inline bool
		operator<(const _Deque_iterator<_Tp, _Ref, _Ptr>& x,
				const _Deque_iterator<_Tp, _Ref, _Ptr>& y)
		{
			return ((x._M_node == y._M_node) ? (x._M_cur < y._M_cur) : (x._M_node < y._M_node));
		}

	template<typename _Tp, typename _RefL, typename _PtrL,
		 typename _RefR, typename _PtrR>
		inline bool
		operator<(const _Deque_iterator<_Tp, _RefL, _PtrL>& x,
				const _Deque_iterator<_Tp, _RefR, _PtrR>& y)
		{
			return ((x._M_node == y._M_node) ? (x._M_cur < y._M_cur) : (x._M_node < y._M_node));
		}

	template<typename _Tp, typename _Ref, typename _Ptr>
		inline bool
		operator>(const _Deque_iterator<_Tp, _Ref, _Ptr>& x,
				const _Deque_iterator<_Tp, _Ref, _Ptr>& y)
		{
			return (y < x);
		}

	template<typename _Tp, typename _RefL, typename _PtrL,
		 typename _RefR, typename _PtrR>
		inline bool
		operator>(const _Deque_iterator<_Tp, _RefL, _PtrL>& x,
				const _Deque_iterator<_Tp, _RefR, _PtrR>& y)
		{
			return (y < x);
		}

	template<typename _Tp, typename _Ref, typename _Ptr>
		inline bool
		operator<=(const _Deque_iterator<_Tp, _Ref, _Ptr>& x,
				 const _Deque_iterator<_Tp, _Ref, _Ptr>& y)
		{
			return (!(y < x));
		}

	template<typename _Tp, typename _RefL, typename _PtrL,
		 typename _RefR, typename _PtrR>
		inline bool
		operator<=(const _Deque_iterator<_Tp, _RefL, _PtrL>& x,
				 const _Deque_iterator<_Tp, _RefR, _PtrR>& y)
		{
			return (!(y < x));
		}

	template<typename _Tp, typename _Ref, typename _Ptr>
		inline bool
		operator>=(const _Deque_iterator<_Tp, _Ref, _Ptr>& x,
				 const _Deque_iterator<_Tp, _Ref, _Ptr>& y)
		{
			return (!(x < y));
		}

	template<typename _Tp, typename _RefL, typename _PtrL,
		 typename _RefR, typename _PtrR>
		inline bool
		operator>=(const _Deque_iterator<_Tp, _RefL, _PtrL>& x,
				 const _Deque_iterator<_Tp, _RefR, _PtrR>& y)
		{
			return (!(x < y));
		}

	template<typename _Tp, typename _Ref, typename _Ptr>
		inline typename _Deque_iterator<_Tp, _Ref, _Ptr>::difference_type
		operator-(const _Deque_iterator<_Tp, _Ref, _Ptr>& x,
				const _Deque_iterator<_Tp, _Ref, _Ptr>& y)
		{
			return( typename _Deque_iterator<_Tp, _Ref, _Ptr>::difference_type
				(_Deque_iterator<_Tp, _Ref, _Ptr>::_S_buffer_size())
				* (x._M_node - y._M_node - 1) + (x._M_cur - x._M_first)
				+ (y._M_last - y._M_cur));
		}

	template<typename _Tp, typename _RefL, typename _PtrL,
		 typename _RefR, typename _PtrR>
		inline typename _Deque_iterator<_Tp, _RefL, _PtrL>::difference_type
		operator-(const _Deque_iterator<_Tp, _RefL, _PtrL>& x,
				const _Deque_iterator<_Tp, _RefR, _PtrR>& y)
		{
			return (typename _Deque_iterator<_Tp, _RefL, _PtrL>::difference_type
				(_Deque_iterator<_Tp, _RefL, _PtrL>::_S_buffer_size())
				* (x._M_node - y._M_node - 1) + (x._M_cur - x._M_first)
				+ (y._M_last - y._M_cur));
		}

	template<typename _Tp, typename _Ref, typename _Ptr>
		inline _Deque_iterator<_Tp, _Ref, _Ptr>
		operator+(ptrdiff_t n, const _Deque_iterator<_Tp, _Ref, _Ptr>& x)
		{
			return (x + n);
		}

	template<typename _Tp>
		void
		fill(const _Deque_iterator<_Tp, _Tp&, _Tp*>&,
	 const _Deque_iterator<_Tp, _Tp&, _Tp*>&, const _Tp&);

	template<typename _Tp>
		_Deque_iterator<_Tp, _Tp&, _Tp*>
		copy(_Deque_iterator<_Tp, const _Tp&, const _Tp*>,
	 _Deque_iterator<_Tp, const _Tp&, const _Tp*>,
	 _Deque_iterator<_Tp, _Tp&, _Tp*>);

	template<typename _Tp>
		inline _Deque_iterator<_Tp, _Tp&, _Tp*>
		copy(_Deque_iterator<_Tp, _Tp&, _Tp*> first,
	 _Deque_iterator<_Tp, _Tp&, _Tp*> last,
	 _Deque_iterator<_Tp, _Tp&, _Tp*> result)
		{
			return (ft::copy(_Deque_iterator<_Tp, const _Tp&, const _Tp*>(first),
					 _Deque_iterator<_Tp, const _Tp&, const _Tp*>(last),
					 result));
		}

	template<typename _Tp>
		_Deque_iterator<_Tp, _Tp&, _Tp*>
		copy_backward(_Deque_iterator<_Tp, const _Tp&, const _Tp*>,
			_Deque_iterator<_Tp, const _Tp&, const _Tp*>,
			_Deque_iterator<_Tp, _Tp&, _Tp*>);

	template<typename _Tp>
		inline _Deque_iterator<_Tp, _Tp&, _Tp*>
		copy_backward(_Deque_iterator<_Tp, _Tp&, _Tp*> first,
			_Deque_iterator<_Tp, _Tp&, _Tp*> last,
			_Deque_iterator<_Tp, _Tp&, _Tp*> result)
		{
			return (ft::copy_backward(_Deque_iterator<_Tp,
				const _Tp&, const _Tp*>(first),
				_Deque_iterator<_Tp,
				const _Tp&, const _Tp*>(last),
				result));
		}

	template<typename _Tp, typename _Alloc>
		class _Deque_base
		{
			protected:
				typedef typename _Alloc::template
					rebind<_Tp>::other				_Tp_alloc_type;
				typedef _Tp_alloc_type				_Alloc_traits;

				typedef _Tp*					_Ptr;
				typedef const _Tp*				_Ptr_const;

				typedef typename _Alloc_traits::template rebind<_Ptr>::other
												_Map_alloc_type;
				typedef _Map_alloc_type			_Map_alloc_traits;

			public:
				typedef _Alloc								allocator_type;
				typedef typename _Alloc_traits::size_type	size_type;

				allocator_type
				get_allocator() const
				{
					return (allocator_type(_M_get_Tp_allocator()));
				}

				typedef _Deque_iterator<_Tp, _Tp&, _Ptr>				iterator;
				typedef _Deque_iterator<_Tp, const _Tp&, _Ptr_const>	const_iterator;

				_Deque_base()
				: _M_impl()
				{
					_M_initialize_map(0);
				}

				_Deque_base(size_t num_elements)
				: _M_impl()
				{
					_M_initialize_map(num_elements);
				}

				_Deque_base(const allocator_type& a, size_t num_elements)
				: _M_impl(a)
				{
					_M_initialize_map(num_elements);
				}

				_Deque_base(const allocator_type& a)
				: _M_impl(a)
				{}

				~_Deque_base();

			protected:
				typedef typename iterator::_Map_pointer _Map_pointer;

				struct _Deque_impl
				: public _Tp_alloc_type
				{
					_Map_pointer	_M_map;
					size_t			_M_map_size;
					iterator		_M_start;
					iterator		_M_finish;

					_Deque_impl()
					: _Tp_alloc_type(), _M_map(), _M_map_size(0),
						_M_start(), _M_finish()
					{}

					_Deque_impl(const _Tp_alloc_type& a)
					: _Tp_alloc_type(a), _M_map(), _M_map_size(0),
						_M_start(), _M_finish()
					{}

					void _M_swap_data(_Deque_impl& x)
					{
						using ft::swap;
						swap(this->_M_start, x._M_start);
						swap(this->_M_finish, x._M_finish);
						swap(this->_M_map, x._M_map);
						swap(this->_M_map_size, x._M_map_size);
					}
				};

				_Tp_alloc_type&
				_M_get_Tp_allocator()
				{
					return (*static_cast<_Tp_alloc_type*>(&this->_M_impl));
				}

				const _Tp_alloc_type&
				_M_get_Tp_allocator() const
				{
					return (*static_cast<const _Tp_alloc_type*>(&this->_M_impl));
				}

				_Map_alloc_type
				_M_get_map_allocator() const
				{
					return (_Map_alloc_type(_M_get_Tp_allocator()));
				}

				_Ptr
				_M_allocate_node()
				{ 
					typedef _Tp_alloc_type	_Traits;
					return (_Traits().allocate(deque_buf_size(sizeof(_Tp))));
				}

				void
				_M_deallocate_node(_Ptr p)
				{
					typedef _Tp_alloc_type	_Traits;
					_Traits().deallocate(p, deque_buf_size(sizeof(_Tp)));
				}

				_Map_pointer
				_M_allocate_map(size_t n)
				{
					_Map_alloc_type map_alloc = _M_get_map_allocator();
					return (_Map_alloc_traits().allocate(n));
				}

				void
				_M_deallocate_map(_Map_pointer p, size_t n)
				{
					_Map_alloc_type map_alloc = _M_get_map_allocator();
					_Map_alloc_traits().deallocate(p, n);
				}

			protected:
				void _M_initialize_map(size_t);
				void _M_create_nodes(_Map_pointer nstart, _Map_pointer nfinish);
				void _M_destroy_nodes(_Map_pointer nstart,
						_Map_pointer nfinish);
				enum { _S_initial_map_size = 8 };

				_Deque_impl		_M_impl;
		};

	template<typename _Tp, typename _Alloc>
		_Deque_base<_Tp, _Alloc>::
		~_Deque_base()
		{
			if (this->_M_impl._M_map)
			{
				_M_destroy_nodes(this->_M_impl._M_start._M_node,
						 this->_M_impl._M_finish._M_node + 1);
				_M_deallocate_map(this->_M_impl._M_map, this->_M_impl._M_map_size);
			}
		}

	template<typename _Tp, typename _Alloc>
		void
		_Deque_base<_Tp, _Alloc>::
		_M_initialize_map(size_t num_elements)
		{
			const size_t num_nodes = (num_elements/ deque_buf_size(sizeof(_Tp)) + 1);

			this->_M_impl._M_map_size = ft::max((size_t) _S_initial_map_size,
						 size_t(num_nodes + 2));
			this->_M_impl._M_map = _M_allocate_map(this->_M_impl._M_map_size);

			_Map_pointer nstart = (this->_M_impl._M_map
						 + (this->_M_impl._M_map_size - num_nodes) / 2);
			_Map_pointer nfinish = nstart + num_nodes;

			try
			{
				_M_create_nodes(nstart, nfinish);
			}
			catch(std::exception& e)
			{
				_M_deallocate_map(this->_M_impl._M_map, this->_M_impl._M_map_size);
				this->_M_impl._M_map = _Map_pointer();
				this->_M_impl._M_map_size = 0;
				throw;
			}

			this->_M_impl._M_start._M_set_node(nstart);
			this->_M_impl._M_finish._M_set_node(nfinish - 1);
			this->_M_impl._M_start._M_cur = _M_impl._M_start._M_first;
			this->_M_impl._M_finish._M_cur = (this->_M_impl._M_finish._M_first
					+ num_elements
					% deque_buf_size(sizeof(_Tp)));
		}

	template<typename _Tp, typename _Alloc>
		void
		_Deque_base<_Tp, _Alloc>::
		_M_create_nodes(_Map_pointer nstart, _Map_pointer nfinish)
		{
			_Map_pointer cur;
			try
			{
				for (cur = nstart; cur < nfinish; ++cur)
					*cur = this->_M_allocate_node();
			}
			catch(std::exception& e)
			{
				_M_destroy_nodes(nstart, cur);
				throw;
			}
		}

	template<typename _Tp, typename _Alloc>
		void
		_Deque_base<_Tp, _Alloc>::
		_M_destroy_nodes(_Map_pointer nstart,
				 _Map_pointer nfinish)
		{
			for (_Map_pointer n = nstart; n < nfinish; ++n)
				_M_deallocate_node(*n);
		}

	template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
		class deque : protected _Deque_base<_Tp, _Alloc>
		{
			typedef typename _Alloc::value_type				_Alloc_value_type;

			typedef _Deque_base<_Tp, _Alloc>			_Base;
			typedef typename _Base::_Tp_alloc_type		_Tp_alloc_type;
			typedef typename _Base::_Alloc_traits		_Alloc_traits;
			typedef typename _Base::_Map_pointer		_Map_pointer;

		public:
			typedef _Tp											value_type;
			typedef typename _Alloc_traits::pointer				pointer;
			typedef typename _Alloc_traits::const_pointer		const_pointer;
			typedef typename _Alloc_traits::reference			reference;
			typedef typename _Alloc_traits::const_reference		const_reference;
			typedef typename _Base::iterator					iterator;
			typedef typename _Base::const_iterator				const_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef size_t										size_type;
			typedef ptrdiff_t									difference_type;
			typedef _Alloc										 allocator_type;

		protected:
			using _Base::_M_initialize_map;
			using _Base::_M_create_nodes;
			using _Base::_M_destroy_nodes;
			using _Base::_M_allocate_node;
			using _Base::_M_deallocate_node;
			using _Base::_M_allocate_map;
			using _Base::_M_deallocate_map;
			using _Base::_M_get_Tp_allocator;

			using _Base::_M_impl;

		public:
			deque() : _Base()
			{}

			explicit
			deque(const allocator_type& a)
			: _Base(a, 0)
			{}

			explicit
			deque(size_type n, const value_type& value = value_type(),
			const allocator_type& a = allocator_type())
			: _Base(a, n)
			{
				_M_fill_initialize(value);
			}

			deque(const deque& x)
			: _Base(x._M_get_Tp_allocator(), x.size())
			{
			template<typename _InputIterator>
				deque(_InputIterator first, _InputIterator last,
				const allocator_type& a = allocator_type())
				: _Base(a)
				{
					typedef typename ft::is_integer<_InputIterator>::type _Integral;
					_M_initialize_dispatch(first, last, _Integral());
				}

			~deque()
			{
				_M_destroy_data(begin(), end(), _M_get_Tp_allocator());
			}

			deque&
			operator=(const deque& x);

			void
			assign(size_type n, const value_type& val)
			{
				_M_fill_assign(n, val);
			}

			template<typename _InputIterator>
				void
				assign(_InputIterator first, _InputIterator last)
				{
					typedef typename ft::is_integer<_InputIterator>::type _Integral;
					_M_assign_dispatch(first, last, _Integral());
				}

			allocator_type
			get_allocator() const
			{
				return (_Base::get_allocator());
			}

			iterator
			begin()
			{
				return (this->_M_impl._M_start);
			}

			const_iterator
			begin() const
			{
				return (this->_M_impl._M_start)
			}

			iterator
			end()
			{
				return (this->_M_impl._M_finish);
			}

			const_iterator
			end() const
			{
				return (this->_M_impl._M_finish);
			}

			reverse_iterator
			rbegin()
			{
				return (reverse_iterator(this->_M_impl._M_finish));
			}

			const_reverse_iterator
			rbegin() const
			{
				return (const_reverse_iterator(this->_M_impl._M_finish));
			}

			reverse_iterator
			rend()
			{
				return (reverse_iterator(this->_M_impl._M_start));
			}

			const_reverse_iterator
			rend() const
			{
				return (const_reverse_iterator(this->_M_impl._M_start));
			}

			size_type
			size() const
			{
				return (this->_M_impl._M_finish - this->_M_impl._M_start);
			}

			size_type
			max_size() const
			{
				return (_Alloc_traits::max_size(_M_get_Tp_allocator()));
			}

			void
			resize(size_type new_size, value_type x = value_type())
			{
				const size_type len = size();
				if (new_size > len)
					insert(this->_M_impl._M_finish, new_size - len, x);
				else if (new_size < len)
					_M_erase_at_end(this->_M_impl._M_start
							+ difference_type(new_size));
			}

			bool
			empty() const
			{
				return (this->_M_impl._M_finish == this->_M_impl._M_start)
			}

			reference
			operator[](size_type n)
			{
				return (this->_M_impl._M_start[difference_type(n)]);
			}

			const_reference
			operator[](size_type n) const
			{
				return (this->_M_impl._M_start[difference_type(n)]);
			}

		protected:
			void
			_M_range_check(size_type n) const
			{
				if (n >= this->size())
					throw(std::out_of_range("Out of range"));
			}

		public:
			reference
			at(size_type n)
			{
				_M_range_check(n);
				return ((*this)[n]);
			}

			const_reference
			at(size_type n) const
			{
				_M_range_check(n);
				return ((*this)[n]);
			}

			reference
			front()
			{
				return (*begin());
			}

			const_reference
			front() const
			{
				return (*begin());
			}

			reference
			back()
			{
				iterator tmp = end();
				--tmp;
				return (*tmp);
			}

			const_reference
			back() const
			{
				const_iterator tmp = end();
				--tmp;
				return (*tmp);
			}

			void
			push_front(const value_type& x)
			{
				if (this->_M_impl._M_start._M_cur != this->_M_impl._M_start._M_first)
				{
					_Alloc_traits::construct(this->_M_impl,
											 this->_M_impl._M_start._M_cur - 1,
											 x);
					--this->_M_impl._M_start._M_cur;
				}
				else
					_M_push_front_aux(x);
			}

			void
			push_back(const value_type& x)
			{
				if (this->_M_impl._M_finish._M_cur
						!= this->_M_impl._M_finish._M_last - 1)
				{
					_Alloc_traits::construct(this->_M_impl,
											 this->_M_impl._M_finish._M_cur,
											 x);
					++this->_M_impl._M_finish._M_cur;
				}
				else
					_M_push_back_aux(x);
			}

			void
			pop_front()
			{
				if (this->_M_impl._M_start._M_cur
						!= this->_M_impl._M_start._M_last - 1)
				{
					_Alloc_traits::destroy(this->_M_impl,
											this->_M_impl._M_start._M_cur);
					++this->_M_impl._M_start._M_cur;
				}
				else
					_M_pop_front_aux();
			}

			void
			pop_back()
			{
				if (this->_M_impl._M_finish._M_cur
						!= this->_M_impl._M_finish._M_first)
				{
					--this->_M_impl._M_finish._M_cur;
					_Alloc_traits::destroy(this->_M_impl,
											this->_M_impl._M_finish._M_cur);
				}
				else
					_M_pop_back_aux();
			}

			iterator
			insert(iterator position, const value_type& x);

			void
			insert(iterator position, size_type n, const value_type& x)
			{
				_M_fill_insert(position, n, x);
			}

			template<typename _InputIterator>
				void
				insert(iterator position, _InputIterator first,
				 _InputIterator last)
				{
					typedef typename ft::is_integer<_InputIterator>::type _Integral;
					_M_insert_dispatch(position, first, last, _Integral());
				}

			iterator
			erase(iterator position)
			{
				return (_M_erase(position._M_const_cast()));
			}

			iterator
			erase(iterator first, iterator last)
			{
				return (_M_erase(first._M_const_cast(), last._M_const_cast()));
			}

			void
			swap(deque& x)
			{
				_M_impl._M_swap_data(x._M_impl);
			}

			void
			clear()
			{
				_M_erase_at_end(begin());
			}

		protected:
			template<typename _Integer>
				void
				_M_initialize_dispatch(_Integer n, _Integer x, true_type)
				{
					_M_initialize_map(static_cast<size_type>(n));
					_M_fill_initialize(x);
				}

			template<typename _InputIterator>
				void
				_M_initialize_dispatch(_InputIterator first, _InputIterator last,
						 false_type)
				{
					typedef typename ft::iterator_traits<_InputIterator>::
						iterator_category _IterCategory;
					_M_range_initialize(first, last, _IterCategory());
				}

			template<typename _InputIterator>
				void
				_M_range_initialize(_InputIterator first, _InputIterator last,
					ft::input_iterator_tag);

			template<typename _ForwardIterator>
				void
				_M_range_initialize(_ForwardIterator first, _ForwardIterator last,
					ft::forward_iterator_tag);
	
			void
			_M_fill_initialize(const value_type& value);

			template<typename _Integer>
				void
				_M_assign_dispatch(_Integer n, _Integer val, true_type)
				{
					_M_fill_assign(n, val);
				}

			template<typename _InputIterator>
				void
				_M_assign_dispatch(_InputIterator first, _InputIterator last,
				 false_type)
				{
					typedef typename ft::iterator_traits<_InputIterator>::
						iterator_category _IterCategory;
					_M_assign_aux(first, last, _IterCategory());
				}

			template<typename _InputIterator>
				void
				_M_assign_aux(_InputIterator first, _InputIterator last,
					ft::input_iterator_tag);

			template<typename _ForwardIterator>
				void
				_M_assign_aux(_ForwardIterator first, _ForwardIterator last,
					ft::forward_iterator_tag)
				{
					const size_type len = ft::distance(first, last);
					if (len > size())
					{
						_ForwardIterator mid = first;
						ft::advance(mid, size());
						ft::copy(first, mid, begin());
						insert(end(), mid, last);
					}
					else
						_M_erase_at_end(ft::copy(first, last, begin()));
				}

			void
			_M_fill_assign(size_type n, const value_type& val)
			{
				if (n > size())
				{
					ft::fill(begin(), end(), val);
					insert(end(), n - size(), val);
				}
				else
				{
					_M_erase_at_end(begin() + difference_type(n));
					ft::fill(begin(), end(), val);
				}
			}

			void _M_push_back_aux(const value_type&);

			void _M_push_front_aux(const value_type&);

			void _M_pop_back_aux();

			void _M_pop_front_aux();

			template<typename _Integer>
				void
				_M_insert_dispatch(iterator pos,
				 _Integer n, _Integer x, true_type)
				{
					_M_fill_insert(pos, n, x);
				}

			template<typename _InputIterator>
				void
				_M_insert_dispatch(iterator pos,
				 _InputIterator first, _InputIterator last,
				 false_type)
				{
					typedef typename ft::iterator_traits<_InputIterator>::
						iterator_category _IterCategory;
								_M_range_insert_aux(pos, first, last, _IterCategory());
				}

			template<typename _InputIterator>
				void
				_M_range_insert_aux(iterator pos, _InputIterator first,
					_InputIterator last, ft::input_iterator_tag);

			template<typename _ForwardIterator>
				void
				_M_range_insert_aux(iterator pos, _ForwardIterator first,
					_ForwardIterator last, ft::forward_iterator_tag);

			void
			_M_fill_insert(iterator pos, size_type n, const value_type& x);

			iterator
			_M_insert_aux(iterator pos, const value_type& x);

			void
			_M_insert_aux(iterator pos, size_type n, const value_type& x);

			template<typename _ForwardIterator>
				void
				_M_insert_aux(iterator pos,
					_ForwardIterator first, _ForwardIterator last,
					size_type n);

			void
			_M_destroy_data_aux(iterator first, iterator last);

			template<typename _Alloc1>
				void
				_M_destroy_data(iterator first, iterator last, const _Alloc1&)
				{
					_M_destroy_data_aux(first, last);
				}

			void
			_M_destroy_data(iterator first, iterator last,
					const std::allocator<_Tp>&)
			{
				if (!has_trivial_destructor(value_type))
					_M_destroy_data_aux(first, last);
			}

			void
			_M_erase_at_begin(iterator pos)
			{
				_M_destroy_data(begin(), pos, _M_get_Tp_allocator());
				_M_destroy_nodes(this->_M_impl._M_start._M_node, pos._M_node);
				this->_M_impl._M_start = pos;
			}

			void
			_M_erase_at_end(iterator pos)
			{
				_M_destroy_data(pos, end(), _M_get_Tp_allocator());
				_M_destroy_nodes(pos._M_node + 1,
						 this->_M_impl._M_finish._M_node + 1);
				this->_M_impl._M_finish = pos;
			}

			iterator
			_M_erase(iterator pos);

			iterator
			_M_erase(iterator first, iterator last);

			iterator
			_M_reserve_elements_at_front(size_type n)
			{
				const size_type vacancies = this->_M_impl._M_start._M_cur
											this->_M_impl._M_start._M_first;
				if (n > vacancies)
					_M_new_elements_at_front(n - vacancies);
				return (this->_M_impl._M_start - difference_type(n));
			}

			iterator
			_M_reserve_elements_at_back(size_type n)
			{
				const size_type vacancies = (this->_M_impl._M_finish._M_last
										- this->_M_impl._M_finish._M_cur) - 1;
				if (n > vacancies)
					_M_new_elements_at_back(n - vacancies);
				return (this->_M_impl._M_finish + difference_type(n));
			}

			void
			_M_new_elements_at_front(size_type new_elements);

			void
			_M_new_elements_at_back(size_type new_elements);

			void
			_M_reserve_map_at_back(size_type nodes_to_add = 1)
			{
				if (nodes_to_add + 1 > this->_M_impl._M_map_size
						- (this->_M_impl._M_finish._M_node - this->_M_impl._M_map))
					_M_reallocate_map(nodes_to_add, false);
			}

			void
			_M_reserve_map_at_front(size_type nodes_to_add = 1)
			{
				if (nodes_to_add > size_type(this->_M_impl._M_start._M_node
										 - this->_M_impl._M_map))
					_M_reallocate_map(nodes_to_add, true);
			}

			void
			_M_reallocate_map(size_type nodes_to_add, bool add_at_front);
		};


	template<typename _Tp, typename _Alloc>
		inline bool
		operator==(const deque<_Tp, _Alloc>& x,
					const deque<_Tp, _Alloc>& y)
		{
			return (x.size() == y.size()
						 && ft::equal(x.begin(), x.end(), y.begin()));
		}

	template<typename _Tp, typename _Alloc>
		inline bool
		operator<(const deque<_Tp, _Alloc>& x,
				const deque<_Tp, _Alloc>& y)
		{
			return (ft::lexicographical_compare(x.begin(), x.end(),
						y.begin(), y.end()));
		}

	template<typename _Tp, typename _Alloc>
		inline bool
		operator!=(const deque<_Tp, _Alloc>& x,
				 const deque<_Tp, _Alloc>& y)
		{
			return (!(x == y));
		}

	template<typename _Tp, typename _Alloc>
		inline bool
		operator>(const deque<_Tp, _Alloc>& x,
				const deque<_Tp, _Alloc>& y)
		{
			return (y < x);
		}

	template<typename _Tp, typename _Alloc>
		inline bool
		operator<=(const deque<_Tp, _Alloc>& x,
				 const deque<_Tp, _Alloc>& y)
		{
			return (!(y < x));
		}

	template<typename _Tp, typename _Alloc>
		inline bool
		operator>=(const deque<_Tp, _Alloc>& x,
				 const deque<_Tp, _Alloc>& y)
		{
			return (!(x < y));
		}

	template<typename _Tp, typename _Alloc>
		inline void
		swap(deque<_Tp,_Alloc>& x, deque<_Tp,_Alloc>& y)
		{
			x.swap(y);
		}
}

#endif
