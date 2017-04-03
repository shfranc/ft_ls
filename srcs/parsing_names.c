/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_names.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:24:18 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/03 22:51:51 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*file_new(char *path, t_opt *option)
{
	t_file		*elem;
	int			ret_lstat;
	int			ret_sstat;
	char		*temp;

	errno = 0;
	if (!(elem = (t_file*)malloc(sizeof(t_file))))
		ft_exit("Unable to malloc t_file");
	file_init(elem);
	if ((ret_lstat = lstat(path, &elem->lstat)) == -1)
	{
		elem->error = errno;
		ft_putnbr_endl(elem->error);
		ft_putendl(strerror(elem->error));
	}
	if ((ret_sstat = stat(path, &elem->stat)) == -1)
	{
		elem->error = errno;
		ft_putnbr_endl(elem->error);
		ft_putendl(strerror(elem->error));
	}
	if (!(elem->path = ft_strdup(path)))
		ft_exit("Unable to malloc path");
	if (!(temp = ft_strrchr(elem->path, '/')))
		elem->name = elem->path;
	else
		elem->name = temp + 1;
	if (option->l && (elem->error == 0 || elem->error == 20))
		get_usr_group_struct(elem);
	return (elem);
}

void	file_add_last(t_file **begin, t_file *new)
{
	t_file	*temp;

	if (*begin == NULL)
		*begin = new;
	else
	{
		temp = *begin;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	walk_dir(char *av_dir, t_file **files, t_opt *option)
{
	DIR				*dir_ptr;
	struct dirent	*dir_temp;
	t_file			*begin;
	t_file			*elem;
	char			*path;

	begin = NULL;
	if ((dir_ptr = opendir(av_dir)) == NULL)
	{
		if (errno != 0)
			(*files)->error = errno;
		return ;
	}
	while ((dir_temp = readdir(dir_ptr)) != NULL)
	{
		if (!option->a && *dir_temp->d_name == '.')
			continue ;
		path = ft_strjoin3(av_dir, "/", dir_temp->d_name);
		elem = file_new(path, option);
		file_add_last(&begin, elem);
		ft_strdel(&path);
	}
	(*files)->inside = begin;
	closedir(dir_ptr);
}

void	read_names(int ac, char **av, t_file **files, t_opt *option)
{
	t_file	*elem;

	while (ac)
	{
		elem = file_new(*av, option);
		if (((elem->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
			walk_dir(elem->path, &elem, option);
		file_add_last(files, elem);
		if (--ac)
			++av;
	}
}
