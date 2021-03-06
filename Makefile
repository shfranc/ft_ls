# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/13 13:03:38 by sfranc            #+#    #+#              #
#    Updated: 2017/04/10 13:49:08 by sfranc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRCS_PATH = srcs
OBJS_PATH = objs
SRCS = 	$(addprefix $(SRCS_PATH)/, main.c \
	parsing_options.c \
	parsing_names.c \
	parsing_misc.c \
	recursive_search.c \
	merge_sorting.c \
	sorting.c \
	reverse_sorting.c \
	long_format.c \
	long_format_details_part1.c \
	long_format_details_part2.c \
	classic_display.c \
	display_colors.c \
	column.c \
	column_part2.c \
	long_display.c \
	display_errors.c \
	free.c)
OBJS =  $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)
INCLUDES = includes libft/includes
LIB = $(LIB_PATH)/libft.a
LIB_PATH = ./libft
CC = gcc
FLAGS = -Wall -Wextra -Werror
GREEN = \033[01;32m
YELLOW = \033[01;33m
CYAN = \033[01;36m
RESET = \033[00m

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

$(LIB):
	make -C $(LIB_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES)
	$(CC) $(FLAGS) -o $@ -c $< $(addprefix -I , $(INCLUDES))

clean:
	make clean -C $(LIB_PATH)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIB_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re