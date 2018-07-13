/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 12:11:38 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/12 12:11:42 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Avm.class.hpp"

int			main(int ac, char *av[])
{
	if (ac > 2)
		std::cout << "Too much arguments. avm need 0 or 1 argument." << std::endl;
	else
		try
		{
			Avm		op(ac, av);
			return 0;
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	return -1;
}
