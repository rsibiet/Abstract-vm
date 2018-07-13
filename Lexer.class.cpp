/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 11:19:04 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/15 11:19:05 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.class.hpp"
#include <iostream>

Lexer::Lexer(void) { return ; }

Lexer::~Lexer(void) { return ; }

Lexer::Lexer(Lexer const & src)
{ *this = src; return ; }

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void			Lexer::except(Error err, unsigned int nb, int mod)
{
	if (mod == 0)
	{
		std::cout << "Line " << nb << ": ";
		if (err == Error::SYNTAX)
			std::cout << "Lexical error or Syntactic error." << std::endl;
		else if (err == Error::UNKNOW)
			std::cout << "Unknown instruction." << std::endl;
		return ;
	}
	throw Exception(err, nb);
}

std::string		Lexer::analyse_syntax(std::string line, unsigned int nb, int mod)
{
 	std::regex int8Val("int8\\(([-]?)[[:digit:]]+\\)");
 	std::regex int16Val("int16\\(([-]?)[[:digit:]]+\\)");
 	std::regex int32Val("int32\\(([-]?)[[:digit:]]+\\)");
 	std::regex floatVal("float\\(([-]?)[[:digit:]]+([.]){1}[[:digit:]]+\\)");
 	std::regex doubleVal("double\\(([-]?)[[:digit:]]+([.]){1}[[:digit:]]+\\)");
    std::string val = line.substr(line.find(" ") + 1);
    if (!_define[val].empty())
    	return line;
    if (val != "INT_MAX" && val != "INT_MIN" &&
    	!regex_match(val, int8Val) && !regex_match(val, int16Val) &&
    	!regex_match(val, int32Val) && !regex_match(val, floatVal) &&
    	!regex_match(val, doubleVal))
		except(Error::SYNTAX, nb, mod);
	return line;
}

std::string		Lexer::define(std::string line, unsigned int nb, int mod)
{
		std::pair<std::string, std::string> pair;
		pair.first = line.substr(line.find(" ") + 1);
    	pair.second = pair.first.substr(pair.first.find(" ") + 1);
    	pair.first = pair.first.substr(0, pair.first.find(" "));
    	std::string end = pair.second.substr(0, pair.second.find(" "));

    	if (pair.first.empty() || pair.second.empty() || pair.second != end)
			except(Error::SYNTAX, nb, mod);
		_define.insert(pair);
	return line;
}

std::string		Lexer::analyse(std::string line, unsigned int nb, int mod)
{
	if (nb == 1)
		_define.clear();
	if (line == ";;")
		return line ;
	line = line.substr(0, line.find(";")); // split line with ";"
	rtrim(line);
	std::string inst = line.substr(0, line.find(" ")); // split line with " "
	for (size_t i=0; i<_instruction.size();i++)
	{
		if (inst.empty() == true || inst[0] == ';')
			return line;
		if (inst == _instruction[i])
		{
			if (inst == "define")
				return define(line, nb, mod);
			else if (inst == "push" || inst == "assert")
				return analyse_syntax(line, nb, mod);
			else if (inst != line)
			{
				except(Error::SYNTAX, nb, mod);
				return line;
			}
			else
				return line;
		}
	}
	if (line.size() == 0 || line[0] != ';')
		except(Error::UNKNOW, nb, mod);
	return line;
}

Lexer 		&Lexer::operator=(Lexer const &)
{ return *this; }

std::vector<std::string> const	Lexer::_instruction
{
	"define",
	"push",
	"pop",
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit"
};
