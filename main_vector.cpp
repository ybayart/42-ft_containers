/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexa <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:39:13 by hexa              #+#    #+#             */
/*   Updated: 2020/07/06 16:48:27 by YanYan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <vector>

template <typename T>
static void
print_it(T& toto)
{
	typename T::iterator it;
	typename T::reverse_iterator itr;

	it = toto.begin();
	itr = toto.rbegin();
	for (;it != toto.end();it++, itr++)
		std::cout << "  iterator " << *it << " - " << *itr << std::endl;

	std::cout << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "capacity() " << toto.capacity() << std::endl;
	std::cout << "   empty() " << toto.empty() << std::endl;
//	if (toto.empty() == 0)
//		std::cout << "  extrem() " << toto.front() << " >> " << toto.back() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

void
main_vector(void)
{
	NAMESPACE::vector<int>	toto;

	std::cout << "max_size() " << toto.max_size() << std::endl;
	print_it(toto);

	NAMESPACE::vector<int>	tata(10, 42);

	std::cout << "max_size() " << tata.max_size() << std::endl;
	print_it(tata);

	tata.resize(5);
	print_it(tata);

	tata.resize(8);
	print_it(tata);

	tata.resize(11, 666);
	print_it(tata);

	for (size_t i = 0;i < tata.size();i++)
		std::cout << i << " -> " << tata[i] << " | " << tata.at(i) << std::endl;
	try
	{
		tata.at(11);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "front: " << tata.front() << std::endl <<
					"back: " << tata.back() << std::endl << std::endl;

	toto.assign(5, 6);
	print_it(toto);

	toto.assign(15, 60);
	print_it(toto);

	toto.assign(tata.begin(), tata.end());
	print_it(toto);

	toto.pop_back();
	toto.pop_back();
	toto.pop_back();
	toto.pop_back();
	toto.pop_back();
	print_it(toto);

	for (int i = -42;i < -30;i++)
		toto.push_back(i);
	print_it(toto);

	while (toto.size() > 0)
		toto.pop_back();
	for (int i = 0;i < 10;i++)
		toto.push_back(i);
	NAMESPACE::vector<int>::iterator it;
	it = toto.begin();
	it += 4;
	std::cout << "it: " << *it << std::endl;
	std::cout << "it: " << *(toto.insert(it, 80)) << std::endl;
	std::cout << "it: " << *(toto.insert(toto.end(), 80)) << std::endl;
	print_it(toto);

	toto.insert(toto.end(), 10, 42);
	print_it(toto);

	it = toto.begin();
	it += 5;
	toto.insert(it, 5, -666);
	print_it(toto);

	it = toto.begin();
	it += 6;
	toto.insert(it, tata.begin(), tata.end());
	print_it(toto);

	it = toto.begin();
	it += 2;
	std::cout << *(toto.erase(it)) << std::endl;
	print_it(toto);

	std::cout << *(toto.erase(toto.end() - 1)) << std::endl;
	print_it(toto);

	std::cout << *(toto.erase(toto.begin() + 10, toto.end() - 5)) << std::endl;
	print_it(toto);

	std::cout << *(toto.erase(toto.end() - 6, toto.end() - 1)) << std::endl;
	print_it(toto);

	toto.swap(tata);
	print_it(toto);
	print_it(tata);

	std::cout << "toto == tata: " << (toto == tata) << " != " << (toto != tata) << std::endl;
	std::cout << "toto == toto: " << (toto == toto) << " != " << (toto != toto) << std::endl;
	std::cout << "tata == tata: " << (tata == tata) << " != " << (tata != tata) << std::endl;

	std::cout << "toto < tata: " << (toto < tata) << std::endl;
	std::cout << "toto > tata: " << (toto > toto) << std::endl;
	std::cout << "toto <= toto: " << (toto <= toto) << std::endl;
	std::cout << "toto >= toto: " << (toto >= toto) << std::endl;

	toto.clear();
	tata.clear();
	print_it(toto);
	print_it(tata);
}
