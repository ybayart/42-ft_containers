/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexa <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:44:02 by hexa              #+#    #+#             */
/*   Updated: 2020/05/06 15:46:02 by hexa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <memory>
# include <iostream>

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
