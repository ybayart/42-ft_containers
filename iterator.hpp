
#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>

namespace	ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<typename _Category, typename _Tp, typename _Distance = __gnu_cxx::ptrdiff_t,
					 typename _Pointer = _Tp*, typename _Reference = _Tp&>
		struct iterator
		{
			typedef _Category	iterator_category;
			typedef _Tp				value_type;
			typedef _Distance	difference_type;
			typedef _Pointer	 pointer;
			typedef _Reference reference;
		};

	template<typename _Iterator>
		struct iterator_traits
		{
			typedef typename _Iterator::iterator_category	iterator_category;
			typedef typename _Iterator::value_type			value_type;
			typedef typename _Iterator::difference_type		difference_type;
			typedef typename _Iterator::pointer				pointer;
			typedef typename _Iterator::reference			reference;
		};

	template<typename _Tp>
		struct iterator_traits<_Tp*>
		{
			typedef random_access_iterator_tag	iterator_category;
			typedef _Tp							value_type;
			typedef __gnu_cxx::ptrdiff_t					difference_type;
			typedef _Tp*						pointer;
			typedef _Tp&						reference;
		};

	template<typename _Tp>
		struct iterator_traits<const _Tp*>
		{
			typedef random_access_iterator_tag	iterator_category;
			typedef _Tp							value_type;
			typedef __gnu_cxx::ptrdiff_t					difference_type;
			typedef const _Tp*					pointer;
			typedef const _Tp&					reference;
		};

	template<typename _Iter>
		typename iterator_traits<_Iter>::iterator_category
		__iterator_category(const _Iter&)
		{
			return (typename iterator_traits<_Iter>::iterator_category());
		}

	template<typename _Iterator, bool _HasBase>
		struct _Iter_base
		{
			typedef _Iterator iterator_type;
			static iterator_type _S_base(_Iterator __it)
			{
				return (__it);
			}
		};

	template<typename _Iterator>
		struct _Iter_base<_Iterator, true>
		{
			typedef typename _Iterator::iterator_type iterator_type;
			static iterator_type _S_base(_Iterator __it)
			{
				return (__it.base());
			}
		};



	template<typename _InputIterator>
		typename iterator_traits<_InputIterator>::difference_type
		__distance(_InputIterator __first, _InputIterator __last,
							 input_iterator_tag)
		{
			typename iterator_traits<_InputIterator>::difference_type __n = 0;
			while (__first != __last)
			{
				++__first;
				++__n;
			}
			return (__n);
		}

	template<typename _RandomAccessIterator>
		typename iterator_traits<_RandomAccessIterator>::difference_type
		__distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
							 random_access_iterator_tag)
		{
			return (__last - __first);
		}

	template<typename _InputIterator>
		inline
		typename iterator_traits<_InputIterator>::difference_type
		distance(_InputIterator __first, _InputIterator __last)
		{
			return (ft::__distance(__first, __last,
					 ft::__iterator_category(__first)));
		}

	template<typename _InputIterator, typename _Distance>
		inline void
		__advance(_InputIterator& __i, _Distance __n, input_iterator_tag)
		{
			while (__n--)
				++__i;
		}

	template<typename _BidirectionalIterator, typename _Distance>
		inline void
		__advance(_BidirectionalIterator& __i, _Distance __n,
				bidirectional_iterator_tag)
		{
			if (__n > 0)
				while (__n--)
					++__i;
			else
				while (__n++)
					--__i;
		}

	template<typename _RandomAccessIterator, typename _Distance>
		inline void
		__advance(_RandomAccessIterator& __i, _Distance __n,
							random_access_iterator_tag)
		{
			__i += __n;
		}

	template<typename _InputIterator, typename _Distance>
		inline void
		advance(_InputIterator& __i, _Distance __n)
		{
			typename iterator_traits<_InputIterator>::difference_type __d = __n;
			ft::__advance(__i, __d, ft::__iterator_category(__i));
		}




	template<typename _Iterator>
		class reverse_iterator
		: public iterator<typename iterator_traits<_Iterator>::iterator_category,
						typename iterator_traits<_Iterator>::value_type,
						typename iterator_traits<_Iterator>::difference_type,
						typename iterator_traits<_Iterator>::pointer,
						typename iterator_traits<_Iterator>::reference>
		{
		protected:
			_Iterator		current;

			typedef iterator_traits<_Iterator>		__traits_type;

		public:
			typedef _Iterator								iterator_type;
			typedef typename __traits_type::difference_type	difference_type;
			typedef typename __traits_type::pointer			pointer;
			typedef typename __traits_type::reference		reference;
			reverse_iterator(void) : current() {}
			reverse_iterator(iterator_type __x) : current(__x) {}
			reverse_iterator(const reverse_iterator& __x) : current(__x.current) {}

			template<typename _Iter>
				reverse_iterator(const reverse_iterator<_Iter>& __x) : current(__x.base()) {}

			iterator_type
			base(void) const
			{
				return (current);
			}

			reference
			operator*	(void) const
			{
				_Iterator __tmp = current;
				return (*(--__tmp));
			}

			// pointer
			// operator->	(void) const
			// {
			// 	return (std::addressof(operator*()));
			// }

			reverse_iterator&
			operator++	(void)
			{
				--current;
				return (*this);
			}

			reverse_iterator
			operator++	(int)
			{
				reverse_iterator __tmp = *this;
				--current;
				return (__tmp);
			}

			reverse_iterator&
			operator--	(void)
			{
				++current;
				return (*this);
			}

			reverse_iterator
			operator--	(int)
			{
				reverse_iterator __tmp = *this;
				++current;
				return (__tmp);
			}

			reverse_iterator
			operator+	(difference_type __n) const
			{
				return (reverse_iterator(current - __n));
			}

			reverse_iterator&
			operator+=	(difference_type __n)
			{
				current -= __n;
				return (*this);
			}

			reverse_iterator
			operator-	(difference_type __n) const
			{
				return (reverse_iterator(current + __n));
			}

			reverse_iterator&
			operator-=	(difference_type __n)
			{
				current += __n;
				return (*this);
			}

			reference
			operator[]	(difference_type __n) const
			{
				return (*(*this + __n));
			}
		};

	template<typename _Iterator>
		inline bool
		operator==	(const reverse_iterator<_Iterator>& __x,
				 const reverse_iterator<_Iterator>& __y)
		{
			return (__x.base() == __y.base());
		}

	template<typename _Iterator>
		inline bool
		operator<	(const reverse_iterator<_Iterator>& __x,
				const reverse_iterator<_Iterator>& __y)
		{
			return (__y.base() < __x.base());
		}

	template<typename _Iterator>
		inline bool
		operator!=	(const reverse_iterator<_Iterator>& __x,
				 const reverse_iterator<_Iterator>& __y)
		{
			return (!(__x == __y));
		}

	template<typename _Iterator>
		inline bool
		operator>	(const reverse_iterator<_Iterator>& __x,
				const reverse_iterator<_Iterator>& __y)
		{
			return (__y < __x);
		}

	template<typename _Iterator>
		inline bool
		operator<=	(const reverse_iterator<_Iterator>& __x,
				 const reverse_iterator<_Iterator>& __y)
		{
			return (!(__y < __x));
		}

	template<typename _Iterator>
		inline bool
		operator>=	(const reverse_iterator<_Iterator>& __x,
				 const reverse_iterator<_Iterator>& __y)
		{
			return (!(__x < __y));
		}


	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator==	(const reverse_iterator<_IteratorL>& __x,
				 const reverse_iterator<_IteratorR>& __y)
		{
			return (__x.base() == __y.base());
		}

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator<	(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (__y.base() < __x.base());
		}

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator!=	(const reverse_iterator<_IteratorL>& __x,
				 const reverse_iterator<_IteratorR>& __y)
		{
			return (!(__x == __y));
		}

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator>	(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (__y < __x);
		}

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator<=	(const reverse_iterator<_IteratorL>& __x,
				 const reverse_iterator<_IteratorR>& __y)
		{
			return (!(__y < __x));
		}

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator>=	(const reverse_iterator<_IteratorL>& __x,
				 const reverse_iterator<_IteratorR>& __y)
		{
			return (!(__x < __y));
		}
	
	template<typename _Iterator>
		inline typename reverse_iterator<_Iterator>::difference_type
		operator-	(const reverse_iterator<_Iterator>& __x,
				const reverse_iterator<_Iterator>& __y)
		{
			return (__y.base() - __x.base());
		}

	template<typename _IteratorL, typename _IteratorR>
		inline typename reverse_iterator<_IteratorL>::difference_type
		operator-	(const reverse_iterator<_IteratorL>& __x,
				const reverse_iterator<_IteratorR>& __y)
		{
			return (__y.base() - __x.base());
		}

	template<typename _Iterator>
		inline reverse_iterator<_Iterator>
		operator+	(typename reverse_iterator<_Iterator>::difference_type __n,
				const reverse_iterator<_Iterator>& __x)
		{
			return (reverse_iterator<_Iterator>(__x.base() - __n));
		}
}

#endif
