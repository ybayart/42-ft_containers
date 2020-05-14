#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils.hpp"

namespace	ft
{
	template<typename _Tp, typename _Alloc>
		struct _Vector_base
		{
			private:
				typedef _Alloc								allocator_type;
				typedef typename allocator_type::pointer	pointer;

				struct _Vector_impl
				: public _Alloc
				{
					pointer _M_start;
					pointer _M_finish;
					pointer _M_end_of_storage;

					_Vector_impl (void)
					: allocator_type(), _M_start(), _M_finish(), _M_end_of_storage()
					{}

					_Vector_impl(_Alloc const& a)
					: allocator_type(a), _M_start(), _M_finish(), _M_end_of_storage()
					{}

					void
					_M_swap_data (_Vector_impl& x)
					{
						std::swap(_M_start, x._M_start);
						std::swap(_M_finish, x._M_finish);
						std::swap(_M_end_of_storage, x._M_end_of_storage);
					}
				};

			public:
				allocator_type&
				_M_get_Tp_allocator (void)
				{
					return (*static_cast<allocator_type*>(&this->_M_impl));
				}

				const allocator_type&
				_M_get_Tp_allocator (void) const
				{
					return (*static_cast<const allocator_type*>(&this->_M_impl));
				}

				allocator_type
				get_allocator (void) const
				{
					return (allocator_type(_M_get_Tp_allocator()));
				}

				_Vector_base (void)
				: _M_impl()
				{}

				_Vector_base (const allocator_type& a)
				: _M_impl(a)
				{}

				_Vector_base (size_t n)
				: _M_impl()
				{
					_M_create_storage(n);
				}

				_Vector_base (size_t n, const allocator_type& a)
				: _M_impl(a)
				{
					_M_create_storage(n);
				}

				~_Vector_base (void)
				{
					_M_deallocate(this->_M_impl._M_start,
						this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
				}


				_Vector_impl	_M_impl;

				pointer
				_M_allocate (size_t n)
				{
					allocator_type	alloc;
					
					alloc = _M_get_Tp_allocator();
					if (n == 0)
						return (pointer());
					else
						return (alloc.allocate(n));
				}

				void
				_M_deallocate (pointer p, size_t n)
				{
					allocator_type	alloc;
					
					alloc = _M_get_Tp_allocator();
					if (p)
						alloc.deallocate(p, n);
				}

			private:
				void
				_M_create_storage (size_t n)
				{
					this->_M_impl._M_start = this->_M_allocate(n);
					this->_M_impl._M_finish = this->_M_impl._M_start;
					this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
				}
		};


	template<typename T, typename Alloc = std::allocator<T> >
		class vector
		: protected _Vector_base<T, Alloc>
		{
			typedef _Vector_base<T, Alloc>							_Base;

			public:
				typedef T											value_type;
				typedef	Alloc										allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef normal_iterator<pointer, vector>			iterator;
				typedef normal_iterator<const_pointer, vector>		const_iterator;
				typedef std::reverse_iterator<iterator>				reverse_iterator;
				typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
				typedef ptrdiff_t									difference_type;
				typedef size_t										size_type;

			public:
				explicit vector (const allocator_type& alloc = allocator_type());
				explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
				template <class InputIterator>
					vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
				vector (const vector& x);

				~vector (void);

				vector& operator=	(const vector& x);

				iterator begin (void);
				const_iterator begin (void) const;

				iterator end (void);
				const_iterator end (void) const;

				reverse_iterator rbegin (void);
				const_reverse_iterator rbegin(void) const;

				reverse_iterator rend (void);
				const_reverse_iterator rend(void) const;

				size_type size (void) const;

				size_type max_size (void) const;

				void resize (size_type n, value_type val = value_type());

				size_type capacity (void) const;

				bool empty (void) const;

				void reserve (size_type n);

				reference operator[]	(size_type n);
				const_reference operator[]	(size_type n) const;

				reference at (size_type n);
				const_reference at (size_type n) const;

				reference front (void);
				const_reference front (void) const;

				reference back (void);
				const_reference back(void) const;

				template <class InputIterator>
					void assign (InputIterator first, InputIterator last);
				void assign (size_type n, const value_type& val);

				void push_back (const value_type& val);

				void pop_back (void);

				iterator insert (iterator position, const value_type& val);

				void insert (iterator position, size_type n, const value_type& val);
				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last);

				iterator erase (iterator position);
				iterator erase (iterator first, iterator last);

				void swap (vector& x);

				void clear (void);

			protected:
				using _Base::_M_allocate;
				using _Base::_M_deallocate;
				using _Base::_M_impl;
				using _Base::_M_get_Tp_allocator;

			private:
				allocator_type	_alloc;

				void
				_M_dispatch(size_type n, const value_type& val, true_type)
				{
					this->_M_impl._M_start = _M_allocate(n);
					this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
					_M_init_fill(n, val);
				}

				template <typename InputIterator>
				void
				_M_dispatch(InputIterator first, InputIterator last, false_type)
				{
					typedef typename ft::iterator_traits<InputIterator>::iterator_category IterCategory;
					_M_init_range(first, last, IterCategory());
				}

