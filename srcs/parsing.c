/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:42:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/24 18:57:49 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*ft_filenew(char *av)
{
	t_file		*elem;
	struct stat	l_stat;
	int			ret_lstat;

	if (!(elem = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	ret_lstat = lstat(av, &l_stat);
	//	ft_putnbr_endl(ret_lstat);
	elem->name = ft_strdup(av);
	elem->error = errno;
	elem->lstat = l_stat;
	elem->next = NULL;
	elem->inside = NULL;
	return (elem);
}

void	ft_fileadd_last(t_file **alst, t_file *new)
{
	t_file	*temp;

	temp = *alst;
	if (alst)
	{
		if (temp == NULL)
			temp = new;
		else
		{
			while (temp->next)
				temp = temp->next;
			temp->next = new;
		}
	}
}

void		read_names(int ac, char **av, t_file **names)
{
	t_file	*temp;

	//	ft_putendl("--- read_names");
	//	ft_putnbr_endl(ac);
	while (ac)
	{
		//		ft_putendl(*av);
		temp = ft_filenew(*av);
		if (*names != NULL)
			ft_fileadd_last(names, temp);
		else
			*names = temp;
		//		ft_putendl((*names)->name);
		if (ac--)
			av++;
	}
}

void	read_inside(char *av, t_file **names)
{
	DIR				*dir_ptr;
	struct dirent	*dir_temp;
	t_file			*temp;

	ft_putendl("--- read_inside 1");
	dir_ptr = opendir(av);
	while ((dir_temp = readdir(dir_ptr)) != NULL)
	{
		if (*dir_temp->d_name != '.')
		{
			temp = ft_filenew(dir_temp->d_name);
			if (*names == NULL)
				*names = temp;
			else
			{
				if ((*names)->inside != NULL)
				{
					ft_fileadd_last(&(*names)->inside, temp);
				}
				else
				{
					(*names)->inside = temp;
				}
			}
		}
	}
}

int		parsing(int ac, char **av, t_file **names, char *options)
{
	(void)options;
	if (ac == 1)
	{
		ft_putendl("--- open . et lis");
		read_inside(".", names);
		return (1);
	}
	while (--ac)
	{
		++av;
		if (**av != '-')
		{
			ft_putendl("--- read names");
			read_names(ac, av, names);
			return (1);
		}
		else
		{
			if (ft_strequ(*av, "--"))
			{
				ft_putendl("-- skip -- et read_names");
				read_names(--ac, ++av, names);
				return (1);
			}
			ft_putendl("--- read_option");
		}
	}
	return (0);
}
