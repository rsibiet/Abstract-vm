/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 11:23:25 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/20 11:23:27 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.class.hpp"

extern unsigned int line_error;

template<typename T> Operand<T>::Operand(void) { return ; }

template<typename T>Operand<T>::Operand(T value)
{ _value = std::to_string(value); }

template<typename T> Operand<T>::Operand(Operand<T> const & src)
{ static_cast<void>(src); }

template<typename T> Operand<T>::~Operand(void) { return ; }

template<typename T> Operand<T> &	Operand<T>::operator=(Operand<T> const & rhs)
{ _value = rhs._value; return *this; }

template<> eOperandType	Operand<int8_t>::getType(void) const { return Int8; }
template<> eOperandType	Operand<int16_t>::getType(void) const { return Int16; }
template<> eOperandType	Operand<int32_t>::getType(void) const { return Int32; }
template<> eOperandType	Operand<float>::getType(void) const { return Float; }
template<> eOperandType	Operand<double>::getType(void) const { return Double; }

template<typename T> int	Operand<T>::getPrecision(void) const
{ return this->getType(); }

template<typename T> std::string const	stringToReturn(double value, int precision)
{
	std::string		ret;

	if (precision == Int8)
		ret = std::to_string(static_cast<int8_t>(value));
	else if (precision == Int16)
		ret = std::to_string(static_cast<int16_t>(value));
	else if (precision == Int32)
		ret = std::to_string(static_cast<int32_t>(value));
	else if (precision == Float)
		ret = std::to_string(static_cast<float>(value));
	else
		ret = std::to_string(value);
	return ret;
}

template<typename T> double 		maxValue(int precision)
{
	double valMax;

	if (precision == Int8) { valMax = 127; }
	else if (precision == Int16) { valMax = 32767; }
	else if (precision == Int32) { valMax = INT_MAX; }
	else if (precision == Float) { valMax = FLT_MAX; }
	else { valMax = DBL_MAX; }
	return valMax;
}

template<typename T> double 		minValue(int precision)
{
	double valMin;

	if (precision == Int8) { valMin = -128; }
	else if (precision == Int16) { valMin = -32768; }
	else if (precision == Int32) { valMin = INT_MIN; }
	else if (precision == Float) { valMin = FLT_MIN; }
	else { valMin = -DBL_MAX; }
	return valMin;
}

template<typename T> int			getGoodPrecision(IOperand const & lhs, IOperand const & rhs)
{
	if (lhs.getPrecision() < rhs.getPrecision())
		return rhs.getPrecision();
	return lhs.getPrecision();	
}

template<typename T> eOperandType	getGoodType(IOperand const & lhs, IOperand const & rhs)
{
	if (lhs.getPrecision() < rhs.getPrecision())
		return rhs.getType();
	return lhs.getType();	
}

template<typename T> IOperand const *	Operand<T>::operator+(IOperand const & rhs) const
{
	OperandFactory			fact;
	int	precision  		= 	getGoodPrecision<T>(*this, rhs);
	eOperandType type 	= 	getGoodType<T>(*this, rhs);
	double val_lhs 		= 	std::stod(_value);
	double val_rhs 		= 	std::stod(rhs.toString());
	double	valMax 		= 	maxValue<T>(precision);
	double	valMin 		= 	minValue<T>(precision);

	if ((valMax - val_lhs) < val_rhs || (valMax - val_rhs) < val_lhs)
		throw Exception(Error::OVERFLOW_, line_error);
	else if ((valMin - val_lhs) > val_rhs || (valMin - val_rhs) > val_lhs)
		throw Exception(Error::UNDERFLOW_, line_error);
	double sum = val_lhs + val_rhs;
	std::string const	stdSum = stringToReturn<T>(sum, precision);	
	return fact.createOperand(type, stdSum);
}

