
#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>

# include "iterator.hpp"

namespace	ft
{
	namespace __detail
	{
		struct _List_node_base
		{
			_List_node_base* _M_next;
			_List_node_base* _M_prev;

			static void
			swap(_List_node_base& __x, _List_node_base& __y);

			void
			_M_transfer(_List_node_base* const __first,
			_List_node_base* const __last);

			void
			_M_reverse();

			void
			_M_hook(_List_node_base* const __position);

			void
			_M_unhook();
		};
	}

	template<typename _Tp>
		struct _List_node : public __detail::_List_node_base
		{
			_Tp _M_data;
			_Tp*			 _M_valptr()			 { return std::__addressof(_M_data); }
			_Tp const* _M_valptr() const { return std::__addressof(_M_data); }
		};

	template<typename _Tp>
		struct _List_iterator
		{
			typedef _List_iterator<_Tp>	_Self;
			typedef _List_node<_Tp>		_Node;

			typedef ptrdiff_t			difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef _Tp					value_type;
			typedef _Tp*				pointer;
			typedef _Tp&				reference;

			_List_iterator() : _M_node() {}

			explicit
			_List_iterator(__detail::_List_node_base* __x) : _M_node(__x) { }

			_Self
			_M_const_cast() const
			{
				return *this;
			}

			reference
			operator*() const
			{
				return *static_cast<_Node*>(_M_node)->_M_valptr();
			}

			pointer
			operator->() const
			{
				return static_cast<_Node*>(_M_node)->_M_valptr();
			}

			_Self&
			operator++()
			{
				_M_node = _M_node->_M_next;
				return *this;
			}

			_Self
			operator++(int)
			{
				_Self __tmp = *this;
				_M_node = _M_node->_M_next;
				return __tmp;
			}

			_Self&
			operator--()
			{
				_M_node = _M_node->_M_prev;
				return *this;
			}

			_Self
			operator--(int)
			{
				_Self __tmp = *this;
				_M_node = _M_node->_M_prev;
				return __tmp;
			}

			bool
			operator==(const _Self& __x) const
			{
				return _M_node == __x._M_node;
			}

			bool
			operator!=(const _Self& __x) const
			{
				return _M_node != __x._M_node;
			}

			__detail::_List_node_base* _M_node;
		};

	template<typename _Tp>
		struct _List_const_iterator
		{
			typedef _List_const_iterator<_Tp>		_Self;
			typedef const _List_node<_Tp>			_Node;
			typedef _List_iterator<_Tp>				iterator;

			typedef ptrdiff_t						difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef _Tp								value_type;
			typedef const _Tp*						pointer;
			typedef const _Tp&						reference;

			_List_const_iterator() : _M_node() {}

			explicit
			_List_const_iterator(const __detail::_List_node_base* __x) : _M_node(__x) { }

			_List_const_iterator(const iterator& __x) : _M_node(__x._M_node) { }

			iterator
			_M_const_cast() const
			{
				return iterator(const_cast<__detail::_List_node_base*>(_M_node));
			}

			reference
			operator*() const
			{
				return *static_cast<_Node*>(_M_node)->_M_valptr();
			}

			pointer
			operator->() const
			{
				return static_cast<_Node*>(_M_node)->_M_valptr();
			}

			_Self&
			operator++()
			{
				_M_node = _M_node->_M_next;
				return *this;
			}

			_Self
			operator++(int)
			{
				_Self __tmp = *this;
				_M_node = _M_node->_M_next;
				return __tmp;
			}

			_Self&
			operator--()
			{
				_M_node = _M_node->_M_prev;
				return *this;
			}

			_Self
			operator--(int)
			{
				_Self __tmp = *this;
				_M_node = _M_node->_M_prev;
				return __tmp;
			}

			bool
			operator==(const _Self& __x) const
			{
				return _M_node == __x._M_node;
			}

			bool
			operator!=(const _Self& __x) const
			{
				return _M_node != __x._M_node;
			}

			const __detail::_List_node_base* _M_node;
		};

	template<typename _Val>
		inline bool
		operator==(const _List_iterator<_Val>& __x,
				 const _List_const_iterator<_Val>& __y)
		{
			return __x._M_node == __y._M_node;
		}

	template<typename _Val>
		inline bool
		operator!=(const _List_iterator<_Val>& __x,
				 const _List_const_iterator<_Val>& __y)
		{
			return __x._M_node != __y._M_node;
		}

//	template <class T, class Alloc>
	template <typename T, typename Alloc = std::allocator<T>>
	class	list
	{
		public:
			typedef T											value_type;
			typedef std::allocator<value_type>					allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::_List_iterator<T>						iterator;
			typedef ft::_List_iterator<const T>					const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			typedef std::ptrdiff_t difference_type;
			typedef size_t size_type;

