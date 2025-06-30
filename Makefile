# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdios-el <mdios-el@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 16:52:00 by mdios-el          #+#    #+#              #
#    Updated: 2025/06/23 16:52:00 by mdios-el         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = src/main.c \
	   src/init.c \
	   src/core.c \
	   src/utils.c \
	   src/cleanup.c \
	   src/monitor.c \
	   src/routine.c

OBJS = $(SRCS:.c=.o)

INCS = -I includes

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
