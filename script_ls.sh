#make re -C ../libft_gitperso
#gcc -Wall -Werror -Wextra -o ft_list_dir ../libft_gitperso/libft.a -I ../libft_gitperso/includes essais/ft_list_dir.c
#echo "compil ft_list_dir : \033[01;32mOK\033[00m"
gcc -Wall -Werror -Wextra -o ft_inspect_file ../libft_gitperso/libft.a -I ../libft_gitperso/includes essais/ft_inspect_file.c
echo "compil ft_inspect_file : \033[01;32mOK\033[00m"
