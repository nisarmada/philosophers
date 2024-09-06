# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsarmada <nsarmada@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/08/06 14:25:39 by nsarmada      #+#    #+#                  #
#    Updated: 2024/09/06 15:08:07 by nsarmada      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = philo.c philo_utils.c utils_2.c utils_3.c eating.c main.c

OBJ = $(SRC:.c=.o)

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: fclean all

.PHONY: all clean fclean re