/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:05:33 by rsibiet           #+#    #+#             */
/*   Updated: 2017/09/18 18:05:34 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>
#include <regex>
#include <vector>
#include <climits>
#include <ctype.h>
#include <math.h>
#include <unordered_map>
#include "Exception.class.hpp"
#include "OperandFactory.class.hpp"

class Parser
{
public:
	Parser(void);
	Parser(Parser const & src);
	~Parser(void);

	Parser 		&operator=(Parser const & rhs);

	void		parse(std::vector<std::string> cmd, int step);

private:
	void		PrintChar(void);
	void		DoOperation(void);
	void		pushOrAssertOp(std::string cmd);
	void		dumpStack(int stepMod);
	void		define(std::string cmd);


	std::string 									_inst;
	eOperandType									_type;
	std::string 									_val;
	std::deque<IOperand const *>					_stack;
	OperandFactory									_fact;
	std::unordered_map<std::string, std::string> 	_define;
};