/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexa <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:39:13 by hexa              #+#    #+#             */
/*   Updated: 2020/05/04 21:00:50 by hexa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"

int
main(void)
{
	ft::list<int>	toto(50);

	std::cout << "begin() " << *toto.begin() << std::endl;
	std::cout << "end() " << *toto.end() << std::endl;
	std::cout << "empty() " << toto.empty() << std::endl;
	std::cout << "size() " << toto.size() << std::endl;
	std::cout << "max_size() " << toto.max_size() << std::endl;
}
