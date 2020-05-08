#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils.hpp"

namespace	ft
{
	template<typename _Tp, typename _Alloc>
		struct _Vector_base
		{
			private:
				typedef typename _Alloc::pointer	pointer;

				struct _Vector_impl
				: public _Alloc
				{
					pointer _M_start;
					pointer _M_finish;
					pointer _M_end_of_storage;

					_Vector_impl (void)
					: _Alloc(), _M_start(), _M_finish(), _M_end_of_storage()
					{}

					_Vector_impl(_Alloc const& a)
					: _Alloc(a), _M_start(), _M_finish(), _M_end_of_storage()
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
				typedef _Alloc		allocator_type;

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
					if (n == 0)
						return (pointer());
					else
						return (allocator_type.allocate(_M_impl, n));
				}

				void
				_M_deallocate (pointer p, size_t n)
				{
					if (p)
						allocator_type.deallocate(_M_impl, p, n);
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
				typedef typename _Base::pointer						pointer;
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
		};
	
	template <typename T, typename Alloc>
	vector<T, Alloc>::vector (const allocator_type& alloc)
	: _Base(alloc)
	{}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector (size_type n, const value_type& val, const allocator_type& alloc)
	: _Base(n, alloc)
	{
		pointer	cur = this->_M_impl._M_start;
		try
		{
			for (; n > 0; --n, ++cur)
				alloc.construct(alloc, std::__addressof(*cur), val);
			this->_M_impl._M_finish = cur;
		}
		catch(std::exception& e)
		{
			alloc.deallocate(this->_M_impl._M_start, n * sizeof(val));
			throw;
		}
	}

	// template <typename T, typename Alloc>
	// template <class InputIterator>
	// vector<T, Alloc>::vector (InputIterator first, InputIterator last, const allocator_type& alloc)
	// {}

	// template <typename T, typename Alloc>
	// vector<T, Alloc>::vector (const vector& x)
	// {}


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
