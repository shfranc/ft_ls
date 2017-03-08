/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_names.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:24:18 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/08 17:58:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*file_new(char *path, t_opt *option)
{
	t_file		*elem;
	int			ret_lstat;
	int			ret_sstat;

	if (!(elem = (t_file*)malloc(sizeof(t_file))))
		ft_exit("Unable to malloc t_file");
	elem->error = 0;
	if ((ret_lstat = lstat(path, &elem->lstat)) == -1
		|| (ret_sstat = stat(path, &elem->stat)) == -1)
		elem->error = errno;

	if (!(elem->path = ft_strdup(path)))
		ft_exit("Unable to malloc path");

//	if (!(elem->path = (char*)malloc(sizeof(char) * (ft_strlen(path) + 1))))
//			elem->path = ft_memcpy(elem->path, path, ft_strlen(path) + 1);

	if (!(elem->name = ft_strrchr(elem->path, '/') + 1))
		elem->name = elem->path;
//	
//	printf("%d\t%d\t%s\n", ret_lstat, elem->error, elem->name);
	elem->next = NULL;
	elem->inside = NULL;
	if (option->l)
		get_usr_group_struct(elem);
	return (elem);
}

/*void	file_add(t_file **begin, t_file *new) // on ne surprotege pas file_add, donc bien verifier que begin existe
{
	if (*begin == NULL)
		*begin = new;
	else
	{
		new->next = *begin;
		*begin = new;
	}
}*/

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
		path = ft_strnew(ft_strlen(av_dir) + ft_strlen(dir_temp->d_name) + 1);
		path = ft_strcat(ft_strcat(ft_strcpy(path, av_dir), "/"), dir_temp->d_name);
		elem = file_new(path, option);
		file_add_last(&begin, elem);
		ft_strdel(&path);
	}
	(*files)->inside = begin;
	closedir(dir_ptr);
//	if ((closedir(dir_ptr)) == -1)
//		(*names)->error = errno;
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

//		if (((elem->lstat.st_mode & S_IFMT) ^ S_IFLNK) == 0)
//		{
//			link_name = (char*)malloc(elem->lstat.st_size + 1);
//			r = readlink(elem->name, link_name, elem->lstat.st_size + 1);
//			link_name[elem->lstat.st_size] = '\0';
//			ft_putstr("link name : ");
//			ft_putendl(link_name);
//		}
