# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 16:01:19 by kizuna            #+#    #+#              #
#    Updated: 2025/01/25 16:13:20 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I.

SRCS_DIR = src/
FT_IS_DIR = $(SRCS_DIR)ft_is/
FT_LST_DIR = $(SRCS_DIR)ft_lst/
FT_MEM_DIR = $(SRCS_DIR)ft_mem/
FT_PUT_DIR = $(SRCS_DIR)ft_put/
FT_STR_DIR = $(SRCS_DIR)ft_str/
FT_TO_DIR = $(SRCS_DIR)ft_to/

SRCS = $(FT_IS_DIR)ft_isalnum.c \
		$(FT_IS_DIR)ft_isalpha.c \
		$(FT_IS_DIR)ft_isascii.c \
		$(FT_IS_DIR)ft_isdigit.c \
		$(FT_IS_DIR)ft_isprint.c \
		$(FT_TO_DIR)ft_atoi.c \
		$(FT_TO_DIR)ft_itoa.c \
		$(FT_TO_DIR)ft_tolower.c \
		$(FT_TO_DIR)ft_toupper.c \
		$(FT_MEM_DIR)ft_bzero.c \
		$(FT_MEM_DIR)ft_calloc.c \
		$(FT_MEM_DIR)ft_memchr.c \
		$(FT_MEM_DIR)ft_memcmp.c \
		$(FT_MEM_DIR)ft_memcpy.c \
		$(FT_MEM_DIR)ft_memmove.c \
		$(FT_MEM_DIR)ft_memset.c \
		$(FT_PUT_DIR)ft_putchar_fd.c \
		$(FT_PUT_DIR)ft_putendl_fd.c \
		$(FT_PUT_DIR)ft_putnbr_fd.c \
		$(FT_PUT_DIR)ft_putstr_fd.c \
		$(FT_STR_DIR)ft_split.c \
		$(FT_STR_DIR)ft_strchr.c \
		$(FT_STR_DIR)ft_strdup.c \
		$(FT_STR_DIR)ft_strjoin.c \
		$(FT_STR_DIR)ft_strlcat.c \
		$(FT_STR_DIR)ft_strlcpy.c \
		$(FT_STR_DIR)ft_strlen.c \
		$(FT_STR_DIR)ft_strmapi.c \
		$(FT_STR_DIR)ft_strncmp.c \
		$(FT_STR_DIR)ft_strnstr.c \
		$(FT_STR_DIR)ft_strrchr.c \
		$(FT_STR_DIR)ft_strtrim.c \
		$(FT_STR_DIR)ft_substr.c \
		$(FT_STR_DIR)ft_striteri.c

BONUS = $(FT_LST_DIR)ft_lstnew_bonus.c \
		$(FT_LST_DIR)ft_lstadd_front_bonus.c \
		$(FT_LST_DIR)ft_lstsize_bonus.c \
		$(FT_LST_DIR)ft_lstlast_bonus.c \
		$(FT_LST_DIR)ft_lstadd_back_bonus.c \
		$(FT_LST_DIR)ft_lstdelone_bonus.c \
		$(FT_LST_DIR)ft_lstclear_bonus.c \
		$(FT_LST_DIR)ft_lstiter_bonus.c \
		$(FT_LST_DIR)ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus