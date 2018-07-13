/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 11:23:33 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/20 11:23:35 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <climits>
#include <ctype.h>
#include <cmath>
#include <float.h>
#include "Exception.class.hpp"
#include "IOperand.interface.hpp"
#include "OperandFactory.class.hpp"

template <typename T> class Operand : public IOperand
{
public:
	Operand(void);
	Operand(T value);
	Operand(Operand const & src);
	~Operand(void);

	Operand		&operator=(Operand const & rhs);

	int 				getPrecision(void) const;		// Precision of the type of the instance
	eOperandType 		getType(void) const;	// Type of the instance

	IOperand const * operator+(IOperand const & rhs) const; // Sum
	IOperand const * operator-(IOperand const & rhs) const; // Difference 
	IOperand const * operator*(IOperand const & rhs) const; // Product
	IOperand const * operator/(IOperand const & rhs) const; // Quotient
	IOperand const * operator%(IOperand const & rhs) const; // Modulo

  	std::string const & toString(void) const; // String representation of the instance

private:
	std::string			_value;

};

