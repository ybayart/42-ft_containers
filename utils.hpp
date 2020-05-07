/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexa <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:44:02 by hexa              #+#    #+#             */
/*   Updated: 2020/05/07 14:35:40 by hexa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <memory>
# include <iostream>
# include <cstddef>

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
}

# include "iterator.hpp"
# include "list.hpp"


#endif
