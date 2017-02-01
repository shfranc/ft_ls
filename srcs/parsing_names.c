/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_names.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:24:18 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/01 11:23:34 by sfranc           ###   ########.fr       */
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

void	walk_dir(char *av_dir, t_file **names)
{
	DIR				*dir_ptr;
	struct dirent	*dir_temp;
	t_file			*begin;
	t_file			*elem;
	char			*temp;

	begin = NULL;
	if (!(dir_ptr = opendir(av_dir)))
	{
		if (errno != 0)
			(*names)->error = errno;
		return ;
	}
	while ((dir_temp = readdir(dir_ptr)) != NULL)
	{
		temp = ft_strnew(ft_strlen(av_dir) + ft_strlen(dir_temp->d_name) + 1);
		temp = ft_strcat(ft_strcat(ft_strcpy(temp, av_dir), "/"), dir_temp->d_name);
		elem = file_new(temp);
		file_add_last(&begin, elem);
		ft_strdel(&temp);
	}
	(*names)->inside = begin;
}

void	read_names(int ac, char **av, t_file **names) /* la distinction dir non dir se fera plutot a l'affichage. */
{
	t_file	*elem;

	while (ac)
	{
		elem = file_new(*av);
		if (((elem->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
		{
			walk_dir(elem->name, &elem);
		}
		file_add_last(names, elem);
		if (--ac)
			++av;
	}
}
