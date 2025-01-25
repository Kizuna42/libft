# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 16:03:38 by kizuna            #+#    #+#              #
#    Updated: 2025/01/25 16:20:03 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include

SRCS_DIR = src/
SRCS = $(SRCS_DIR)ft_printf.c \
        $(SRCS_DIR)ft_print_char.c \
        $(SRCS_DIR)ft_print_str.c \
        $(SRCS_DIR)ft_print_ptr.c \
        $(SRCS_DIR)ft_print_nbr.c \
        $(SRCS_DIR)ft_print_unsigned.c \
        $(SRCS_DIR)ft_print_hex.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(LIBFT) $(OBJS)
	ar x $(LIBFT)
	ar rcs $(NAME) *.o $(OBJS)
	rm -f *.o

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
