/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 14:41:29 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/14 14:41:30 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.class.hpp"

Exception::Exception(const char *ex) throw()
{ _except = ex;	return ; }

// std::to_string(line)
Exception::Exception(Error err, unsigned int nb) throw()
{
	if (err != Error::NOT_EXIT)
		std::cout << "Line " << nb << ": ";
	if (err == Error::SYNTAX)
		_except = "\033[1;33mLexical error or Syntactic error.\033[0m";
	else if (err == Error::UNKNOW)
		_except = "\033[1;33mUnknown instruction.\033[0m";
	else if (err == Error::OVERFLOW_)
		_except = "\033[1;31mOverflow on a value or the result of an operation.\033[0m";	
	else if (err == Error::UNDERFLOW_)
		_except = "\033[1;31mUnderflow on a value or the result of an operation.\033[0m";
	else if (err == Error::EMPTY)
		_except = "\033[1;36mPop on an empty stack.\033[0m";
	else if (err == Error::DIV_ZERO)
		_except = "\033[1;31mDivision/modulo by 0.\033[0m";
	else if (err == Error::NOT_EXIT)
		_except = "\033[1;36mThe program doesn’t have an exit instruction.\033[0m";
	else if (err == Error::ASSERT)
		_except = "\033[1;36mAssert instruction is not true.\033[0m";
	else if (err == Error::LESS_THAT_TWO)
		_except = "\033[1;36mThe stack is composed of strictly less that two values when an arithmetic instruction is executed.\033[0m";
	else if (err == Error::NOT_8_BIT_INT)
		_except = "\033[1;36mYou can not print other value than 8-bit integer.\033[0m";
	else if (err == Error::EMPTY_PRINT)
		_except = "\033[1;36mEmpty stack. Nothing to print.\033[0m";
	else if (err == Error::NO_DISPLAYABLE)
		_except = "\033[1;36mCorresponding character of this ASCII value is not displayable.\033[0m";
	return ;
}

Exception::~Exception(void) throw() { return ; }

const char		*Exception::what(void) const throw() { return (_except); }