			explicit list (const allocator_type& alloc = allocator_type());
			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			list (const list& x);

			~list();

			list& operator= (const list& x);

			iterator begin();
			const_iterator begin() const;

			iterator end();
			const_iterator end() const;

			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;

			reverse_iterator rend();
			const_reverse_iterator rend() const;

			bool empty() const;

			size_type size() const;

			size_type max_size() const;

			reference front();
			const_reference front() const;

			reference back();
			const_reference back() const;

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last);
			void assign (size_type n, const value_type& val);

			void push_front (const value_type& val);

			void pop_front();

			void push_back (const value_type& val);

			void pop_back();

			iterator insert (iterator position, const value_type& val);
			void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);

			void swap (list& x);

			void resize (size_type n, value_type val = value_type());

			void clear();

			void splice (iterator position, list& x);
			void splice (iterator position, list& x, iterator i);
			void splice (iterator position, list& x, iterator first, iterator last);

			void remove (const value_type& val);

			template <class Predicate>
			void remove_if (Predicate pred);
			
			void unique();
			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred);

			void merge (list& x);
			template <class Compare>
			void merge (list& x, Compare comp);

			void sort();
			template <class Compare>
			void sort (Compare comp);

			void reverse();
/*
//			template <class T, class Alloc>
			bool operator== (const list<T,Alloc>& rhs);
//			template <class T, class Alloc>
			bool operator!= (const list<T,Alloc>& rhs);
//			template <class T, class Alloc>
			bool operator<	(const list<T,Alloc>& rhs);
//			template <class T, class Alloc>
			bool operator<= (const list<T,Alloc>& rhs);
//			template <class T, class Alloc>
			bool operator>	(const list<T,Alloc>& rhs);
//			template <class T, class Alloc>
			bool operator>= (const list<T,Alloc>& rhs);*/


//			template <class T, class Alloc>
			void swap (list<T,Alloc>& x, list<T,Alloc>& y);

		private:
			allocator_type _allocator;
			pointer _arr;
			size_type _size;
			size_type _capacity;
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
	list<T, Alloc>::list(const allocator_type& alloc)
		: _allocator(alloc), _arr(NULL), _size(0), _capacity(0)
	{}

	template <typename T, typename Alloc>
	list<T, Alloc>::list(size_type n, const value_type& val, const allocator_type& alloc)
		: _allocator(alloc), _size(n), _capacity(n)
	{
		_arr = _allocator.allocate(n);
		for (size_type i = 0; i < n; i++) {
			_allocator.construct(_arr + i, val);
		}
	}

	template <typename T, typename Alloc>
	template <typename InputIterator>
	list<T, Alloc>::list(InputIterator first, InputIterator last, const allocator_type& alloc)
	{
		_allocator = alloc;
		_size = last - first;
		_capacity = _size;
		_arr = _allocator.allocate(_size);
		int i = 0;
		for (InputIterator it = first; it != last; ++it, ++i)
		{
			_allocator.construct(_arr + i, *it);
		}
	}

	template <typename T, typename Alloc>
	list<T, Alloc>::list(const list &other)
		: _allocator(other._allocator), _size(other._size), _capacity(other._capacity)
	{
		if (other._arr) {
			_arr = _allocator.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(_arr + i, other._arr[i]);
		}
	}

	template <typename T, typename Alloc>
	list<T, Alloc>::~list()
	{
		if (_capacity) {
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_arr + i);
			_allocator.deallocate(_arr, _capacity);
		}
	}

	template <typename T, typename Alloc>
	list<T, Alloc>&
	list<T, Alloc>::operator=	(const list& src)
	{
		if (_arr) {
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_arr[i]);
			_allocator.deallocate(_arr, _capacity);
		}
		if (src._arr) {
			_arr = _allocator.allocate(src._capacity);
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(&_arr[i], src._arr[i]);
		}
		_size = src._size;
		_capacity = src._capacity;
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::iterator
	list<T, Alloc>::begin (void)
	{
		return (iterator(_arr));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_iterator
	list<T, Alloc>::begin(void) const
	{
		return (const_iterator(_arr));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::iterator
	list<T, Alloc>::end (void)
	{
		return (iterator(_arr + _size));
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::const_iterator
	list<T, Alloc>::end(void) const
	{
		return (const_iterator(_arr + _size));
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
		return (_size == 0);
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::size_type
	list<T, Alloc>::size(void) const
	{
		return (_size);
	}

	template <typename T, typename Alloc>
	typename list<T, Alloc>::size_type
	list<T, Alloc>::max_size(void) const
	{
		return (static_cast<size_type>(-1 / sizeof(T)));
	}
}

#endif
