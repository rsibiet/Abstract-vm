/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.class.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:31:19 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/20 12:31:20 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <climits>
#include "Exception.class.hpp"
#include "Operand.class.hpp"
#include <stdint.h>

class OperandFactory
{
public:
	typedef IOperand const * (OperandFactory::*F_POINT)(std::string const & value) const;

	OperandFactory(void);
	OperandFactory(OperandFactory const & src);
	~OperandFactory(void);

	OperandFactory		&operator=(OperandFactory const & rhs);
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private:
	int					convertToInt(std::string const & value) const;
	void				throwException(char c) const;

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

};
