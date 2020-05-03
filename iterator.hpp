/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexa <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 16:43:10 by hexa              #+#    #+#             */
/*   Updated: 2020/05/03 21:21:48 by hexa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace	ft
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
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
			typedef ptrdiff_t					difference_type;
			typedef _Tp*						pointer;
			typedef _Tp&						reference;
		};

	template<typename _Tp>
		struct iterator_traits<const _Tp*>
		{
			typedef random_access_iterator_tag	iterator_category;
			typedef _Tp							value_type;
			typedef ptrdiff_t					difference_type;
			typedef const _Tp*					pointer;
			typedef const _Tp&					reference;
		};

	template<typename _Iter>
		typename iterator_traits<_Iter>::iterator_category
		__iterator_category(const _Iter&)
		{
			return typename iterator_traits<_Iter>::iterator_category();
		}



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
			return __n;
		}

	template<typename _RandomAccessIterator>
		typename iterator_traits<_RandomAccessIterator>::difference_type
		__distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
							 random_access_iterator_tag)
		{
			return __last - __first;
		}
}


/*Fixed&	Fixed::operator ++ (void)
{
	this->m_value++;
	return (*this);
}

Fixed	Fixed::operator ++ (int)
{
	Fixed	tmp(*this);
	++(*this);
	return (tmp);
}*/


#endif
