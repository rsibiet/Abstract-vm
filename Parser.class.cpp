/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:05:28 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/18 18:05:29 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.class.hpp"
extern unsigned int		line_error;

Parser::Parser(void) { return ; }

Parser::Parser(Parser const & src)
{ *this = src; return ; }

Parser::~Parser(void) { return ; }

Parser 		&Parser::operator=(Parser const & rhs)
{ static_cast<void>(rhs); return *this; }

void		Parser::pushOrAssertOp(std::string cmd)
{
 	std::regex int8Val("int8\\(([-]?)[[:digit:]]+\\)");
 	std::regex int16Val("int16\\(([-]?)[[:digit:]]+\\)");
 	std::regex int32Val("int32\\(([-]?)[[:digit:]]+\\)");
 	std::regex floatVal("float\\(([-]?)[[:digit:]]+([.]){1}[[:digit:]]+\\)");
 	std::regex doubleVal("double\\(([-]?)[[:digit:]]+([.]){1}[[:digit:]]+\\)");
    _val = cmd.substr(cmd.find(" ") + 1);
    if (!_define[_val].empty())
    	_val = _define[_val];
    if (_val == "INT_MAX") {
    	_val = std::to_string(INT_MAX);
    	_type = Int32;
    }
    else if (_val == "INT_MIN") {
    	_val = std::to_string(INT_MIN);
    	_type = Int32;
    }
    else if (regex_match(_val, int8Val)) {
    	_val = _val.substr(5, _val.find(")") - 5);
    	_type = Int8;
    }
	else if (regex_match(_val, int16Val)) {
    	_val = _val.substr(6, _val.find(")") - 6);
    	_type = Int16;
	}
	else if (regex_match(_val, int32Val)) {
    	_val = _val.substr(6, _val.find(")") - 6);
    	_type = Int32;
	}
    else if (regex_match(_val, floatVal)) {
    	_val = _val.substr(6, _val.find(")") - 6);
    	_type = Float;
	}
	else if (regex_match(_val, doubleVal)) {
    	_val = _val.substr(7, _val.find(")") - 7);
    	_type = Double;
	}
	IOperand const *res = _fact.createOperand(_type, _val);
	if (_inst == "push")
		_stack.push_back(res);
	else
	{
		if (res->toString() != _stack.back()->toString() ||
				res->getType() != _stack.back()->getType())
			throw Exception(Error::ASSERT, line_error);
	}
}

void		Parser::DoOperation(void)
{
	if (_stack.size() < 2)
		throw Exception(Error::LESS_THAT_TWO, line_error);
	else if (_inst == "add")
		_stack[_stack.size() - 2] = *_stack[_stack.size() - 2] + *_stack.back();
	else if (_inst == "sub")
		_stack[_stack.size() - 2] = *_stack[_stack.size() - 2] - *_stack.back();
	else if (_inst == "mul")
		_stack[_stack.size() - 2] = *_stack[_stack.size() - 2] * *_stack.back();
	else if (_inst == "div")
		_stack[_stack.size() - 2] = *_stack[_stack.size() - 2] / *_stack.back();
	else if (_inst == "mod")
		_stack[_stack.size() - 2] = *_stack[_stack.size() - 2] % *_stack.back();
	_stack.pop_back();
}

void		Parser::PrintChar(void)
{
	int8_t tmp;

	if (_stack.empty() == true)
		throw Exception(Error::EMPTY_PRINT, line_error);
	else if (_stack.back()->getType() != Int8)
		throw Exception(Error::NOT_8_BIT_INT, line_error);
	tmp = static_cast<int8_t>(std::stoi(_stack.back()->toString()));
	if (tmp < 32 || tmp > 126)
		throw Exception(Error::NO_DISPLAYABLE, line_error);
	std::cout << tmp << std::endl;
}

void		Parser::dumpStack(int stepMod)
{
	static std::string tab[] =
	{
		"int8_t",
		"int16_t",
		"int32_t",
		"float",
		"double"
	};
	for (int i = _stack.size() - 1; i >= 0; i--) {
		if (stepMod == 1)
		{
			std::cout << "\033[1;37m--> Type : " << tab[_stack[i]->getType()];
			std::cout << ", Value: ";
		}
		std::cout << _stack[i]->toString() << "\033[0m"<< std::endl;
	}
}

void		Parser::define(std::string cmd)
{
	std::pair<std::string, std::string> pair;
	pair.first = cmd.substr(cmd.find(" ") + 1);
    pair.second = pair.first.substr(pair.first.find(" ") + 1);
    pair.first = pair.first.substr(0, pair.first.find(" "));

    if (_define.find(pair.first) == _define.end())
    	_define.insert(pair);
    else
    	_define[pair.first] = pair.second;
}

void		Parser::parse(std::vector<std::string> cmd, int step)
{
	int c;

	for (size_t i=0; i<cmd.size();i++)
	{
		line_error = i + 1 + step;
		_inst = cmd[i].substr(0, cmd[i].find(" ")); // split line with " "
		if (_inst == "define")
			define(cmd[i]);
		else if (_inst == "push")
			pushOrAssertOp(cmd[i]);
		else if (_inst == "pop")
		{
			if (_stack.empty() == true)
				throw Exception(Error::EMPTY, line_error);
			_stack.pop_back();
		}
		else if (_inst == "dump")
			dumpStack(0);
		else if (_inst == "assert")
			pushOrAssertOp(cmd[i]);
		else if (_inst == "exit")
			return ;
		else if (_inst == "print")
			PrintChar();
		else if (_inst.empty() != true && _inst[0] != ';')
			DoOperation();
		if (step == 1)
		{
			std::cout << "\033[1;34mLine " << i + 2 << ": Content of the stack :\033[0m" << std::endl;
			dumpStack(1);
			do c = getchar(); while ((c != '\n') && (c != EOF));
		}
	}
	throw Exception(Error::NOT_EXIT, 0);
}
