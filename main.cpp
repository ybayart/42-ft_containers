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

bool
remove_666(int val)
{
	return (val != 666);
}

void
print_it(ft::list<int>& toto)
{
	ft::list<int>::iterator it;
	ft::list<int>::reverse_iterator itr;

	it = toto.begin();
	itr = toto.rbegin();
	for (;it != toto.end();it++, itr++)
		std::cout << "  iterator " << *it << " - " << *itr << std::endl;

	std::cout << std::endl;
	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	if (toto.empty() == 0)
		std::cout << "  extrem() " << toto.front() << " >> " << toto.back() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

int
main(void)
{
	ft::list<int>	toto;

	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "max_size() " << toto.max_size() << std::endl;
	
	std::cout << "---1" << std::endl;
	toto.push_back(1);
	toto.push_back(4);
	toto.push_back(2);
	toto.push_back(3);
	toto.push_back(5);
	toto.push_front(6);
	toto.push_back(7);
	print_it(toto);

	std::cout << "---2" << std::endl;
	toto.pop_front();
	toto.pop_back();
	print_it(toto);

	std::cout << "---3" << std::endl;
	ft::list<int>::iterator it;
	it = toto.begin();
	for (int i = 0;i < 4;i++)
		it++;
	toto.insert(it, 8, 42);
	print_it(toto);

	std::cout << "---4" << std::endl;
	it = toto.erase(--it, toto.end());
	print_it(toto);

	std::cout << "---5" << std::endl;
	ft::list<int>	tata(5, 42);
	toto.swap(tata);
	print_it(toto);
	print_it(tata);

	std::cout << "---6" << std::endl;
	toto.resize(10, 99);
	print_it(toto);

	std::cout << "---7" << std::endl;
	toto.resize(6);
	print_it(toto);

	std::cout << "---8" << std::endl;
	toto.clear();
	print_it(toto);

	std::cout << "---9" << std::endl;
	print_it(tata);
	tata.remove(1);
	tata.remove(42);
	print_it(tata);

	std::cout << "---10" << std::endl;
	tata.assign(5, 666);
	tata.remove_if(remove_666);
	print_it(tata);

	std::cout << "---11" << std::endl;
	tata.insert(tata.begin(), 4, 42);
	tata.insert(tata.end(), 3, 84);
	tata.push_back(666);
	tata.unique();
	print_it(tata);

	std::cout << "---12" << std::endl;
	tata.sort();
	tata.unique();
	print_it(tata);

	std::cout << "---13" << std::endl;
	toto.push_back(-214748368);
	toto.push_back(0);
	toto.push_back(50);
	toto.push_back(100);
	toto.push_back(8000);
	toto.push_back(2147483647);
	tata.merge(toto);
	print_it(tata);

	std::cout << "---14" << std::endl;
	tata.reverse();
	print_it(tata);

	std::cout << "---15" << std::endl;
	toto.push_front(8888);
	toto.push_front(8888);
	std::cout << "tata" << std::endl;
	print_it(tata);
	std::cout << "toto" << std::endl;
	print_it(toto);
	it = toto.begin();
	it++;
	std::cout << "toto == tata: " << (toto == tata) << " != " << (toto != tata) << std::endl;
	std::cout << "toto == toto: " << (toto == toto) << " != " << (toto != toto) << std::endl;
	std::cout << "tata == tata: " << (tata == tata) << " != " << (tata != tata) << std::endl;

	std::cout << "toto < tata: " << (toto < tata) << std::endl;
	std::cout << "toto > tata: " << (toto > toto) << std::endl;
	std::cout << "toto <= toto: " << (toto <= toto) << std::endl;
	std::cout << "toto >= toto: " << (toto >= toto) << std::endl;
}
