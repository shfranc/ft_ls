make -C libft
#gcc -Wall -Werror -Wextra -o ft_list_dir ../libft_gitperso/libft.a -I ../libft_gitperso/includes essais/ft_list_dir.c
#echo "compil ft_list_dir : \033[01;32mOK\033[00m"
#gcc -Wall -Werror -Wextra -o ft_inspect_file ../libft_gitperso/libft.a -I ../libft_gitperso/includes essais/ft_inspect_file.c
#echo "compil ft_inspect_file : \033[01;32mOK\033[00m"
#gcc -Wall -Werror -Wextra -o ft_ls ../libft_gitperso/libft.a -I ../libft_gitperso/includes -I includes srcs/main.c srcs/parsing_options.c srcs/display.c
#echo "compil ft_ls : \033[01;32mOK\033[00m"
gcc -g -Wall -Werror -Wextra -o ft_ls \
	libft/libft.a \
	-I libft/includes \
	-I includes \
	srcs/main.c \
	srcs/parsing_options.c \
	srcs/display_errors.c \
	srcs/parsing_names.c \
	srcs/classic_display.c \
	srcs/option_upper_r.c \
	srcs/sorting.c \
	srcs/merge_sorting.c \
	srcs/reverse_sorting.c \
	srcs/long_format.c \
	srcs/long_format_details_part1.c \
	srcs/long_format_details_part2.c \
	srcs/long_display.c
echo "compil ft_ls : \033[01;32mOK\033[00m"
