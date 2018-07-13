/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Avm.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 12:14:26 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/14 12:14:27 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <vector>
#include "Exception.class.hpp"
#include "Lexer.class.hpp"
#include "Parser.class.hpp"

class Avm
{
public:
	Avm(int ac, char *av[]);
	Avm(Avm const & src) = delete;
	~Avm(void);
	
	Avm &operator=(Avm const &) = delete;

private:

	void		read_file(char *file);
	void		read_in(void);

	std::vector<std::string>	_cmd;
	Lexer						_lexer;
	Parser						_parser;
	int							_step;
};