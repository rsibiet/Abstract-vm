/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 14:41:36 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/14 14:41:37 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stdexcept>
#include <iostream>
#include <string>

enum class Error
{
	SYNTAX,
	UNKNOW,
	OVERFLOW_,
	UNDERFLOW_,
	EMPTY,
	DIV_ZERO,
	NOT_EXIT,
	ASSERT,
	LESS_THAT_TWO,
	NOT_8_BIT_INT,
	EMPTY_PRINT,
	NO_DISPLAYABLE
};

class Exception : public std::exception
{

public:
	Exception(const char *ex) throw();
	Exception(Error err, unsigned int nb) throw();
	Exception(Exception const & src) = default;
	Exception &operator=(Exception const &) = delete;
	virtual ~Exception(void) throw();
	virtual const char* what(void) const throw();

private:
	const char		*_except;

};
