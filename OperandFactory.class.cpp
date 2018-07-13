/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.class.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:31:13 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/20 12:31:14 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.class.hpp"

unsigned int		line_error;

OperandFactory::OperandFactory(void) { return ; }

OperandFactory::OperandFactory(OperandFactory const & src) 
{ static_cast<void>(src); }

OperandFactory::~OperandFactory(void) {	return ; }

OperandFactory		&OperandFactory::operator=(OperandFactory const & rhs)
{ static_cast<void>(rhs); return *this; }

void				OperandFactory::throwException(char c) const
{
	if (c == '-')
    	throw Exception(Error::UNDERFLOW_, line_error);
    else
    	throw Exception(Error::OVERFLOW_, line_error);
}

int					OperandFactory::convertToInt(std::string const & value) const
{
	int ret;
	try
	{
		ret = std::stoi(value);
	}
	catch (std::exception & e)
	{
		throwException(value[0]);
	}
	return ret;
}
	
IOperand const * OperandFactory::createInt8(std::string const & value) const
{
	int ret = convertToInt(value);
	if (ret < -128)
    	throw Exception(Error::UNDERFLOW_, line_error);
    else if (ret > 127)
    	throw Exception(Error::OVERFLOW_, line_error);
	return new Operand<int8_t>(ret);
}

IOperand const * OperandFactory::createInt16(std::string const & value) const
{
	int ret = convertToInt(value);
	if (ret < -32768)
    	throw Exception(Error::UNDERFLOW_, line_error);
    else if (ret > 32767)
    	throw Exception(Error::OVERFLOW_, line_error);
	return new Operand<int16_t>(ret);
}

IOperand const * OperandFactory::createInt32(std::string const & value) const
{
	int ret = convertToInt(value);
	return new Operand<int32_t>(ret);
}

IOperand const * OperandFactory::createFloat(std::string const & value) const
{
	float ret;
	try
	{
		ret = std::stof(value);
	}
	catch (std::exception & e)
	{
		throwException(value[0]);
	}
	return new Operand<float>(ret);
}

IOperand const * OperandFactory::createDouble(std::string const & value) const
{
	double ret;
	try
	{
		ret = std::stod(value);
	}
	catch (std::exception & e)
	{
		throwException(value[0]);
	}
	return new Operand<double>(ret);
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	static F_POINT fct_array[] =
	{
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble
	};
	IOperand const * new_operand = (this->*fct_array[type])(value);
	return new_operand;
}
