/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiset.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: YanYan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:31:01 by YanYan            #+#    #+#             */
/*   Updated: 2020/07/17 15:31:02 by YanYan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTISET_HPP
# define MULTISET_HPP

namespace ft
{
	template <typename _Key, typename _Compare = std::less<_Key>,
			typename _Alloc = std::allocator<_Key> >
		class multiset
		{
			typedef typename _Alloc::value_type									 _Alloc_value_type;

		public:
			typedef _Key		key_type;
			typedef _Key		value_type;
			typedef _Compare	key_compare;
			typedef _Compare	value_compare;
			typedef _Alloc		allocator_type;

		private:
			typedef typename _Alloc::template
				rebind<_Key>::other _Key_alloc_type;

			typedef _Rb_tree<key_type, value_type, _Identity<value_type>,
					 key_compare, _Key_alloc_type> _Rep_type;
			_Rep_type _M_t;

			typedef _Key_alloc_type _Alloc_traits;

		public:
			typedef typename _Alloc_traits::pointer				pointer;
			typedef typename _Alloc_traits::const_pointer		const_pointer;
			typedef typename _Alloc_traits::reference			reference;
			typedef typename _Alloc_traits::const_reference		const_reference;
			typedef typename _Rep_type::const_iterator			iterator;
			typedef typename _Rep_type::const_iterator			const_iterator;
			typedef typename _Rep_type::const_reverse_iterator	reverse_iterator;
			typedef typename _Rep_type::const_reverse_iterator	const_reverse_iterator;
			typedef typename _Rep_type::size_type				size_type;
			typedef typename _Rep_type::difference_type			difference_type;

			multiset (void)
			: _M_t()
			{}

			explicit
			multiset(const _Compare& comp,
				 const allocator_type& a = allocator_type())
			: _M_t(comp, _Key_alloc_type(a))
			{}

			template<typename _InputIterator>
				multiset(_InputIterator first, _InputIterator last)
				: _M_t()
				{
					_M_t._M_insert_equal(first, last);
				}

			template<typename _InputIterator>
				multiset(_InputIterator first, _InputIterator last,
					const _Compare& comp,
					const allocator_type& a = allocator_type())
				: _M_t(comp, _Key_alloc_type(a))
				{
					_M_t._M_insert_equal(first, last);
				}

			multiset(const multiset& x)
			: _M_t(x._M_t)
			{}

			multiset&
			operator=(const multiset& x)
			{
				_M_t = x._M_t;
				return (*this);
			}

			key_compare
			key_comp (void) const
			{
				return (_M_t.key_comp());
			}

			value_compare
			value_comp (void) const
			{
				return (_M_t.key_comp());
			}

			allocator_type
			get_allocator (void) const
			{ return allocator_type(_M_t.get_allocator()); }

			iterator
			begin (void) const
			{
				return (_M_t.begin());
			}

			iterator
			end (void) const
			{
				return (_M_t.end());
			}

			reverse_iterator
			rbegin (void) const
			{
				return (_M_t.rbegin());
			}

			reverse_iterator
			rend (void) const
			{
				return (_M_t.rend());
			}

			bool
			empty (void) const
			{
				return (_M_t.empty());
			}

			size_type
			size (void) const
			{
				return (_M_t.size());
			}

			size_type
			max_size (void) const
			{
				return (_M_t.max_size());
			}

			void
			swap(multiset& x)
			{
				_M_t.swap(x._M_t);
			}

			iterator
			insert(const value_type& x)
			{
				return (_M_t._M_insert_equal(x));
			}

			iterator
			insert(const_iterator position, const value_type& x)
			{
				return (_M_t._M_insert_equal_(position, x));
			}

			template<typename _InputIterator>
				void
				insert(_InputIterator first, _InputIterator last)
				{
					_M_t._M_insert_equal(first, last);
				}

			void
			erase(iterator position)
			{
				_M_t.erase(position);
			}

			size_type
			erase(const key_type& x)
			{
				return (_M_t.erase(x));
			}

			void
			erase(iterator first, iterator last)
			{
				_M_t.erase(first, last);
			}

			void
			clear (void)
			{
				_M_t.clear();
			}

			size_type
			count(const key_type& x) const
			{
				return (_M_t.count(x));
			}

			iterator
			find(const key_type& x)
			{
				return (_M_t.find(x));
			}

			const_iterator
			find(const key_type& x) const
			{
				return (_M_t.find(x));
			}

			iterator
			lower_bound(const key_type& x)
			{
				return (_M_t.lower_bound(x));
			}

			const_iterator
			lower_bound(const key_type& x) const
			{
				return (_M_t.lower_bound(x));
			}

			iterator
			upper_bound(const key_type& x)
			{
				return (_M_t.upper_bound(x));
			}

			const_iterator
			upper_bound(const key_type& x) const
			{
				return (_M_t.upper_bound(x));
			}

			ft::pair<iterator, iterator>
			equal_range(const key_type& x)
			{
				return (_M_t.equal_range(x));
			}

			ft::pair<const_iterator, const_iterator>
			equal_range(const key_type& x) const
			{
				return (_M_t.equal_range(x));
			}

			template<typename _K1, typename _C1, typename _A1>
				friend bool
				operator==(const multiset<_K1, _C1, _A1>&,
					const multiset<_K1, _C1, _A1>&);

			template<typename _K1, typename _C1, typename _A1>
				friend bool
				operator< (const multiset<_K1, _C1, _A1>&,
					const multiset<_K1, _C1, _A1>&);
		};

	template<typename _Key, typename _Compare, typename _Alloc>
		inline bool
		operator==(const multiset<_Key, _Compare, _Alloc>& x,
					const multiset<_Key, _Compare, _Alloc>& y)
		{
			return (x._M_t == y._M_t);
		}

	template<typename _Key, typename _Compare, typename _Alloc>
		inline bool
		operator<(const multiset<_Key, _Compare, _Alloc>& x,
					const multiset<_Key, _Compare, _Alloc>& y)
		{
			return (x._M_t < y._M_t);
		}

	template<typename _Key, typename _Compare, typename _Alloc>
		inline bool
		operator!=(const multiset<_Key, _Compare, _Alloc>& x,
					const multiset<_Key, _Compare, _Alloc>& y)
		{
			return (!(x == y));
		}

	template<typename _Key, typename _Compare, typename _Alloc>
		inline bool
		operator>(const multiset<_Key,_Compare,_Alloc>& x,
					const multiset<_Key,_Compare,_Alloc>& y)
		{
			return (y < x);
		}

	template<typename _Key, typename _Compare, typename _Alloc>
		inline bool
		operator<=(const multiset<_Key, _Compare, _Alloc>& x,
					const multiset<_Key, _Compare, _Alloc>& y)
		{
			return (!(y < x));
		}

	template<typename _Key, typename _Compare, typename _Alloc>
		inline bool
		operator>=(const multiset<_Key, _Compare, _Alloc>& x,
					const multiset<_Key, _Compare, _Alloc>& y)
		{
			return (!(x < y));
		}

	template<typename _Key, typename _Compare, typename _Alloc>
		inline void
		swap(multiset<_Key, _Compare, _Alloc>& x,
			multiset<_Key, _Compare, _Alloc>& y)
		{
			x.swap(y);
		}
}

#endif
