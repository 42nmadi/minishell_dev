# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:38:26 by imran             #+#    #+#              #
#    Updated: 2022/04/20 21:49:07 by nmadi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

SRCS=	main.c \
 		execute.c \
		pipe.c \
		find.c \
		free.c \
		error.c \
		ft_split_path.c

CC = gcc

CFLAGS= -Wall -Wextra -Werror

LIBFT = ./libs/libft/libft.a

OBJS_DIR = ./objs

SRCS_DIR = ./srcs

LDFLAGS = -lreadline

LIBS = -L /lib/x86_64-linux-gnu/libreadline.so.8 -lreadline -pthread

INCS = -I /usr/include/

.SILENT:

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:c=o))

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ./libs/libft/
	@echo "\033[0;32mCompiled libft.\033[0m"
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)
	@echo "\033[0;32mCompiled minishell.\033[0m"

all: $(NAME)

linux: $(OBJS)
	$(MAKE) -C ./libs/libft/
	@echo "\033[0;32mCompiled libft.\033[0m"
	$(CC) $(CFLAGS) $(LIBS) $(INCS) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)
	@echo "\033[0;32mCompiled minishell.\033[0m"

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_DIR)
	@echo "\033[0;32mCleaned minishell object files.\033[0m"
	$(MAKE) clean -C ./libs/libft/
	@echo "\033[0;32mCleaned libft object files.\033[0m"

fclean: clean
	rm -rf minishell
	@echo "\033[0;32mCleaned executable.\033[0m"
	$(MAKE) fclean -C ./libs/libft/
	@echo "\033[0;32mCleaned libft archive file.\033[0m"

re: fclean all

.PHONY: all clean fclean re