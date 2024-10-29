# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmoran <lmoran@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/16 03:44:44 by lmoran            #+#    #+#              #
#    Updated: 2024/07/11 17:30:28 by lmoran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#...............................................#

NAME	= philo
CC		= @clang -g3
CFLAGS	= -Wall -Werror -Wextra
RM		= @rm -f
CLEAR	= @clear
FILE	= $(shell ls -l src/ | grep -F .c | wc -l)
HEAD	= ./include/philo.h
CMP		= 1

#...............................................#

SRC	= 	main.c\
		utils.c\
		monit.c\
		inits.c\
		routines.c\
		threads.c
		
OBJ	= $(SRC:.c=.o)

#...............................................#

BOLD	= 	\e[1m
FADE	=	\e[2m
ITA		=	\e[3m
BLINK	=	\e[5m
GREEN	=	\e[38;5;76m
RED		=	\e[38;5;196m
YELLOW	=	\e[38;5;227m
ORANGE	=	\e[38;5;208m
PURPLE	=	\e[38;5;201m
LBLUE	=	\e[38;5;45m
BLUE	=	\e[38;5;27m
INDI	=	\e[38;5;91m
SPINK	=	\e[38;5;225m
PEACH	=	\e[38;5;223m
GREY	=	\e[38;5;254m
RESET	=	\e[00m

#...............................................#

RNBW	= @printf "                                                          \r$(ITA)$(GREEN)ti$(LBLUE)me $(BLUE)to$(INDI) ph$(PURPLE)il$(RED)os$(ORANGE)oph$(YELLOW)y!\n\r$(GREEN). $(LBLUE). $(BLUE). $(INDI). $(PURPLE). $(RED). $(ORANGE). $(YELLOW). $(GREEN). $(LBLUE). $(BLUE). $(INDI).                      \n\n"

all: $(NAME)

%.o: %.c $(HEAD)
	@printf "\r$(FADE)$(SPINK)Compiling $(RESET)$(GREEN)$<$(BLUE) [$(SPINK)$(CMP)$(BLUE)/$(SPINK)$(FILE)$(BLUE)]$(RESET)                       \r"
	$(CC) $(CFLAGS) -c $< -o $@
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(PRINT_NAME) -lXext -lX11 -lm -lz -o $(NAME) $(MLX)
	$(RNBW)

clean:
	$(RM) $(OBJ)
	@printf "\r\n\r$(BOLD)$(GREEN)ALL CLEAN!     \n\n$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@printf "\b\b$(FADE)$(RED)(F'D!)$(RESET)\n\n"

re: fclean all

.PHONY: 
	all clean fclean re