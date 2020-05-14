/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexa <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:44:02 by hexa              #+#    #+#             */
/*   Updated: 2020/05/14 16:48:48 by hexa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <memory>
# include <iostream>
# include <cstddef>
# include <limits>

namespace ft
{
	template <typename T>
	void
	swap(T& a, T& b)
	{
		T	c;

		c = a;
		a = b;
		b = c;
	}

	struct true_type {};
	struct false_type {};

	template<typename _Tp>
		struct is_integer
		{
			enum { value = 0 };
			typedef false_type type;
		};

	template<>
		struct is_integer<bool>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<char>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<signed char>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned char>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<short>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned short>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<int>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned int>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<long>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned long>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<long long>
		{
			enum { value = 1 };
			typedef true_type type;
		};

	template<>
		struct is_integer<unsigned long long>
		{
			enum { value = 1 };
			typedef true_type type;
		};
}

# include "iterator.hpp"
# include "list.hpp"
# include "vector.hpp"


#endif
