/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_names.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:24:18 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/30 19:11:38 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*file_new(char *name, char *path)
{
	t_file		*elem;
	struct stat	l_stat;
	int			ret_lstat;
	char		*temp;

	if (!(elem = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	if (path != NULL)
	{
		temp = name;
		name = ft_strnew(ft_strlen(path) + ft_strlen(temp) + 1);
		name = ft_strcat(ft_strcat(path, "/"), temp);
	}
	ft_putendl(name);
	if ((ret_lstat = lstat(name, &l_stat)) == -1)
		return (NULL);
	elem->name = ft_strdup(name);
	elem->error = errno;
	elem->lstat = l_stat;
	elem->next = NULL;
	elem->inside = NULL;
	return (elem);
}

void	file_add(t_file **begin, t_file *new) /*on ne surprotege pas file_add, donc bien verifier que begin existe */
{
		if (*begin == NULL)
			*begin = new;
		else
		{
			new->next = *begin;
			*begin = new;
		}
}

void	walk_dir(char *av_dir, t_file **names)
{
	DIR				*dir_ptr;
	struct dirent	*dir_temp;
	t_file			*begin;
//	t_file			*elem;

	begin = NULL;
	if (!(dir_ptr = opendir(av_dir)))
	{
		if (errno != 0)
			(*names)->error = errno;
		return ;
	}
	while ((dir_temp = readdir(dir_ptr)) != NULL)
	{
//		elem = file_new(dir_temp->d_name, av_dir);
//		file_add(&begin, elem);
	}
	(*names)->inside = begin;
}

void	read_names(int ac, char **av, t_file **names)
{
	t_file	*elem;

	while (ac)
	{
		elem = file_new(*av, NULL);
		file_add(names, elem);
		if ((((*names)->lstat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
			walk_dir((*names)->name, names);
		if (--ac)
			++av;
	}
}

