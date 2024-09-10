# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 10:43:43 by wait-bab          #+#    #+#              #
#    Updated: 2024/01/14 11:18:19 by wait-bab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#>>> creation library
NAME = libft.a
#>>> all functions
SRC = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_calloc.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strnstr.c ft_atoi.c ft_strncmp.c ft_strdup.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_strlcat.c ft_memchr.c ft_memcmp.c\
	ft_substr.c ft_split.c ft_itoa.c ft_strjoin.c ft_strtrim.c\
	ft_strmapi.c ft_striteri.c
	



#bonus
SRC_BONUS = \
			ft_lstnew_bonus.c\
			ft_lstadd_front_bonus.c\
			ft_lstsize_bonus.c\
			ft_lstlast_bonus.c\
			ft_lstadd_back_bonus.c\
			ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c\
			ft_lstiter_bonus.c\
			ft_lstmap_bonus.c


# >>> compiling

AR = ar rcs  
CC = cc
HEADER = libft.h
CFLAGS = -Wall -Wextra -Werror 
# >>> object .c to .o
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $? 

bonus: $(OBJ_BONUS)
	$(AR) $(NAME) $?

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $<
	
clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re