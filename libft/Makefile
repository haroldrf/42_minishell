# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 18:55:20 by hruiz-fr          #+#    #+#              #
#    Updated: 2024/10/06 16:59:35 by htharrau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Define the compiler, compiler flags and the archive tool
CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror

# Name of the static library
NAME = libft.a
HEADER = libft.h

# All my mandatory .c files
SOURCES = ft_atoi.c \
ft_isdigit.c \
ft_memmove.c \
ft_split.c \
ft_strlcpy.c \
ft_strtrim.c \
ft_bzero.c \
ft_isprint.c \
ft_memset.c \
ft_strchr.c \
ft_strlen.c \
ft_substr.c \
ft_calloc.c \
ft_itoa.c \
ft_putchar_fd.c \
ft_strdup.c \
ft_strmapi.c \
ft_tolower.c \
ft_isalnum.c \
ft_memchr.c \
ft_putendl_fd.c \
ft_striteri.c \
ft_strcmp.c \
ft_strncmp.c \
ft_toupper.c \
ft_isalpha.c \
ft_memcmp.c \
ft_putnbr_fd.c \
ft_strjoin.c \
ft_strnstr.c \
ft_isascii.c \
ft_memcpy.c \
ft_putstr_fd.c \
ft_strlcat.c \
ft_strrchr.c \
ft_lstdelone_bonus.c \
ft_lstiter_bonus.c \
ft_lstlast_bonus.c \
ft_lstmap_bonus.c \
ft_lstsize_bonus.c \
ft_lstnew_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstadd_back_bonus.c \
ft_lstclear_bonus.c \
printf/ft_printf.c \
printf/ft_printf_print_argument.c \
printf/ft_printf_utils2.c \
printf/ft_printf_utils.c \
get_next_line_bonus.c

# Replace .c with .o for object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(NAME)

# Rule to create the static library
$(NAME): $(OBJECTS)
	$(AR) rcs $@ $^

# Generic rule for compiling .c to .o
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJECTS)

# Full clean (objects + executable)
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets (not file names)
.PHONY: all clean fclean re bonus
