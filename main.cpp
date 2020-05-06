/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexa <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:39:13 by hexa              #+#    #+#             */
/*   Updated: 2020/05/06 04:59:54 by hexa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void
print_it(ft::list<int>& toto)
{
	ft::list<int>::iterator it;
	ft::list<int>::reverse_iterator itr;

	std::cout << std::endl;
	it = toto.begin();
	itr = toto.rbegin();
	for (;it != toto.end();it++, itr++)
		std::cout << "  iterator " << *it << " - " << *itr << std::endl;

	std::cout << std::endl;
	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "   first() " << toto.front() << std::endl;
	std::cout << "    back() " << toto.back() << std::endl;
}

int
main(void)
{
	ft::list<int>	toto;

	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "max_size() " << toto.max_size() << std::endl;
	
	toto.push_back(1);
	toto.push_back(2);
	toto.push_back(3);
	toto.push_back(4);
	toto.push_back(5);
	toto.push_front(6);
	toto.push_back(7);

	print_it(toto);

	toto.pop_front();
	toto.pop_back();

	print_it(toto);
}
