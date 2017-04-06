####################################_COLOR_#####################################
GREEN = \033[38;5;10m
GREY = \033[38;5;60m
RED = \033[38;5;9m
END = \033[0m
##################################_COMPILATION_#################################
NAME = ft_ls
CC = gcc
FLAG = -Wall -Wextra -Werror
LFT = ./libft/libft.a
SRCS =	./srcs/main.c \
	./srcs/parsing_options.c \
	./srcs/parsing_names.c \
	./srcs/parsing_misc.c \
	./srcs/recursive_search.c \
	./srcs/merge_sorting.c \
	./srcs/sorting.c \
	./srcs/reverse_sorting.c \
	./srcs/long_format.c \
	./srcs/long_format_details_part1.c \
	./srcs/long_format_details_part2.c \
	./srcs/classic_display.c \
	./srcs/display_colors.c \
	./srcs/column.c \
	./srcs/column_part2.c \
	./srcs/long_display.c \
	./srcs/display_errors.c \
	./srcs/free.c

OBJS = $(SRCS:.c=.o)

INCLUDE = -I ./includes \
		  -I ./libft/includes
###########################_RELINK_MODIFY_.h####################################
RELINK = ./includes/ft_ls.h
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C ./libft/
	@$(CC) $(FLAG) -o $(NAME) $(OBJS) $(LFT)
	@printf "✅  Compilation done.\n"

%.o : %.c $(RELINK) ./Makefile
	@printf " ✅                                                              \r"
	@printf "✅  $(notdir $<)\r"
	@$(CC) -c $(FLAG) $< -o $@ $(INCLUDE)

clean:
	@printf "                                                               \r"
	@printf "✅  all .o deleted\n"
	@rm -f $(OBJS)
	@make -s clean -C ./libft/

fclean:
	@printf "                                                               \r"
	@printf "✅  libft.a, all .o and rabougue.filler deleted\n"
	@rm -f $(NAME) $(OBJS)
	@make -s fclean -C ./libft/

re: fclean all
