# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 11:59:23 by ahamdy            #+#    #+#              #
#    Updated: 2022/05/09 11:59:25 by ahamdy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo.c utils.c error_handling.c initialize.c philo_utils.c

NAME = philo

all : $(NAME)


$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)  -o $(NAME)

# clean :
# 	rm -rf  

fclean : clean
	rm -f $(NAME) 

re : fclean all

.PHONY : all clean fclean re