				void
				_M_init_fill(size_type n, const value_type& val)
				{
					pointer	cur = this->_M_impl._M_start;
					try
					{
						for (;n > 0;--n, ++cur)
							_alloc.construct(cur, val);
						this->_M_impl._M_finish = cur;
					}
					catch(std::exception& e)
					{
						_M_deallocate(this->_M_impl._M_start, n * sizeof(val));
						throw;
					}
				}

				template<typename InputIterator>
				void
				_M_init_range(InputIterator first, InputIterator last, ft::input_iterator_tag)
				{
					try
					{
						for (;first != last; ++first)
							push_back(*first);
					}
					catch(std::exception& e)
					{
						clear();
						throw;
					}
				}

				template<typename ForwardIterator>
				void
				_M_init_range(ForwardIterator first, ForwardIterator last, ft::forward_iterator_tag)
				{
					const size_type n = ft::distance(first, last);
		
					this->_M_impl._M_start = this->_M_allocate(n);
					this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
					_M_cpy_range(first, last);
				}

				template <typename InputIterator>
				void
				_M_cpy_range(InputIterator first, InputIterator last)
				{
					pointer cur = this->_M_impl._M_start;
					try
					{
						for (;first != last; ++first, ++cur)
							_alloc.construct(cur, *first);
						this->_M_impl._M_finish = cur;
					}
					catch(std::exception& e)
					{
						_alloc.destroy(this->_M_impl._M_start);
						throw;
					}
				}

		};
	
	template <typename T, typename Alloc>
	vector<T, Alloc>::vector (const allocator_type& alloc)
	: _Base(alloc)
	{}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector (size_type n, const value_type& val, const allocator_type& alloc)
	: _Base(n, alloc)
	{
		_M_init_fill(n, val);
	}

	template <typename T, typename Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector (InputIterator first, InputIterator last, const allocator_type& alloc)
	: _Base(alloc)
	{
		typedef typename ft::is_integer<InputIterator>::type is_int;
		_M_dispatch(first, last, is_int());
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector (const vector& x)
	: _Base(x.size(), x._M_get_Tp_allocator())
	{
		_M_cpy_range(x.begin(), x.end());
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::~vector(void)
	{
		_alloc.destroy(this->_M_impl._M_start);
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>&
	vector<T, Alloc>::operator=	(const vector& x)
	{
		if (&x != this)
		{
			_alloc.destroy(this->_M_impl._M_start);
			_M_cpy_range(x.begin(), x.end());
		}
		return (*this);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator
	vector<T, Alloc>::begin (void)
	{
		return (iterator(this->_M_impl._M_start));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator
	vector<T, Alloc>::begin (void) const
	{
		return (const_iterator(this->_M_impl._M_start));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator
	vector<T, Alloc>::end (void)
	{
		return (iterator(this->_M_impl._M_finish));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator
	vector<T, Alloc>::end (void) const
	{
		return (const_iterator(this->_M_impl._M_finish));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator
	vector<T, Alloc>::rbegin (void)
	{
		return (reverse_iterator(end()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator
	vector<T, Alloc>::rbegin(void) const
	{
		return (const_reverse_iterator(end()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator
	vector<T, Alloc>::rend (void)
	{
		return (reverse_iterator(begin()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator
	vector<T, Alloc>::rend(void) const
	{
		return (const_reverse_iterator(begin()));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type
	vector<T, Alloc>::size (void) const
	{
		return (size_type(this->_M_impl._M_finish - this->_M_impl._M_start));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type
	vector<T, Alloc>::max_size (void) const
	{
		return (_alloc.max_size());
	}

	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::resize (size_type n, value_type val)
	{
		if (n <= size())
		{
			_alloc.destroy(this->_M_impl._M_start + n);
		}
		else
		{
			reserve(n);
			pointer ptr = this->_M_impl._M_start + size();
			for (size_type i = n - size();i > 0;i--, ptr++)
				_alloc.construct(ptr, val);
		}
		this->_M_impl._M_finish = this->_M_impl._M_start + n;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::size_type
	vector<T, Alloc>::capacity (void) const
	{
		return (size_type(this->_M_impl._M_end_of_storage - this->_M_impl._M_start));
	}

	template <typename T, typename Alloc>
	bool
	vector<T, Alloc>::empty (void) const
	{
		return (begin() == end());
	}

	template <typename T, typename Alloc>
	void
	vector<T, Alloc>::reserve(size_type n)
	{
		if (n > capacity())
		{
			vector<T> tmp = *this;
			this->_M_impl._M_start = _M_allocate(n);
			this->_M_impl._M_end_of_storage = this->_M_impl._M_start + n;
			_M_cpy_range(tmp.begin(), tmp.end());
			std::cout << "addr: " << &tmp << std::endl;
//			_M_deallocate(tmp._M_impl._M_start, tmp._M_impl._M_end_of_storage - tmp._M_impl._M_start);
		}
	}

	template <class T, class Alloc>
		bool operator==	(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator!=	(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator<	(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator<=	(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator>	(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator>=	(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
}

#endif