template<typename T> IOperand const * 	Operand<T>::operator-(IOperand const & rhs) const
{
	OperandFactory			fact;
	int	precision  		= 	getGoodPrecision<T>(*this, rhs);
	eOperandType type 	= 	getGoodType<T>(*this, rhs);
	double val_lhs 		= 	std::stod(_value);
	double val_rhs 		= 	std::stod(rhs.toString());
	double	valMax 		= 	maxValue<T>(precision);
	double	valMin 		= 	minValue<T>(precision);

	if ((valMax - val_lhs) < -val_rhs || (valMax + val_rhs) < val_lhs)
		throw Exception(Error::OVERFLOW_, line_error);
	else if ((valMin - val_lhs) > -val_rhs || (valMin + val_rhs) > val_lhs)
		throw Exception(Error::UNDERFLOW_, line_error);
	double sub = val_lhs - val_rhs;
	std::string const	stdSub = stringToReturn<T>(sub, precision);	
	return fact.createOperand(type, stdSub);
}

template<typename T> IOperand const * 	Operand<T>::operator*(IOperand const & rhs) const
{
	OperandFactory			fact;
	int	precision  		= 	getGoodPrecision<T>(*this, rhs);
	eOperandType type 	= 	getGoodType<T>(*this, rhs);
	double val_lhs 		= 	std::stod(_value);
	double val_rhs 		= 	std::stod(rhs.toString());
	double	valMax 		= 	maxValue<T>(precision);
	double	valMin 		= 	minValue<T>(precision);

	if ((val_lhs > (valMax / val_rhs) && val_lhs > 0 && val_rhs > 0) ||
		(val_lhs < (valMax / val_rhs) && val_lhs < 0 && val_rhs < 0))
		throw Exception(Error::OVERFLOW_, line_error);
	else if ((val_lhs < (valMin / val_rhs) && val_lhs < 0 && val_rhs > 0) ||
			 (val_lhs > (valMin / val_rhs) && val_lhs > 0 && val_rhs < 0))
		throw Exception(Error::UNDERFLOW_, line_error);
	double mul = val_lhs * val_rhs;
	std::string const	stdMul = stringToReturn<T>(mul, precision);	
	return fact.createOperand(type, stdMul);
}

template<typename T> IOperand const * 	Operand<T>::operator/(IOperand const & rhs) const
{
	OperandFactory			fact;
	int	precision  		= 	getGoodPrecision<T>(*this, rhs);
	eOperandType type 	= 	getGoodType<T>(*this, rhs);
	double val_lhs 		= 	std::stod(_value);
	double val_rhs 		= 	std::stod(rhs.toString());
	double	valMax 		= 	maxValue<T>(precision);
	double	valMin 		= 	minValue<T>(precision);

	if (val_rhs == 0)
		throw Exception(Error::DIV_ZERO, line_error);
	else if ((val_rhs < 1 && val_rhs > 0 &&  val_lhs > 0 &&
				val_lhs > (valMax * val_rhs)) ||
			(val_rhs < 0 && val_rhs > -1  && val_lhs < 0 &&
				val_lhs < (valMax * val_rhs)))
		throw Exception(Error::OVERFLOW_, line_error);
	else if ((val_rhs < 1 && val_rhs > 0 && val_lhs < 0 &&
				val_lhs < (valMin * val_rhs)) ||
			(val_rhs < 0 && val_rhs > -1 && val_lhs > 0 &&
				val_lhs > (valMin * val_rhs)))
		throw Exception(Error::UNDERFLOW_, line_error);
	double div = val_lhs / val_rhs;
	std::string const	stdDiv = stringToReturn<T>(div, precision);	
	return fact.createOperand(type, stdDiv);
}

template<typename T> IOperand const * 	Operand<T>::operator%(IOperand const & rhs) const
{
	OperandFactory			fact;
	int	precision  		= 	getGoodPrecision<T>(*this, rhs);
	eOperandType type 	= 	getGoodType<T>(*this, rhs);
	long val_lhs;
	long val_rhs;

	try
	{
		val_lhs	= std::stol(_value);
		val_rhs = std::stol(rhs.toString());
	}
	catch (std::exception & e)
	{
		throw Exception("Error: You can not take a modulo on double or float value out of long range.");
	}
	if (val_rhs == 0)
		throw Exception(Error::DIV_ZERO, line_error);
	double mod = val_lhs % val_rhs;
	std::string const	stdMod = stringToReturn<T>(mod, precision);	
	return fact.createOperand(type, stdMod);
}

template<typename T>	std::string const & Operand<T>::toString(void) const
{ return _value; }

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
