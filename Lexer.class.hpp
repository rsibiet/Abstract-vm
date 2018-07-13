/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 11:19:09 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/15 11:19:11 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <regex>
#include <vector>
#include <unordered_map>
#include "Exception.class.hpp"

class Lexer
{
public:
	Lexer(void);
	Lexer(Lexer const & src);
	~Lexer(void);

	Lexer 			&operator=(Lexer const &);
	std::string 	analyse(std::string line, unsigned int nb, int mod);

private:
	void			except(Error err, unsigned int nb, int mod);
	std::string		analyse_syntax(std::string line, unsigned int nb, int mod);
	std::string		define(std::string line, unsigned int nb, int mod);

	static std::vector<std::string> const			_instruction;
	std::unordered_map<std::string, std::string> 	_define;

};