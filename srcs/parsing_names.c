/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_names.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:24:18 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/15 19:19:14 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*file_new(char *name)
{
	t_file		*elem;
	int			ret_lstat;
	int			ret_sstat;

	errno = 0;
	if (!(elem = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	ret_lstat = lstat(name, &elem->lstat);
	elem->error = errno;
	elem->name = ft_strdup(name);
//	printf("%d\t%d\t%s\n", ret_lstat, elem->error, elem->name);
	ret_sstat = stat(name, &elem->stat);
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

void	walk_dir(char *av_dir, t_file **names, t_opt *options)
{
	DIR				*dir_ptr;
	struct dirent	*dir_temp;
	t_file			*begin;
	t_file			*elem;
	char			*temp;

	begin = NULL;
	if ((dir_ptr = opendir(av_dir)) == NULL)
	{
		if (errno != 0)
			(*names)->error = errno;
		return ;
	}
	while ((dir_temp = readdir(dir_ptr)) != NULL)
	{
		if (!options->a && *dir_temp->d_name == '.')
			continue ;
		temp = ft_strnew(ft_strlen(av_dir) + ft_strlen(dir_temp->d_name) + 1);
		temp = ft_strcat(ft_strcat(ft_strcpy(temp, av_dir), "/"), dir_temp->d_name);
		elem = file_new(temp);
		file_add_last(&begin, elem);
		ft_strdel(&temp);
	}
	(*names)->inside = begin;
	closedir(dir_ptr);
//	if ((closedir(dir_ptr)) == -1)
//		(*names)->error = errno;
}

void	read_names(int ac, char **av, t_file **names, t_opt *options)
{
	t_file	*elem;

	while (ac)
	{
		elem = file_new(*av);
		if (((elem->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
			walk_dir(elem->name, &elem, options);
		file_add_last(names, elem);
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
