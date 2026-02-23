# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 21:17:14 by htharrau          #+#    #+#              #
#    Updated: 2024/10/16 12:52:10 by htharrau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#SETUP
NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
LINK		= 	-lreadline -lhistory
RM			=	rm

#FILES AND PATH
HEADER_SRCS	=	minishell.h
HEADER_DIR	=	inc/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

SRCS	=		main/main.c				main/main_clean.c	main/signals.c	\
				main/main_init.c 		main/main_clean2.c					\
				parse/parse.c			parse/parse_ft_is.c 				\
				parse/tokenize.c 		parse/tokenize_helper.c 			\
				parse/expand.c												\
				parse/expand_string.c 	parse/expand_str_helper.c			\
				parse/delete_empty.c										\
				parse/retoken.c			parse/retoken_helper.c				\
				parse/combine.c			parse/grammar.c						\
				parse/command.c			parse/command_helper.c				\
				parse/heredoc.c												\
				execute/builtins.c  	execute/execute.c  					\
				execute/execute_child.c execute/execute_utils.c				\
				execute/get_cmd_path.c 	execute/set_redirections.c			\
				builtins/cd.c			builtins/echo.c		builtins/env.c	\
				builtins/exit.c 		builtins/export.c	builtins/pwd.c	\
				builtins/unset.c		builtins/builtins_utils.c 			\

		
PATH_DIR	=	src/
PATH_SRCS	=	$(addprefix $(PATH_DIR), $(SRCS))
OBJ			=	$(PATH_SRCS:.c=.o)

LIBFT		= 	$(LIBFT_DIR)/libft.a
LIBFT_DIR	= 	libft

#COMMANDS

all:			$(LIBFT) $(NAME)

$(NAME):		$(OBJ) $(LIBFT)
				@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LINK) -L$(LIBFT_DIR) -lft
				@echo "$(MAGENTA)$(NAME) created.$(DEFAULT)"
				
$(LIBFT):
				$(MAKE) -C $(LIBFT_DIR)

%.o: %.c		$(HEADER) Makefile
				@${CC} ${FLAGS} -c $< -o $@ -I$(LIBFT_DIR)

clean:			
				$(MAKE) -C $(LIBFT_DIR) clean
				@$(RM) -rf $(OBJ) heredoc.tmp
				@echo "$(CYAN)Object files deleted.$(DEFAULT)"

fclean:			clean
				$(MAKE) -C $(LIBFT_DIR) fclean
				@$(RM) -rf $(NAME)
				@echo "$(GREEN)All deleted.$(DEFAULT)"

re:				fclean all

debug: FLAGS += -g
debug: re

.PHONY:			all clean fclean re debug

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
DEFAULT = \033[0m