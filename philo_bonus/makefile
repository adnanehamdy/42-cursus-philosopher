# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 17:19:27 by ahamdy            #+#    #+#              #
#    Updated: 2022/05/12 09:20:46 by ahamdy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo_bonus.c utils.c error_handling.c initialize.c  philo_utils.c

NAME = philo_bonus

all : $(NAME)


$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)  -o $(NAME)

clean : 

fclean : clean
	rm -f $(NAME) 

re : fclean all

.PHONY : all clean fclean re