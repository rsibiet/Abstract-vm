/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Avm.class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 12:14:21 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/14 12:14:23 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Avm.class.hpp"

void		Avm::read_file(char *file)
{
	std::ifstream 	ifs (file, std::ifstream::in);
	std::string		line;

	if (ifs.is_open() == false)
		throw Exception("Error: Unable to open file.");
	while (ifs.good())
	{
		std::getline(ifs, line);
		_cmd.push_back(line);
	}
	ifs.close();
  return ;	
}

void		Avm::read_in(void)
{
	std::string	buff;

	while (buff != ";;")
	{
		if (std::cin.fail() || !std::getline(std::cin, buff))
			return ;
		_cmd.push_back(buff);
	}
	return ;
}

Avm::Avm(int ac, char *av[]) : _step(0)
{
	if (ac == 2)
		read_file(av[1]);
	else
		read_in();
	if (_cmd[0] == "!<")
	{
		_cmd.erase(_cmd.begin());
		_step = 1;
	}
	std::cout << "\033[1;32m\nANALYSIS (interpretation excluded):\033[1;31m" << std::endl;
	for (size_t i=0; i<_cmd.size();i++)
		_cmd[i] = _lexer.analyse(_cmd[i], i + 1, 0);
	std::cout << "\033[1;32m----END OF ANALYSIS----\033[0m\n" << std::endl;
	for (size_t i=0; i<_cmd.size();i++)
		_cmd[i] = _lexer.analyse(_cmd[i], i + 1, 1);
	_parser.parse(_cmd, _step);
	return ;
}

Avm::~Avm(void) { return ; }

