# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/12 12:09:49 by rsibiet           #+#    #+#              #
#    Updated: 2017/09/12 12:11:23 by rsibiet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

FTC = main.cpp \
	  Avm.class.cpp \
	  Exception.class.cpp \
	  Lexer.class.cpp \
	  Parser.class.cpp \
	  OperandFactory.class.cpp \
	  Operand.class.cpp

FTO = $(FTC:%.cpp=%.o)

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(FTO)
	@echo "\033[32m• $(NAME) created!\n\033[0m"
	@clang++ -Wall -Wextra -Werror -std=c++11 -o $(NAME) $(FTO)

%.o: %.cpp
	@clang++ -Wall -Wextra -Werror -std=c++11 -I/Users/rsibiet/Downloads/boost_1_63_0 -o $@ -c $<

clean:
	@rm -rf $(FTO)
	@echo "\033[33m• $(NAME) object deleted!\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31;1m• \033[31m$(NAME) deleted!\033[0m"

re: fclean all
