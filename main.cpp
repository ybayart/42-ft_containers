/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexa <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 18:53:42 by hexa              #+#    #+#             */
/*   Updated: 2020/05/14 18:58:33 by hexa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void main_list(void);

void main_vector(void);

int
main(void)
{
	std::cout << "===== LIST =====" << std::endl;
	main_list();
	std::cout << std::endl;

	std::cout << "===== VECTOR =====" << std::endl;
	main_vector();
}
