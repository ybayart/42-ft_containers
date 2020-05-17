/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexa <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:44:02 by hexa              #+#    #+#             */
/*   Updated: 2020/05/17 16:12:05 by hexa             ###   ########.fr       */
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

	template <typename T>
	inline bool
	itcmp	(const T& lhs, const T& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typedef typename T::const_iterator const_iterator;
		const_iterator	it1;
		const_iterator	it2;
		const_iterator	end1;
		const_iterator	end2;

		it1 = lhs.begin();
		it2 = rhs.begin();
		end1 = lhs.end();
		end2 = rhs.end();
		if (it1 == it2 && end1 == end2)
			return (true);
		while (it1 != end1 && it2 != end2 && *it1 == *it2)
		{
			it1++;
			it2++;
		}
		return (*it1 == *it2);
	}

	template <typename T>
	inline bool
	itinf (const T& lhs, const T& rhs)
	{
		typedef typename T::const_iterator const_iterator;
		const_iterator	it1;
		const_iterator	it2;

		it1 = lhs.begin();
		it2 = rhs.begin();
		while (it1 != lhs.end())
		{
			if (it2 == rhs.end() || *it2 < *it1)
				return (false);
			else if (*it1 < *it2)
				return (true);
			++it1;
			++it2;
		}
		return (it2 != rhs.end());
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
