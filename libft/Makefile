RED = \033[48;5;9m
GREEN = \033[48;5;10m
LOL = \033[48;5;106m
LIL = \033[48;5;129m
END = \033[0m
X = 0
Y = 0

NAME = libft.a

SRC = ./srcs/ft_atoi.c \
		./srcs/ft_bzero.c \
		./srcs/ft_charswap.c \
		./srcs/ft_del.c \
		./srcs/ft_intsize.c \
		./srcs/ft_isalnum.c \
		./srcs/ft_isalpha.c \
		./srcs/ft_isascii.c \
		./srcs/ft_isdigit.c \
		./srcs/ft_isprint.c \
		./srcs/ft_itoa.c \
		./srcs/ft_itoa_base.c \
		./srcs/ft_lstadd.c \
		./srcs/ft_lstadd_last.c \
		./srcs/ft_lstdel.c \
		./srcs/ft_lstdelone.c \
		./srcs/ft_lstiter.c \
		./srcs/ft_lstlen.c \
		./srcs/ft_lstmap.c \
		./srcs/ft_lstnew.c \
		./srcs/ft_lstprint.c \
		./srcs/ft_memalloc.c \
		./srcs/ft_memccpy.c \
		./srcs/ft_memchr.c \
		./srcs/ft_memcmp.c \
		./srcs/ft_memcpy.c \
		./srcs/ft_memdel.c \
		./srcs/ft_memmove.c \
		./srcs/ft_memset.c \
		./srcs/ft_nb_words.c \
		./srcs/ft_putchar.c \
		./srcs/ft_putchar_fd.c \
		./srcs/ft_putendl.c \
		./srcs/ft_putendl_fd.c \
		./srcs/ft_putnbr.c \
		./srcs/ft_putnbr_endl.c \
		./srcs/ft_putnbr_fd.c \
		./srcs/ft_putstr.c \
		./srcs/ft_putstr_fd.c \
		./srcs/ft_range.c \
		./srcs/ft_strcat.c \
		./srcs/ft_strchr.c \
		./srcs/ft_strclr.c \
		./srcs/ft_strcmp.c \
		./srcs/ft_strcpy.c \
		./srcs/ft_strdel.c \
		./srcs/ft_strdup.c \
		./srcs/ft_strequ.c \
		./srcs/ft_striter.c \
		./srcs/ft_striteri.c \
		./srcs/ft_strjoin.c \
		./srcs/ft_strjoin3.c \
		./srcs/ft_strlcat.c \
		./srcs/ft_strlen.c \
		./srcs/ft_strmap.c \
		./srcs/ft_strmapi.c \
		./srcs/ft_strncat.c \
		./srcs/ft_strncmp.c \
		./srcs/ft_strncpy.c \
		./srcs/ft_strnequ.c \
		./srcs/ft_strnew.c \
		./srcs/ft_strnew_set.c \
		./srcs/ft_strnstr.c \
		./srcs/ft_strrchr.c \
		./srcs/ft_strsplit.c \
		./srcs/ft_strstr.c \
		./srcs/ft_strsub.c \
		./srcs/ft_strtrim.c \
		./srcs/ft_tolower.c \
		./srcs/ft_toupper.c \
		./srcs/printbit.c \
		./srcs/sort_int_tab.c \
		./srcs/ull_len.c \
		./srcs/ull_toa.c

OBJS = $(SRC:.c=.o)

CC = clang

#FLAG = -Weverything -O3
FLAG = -Wall -Wextra -Werror

HEAD = ./includes/

all: $(NAME)

$(NAME): $(OBJS) ./includes/libft.h
	@$(CC) $(FLAG) -c $(SRC) -I $(HEAD)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

%.o : %.c $(HEAD)
	@printf " ✅                                                              \r"
	@printf "✅  $(notdir $<)\r"
	$(CC) -c $(FLAG) $< -o $@

mc: fclean all clean

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all