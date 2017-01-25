/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 11:50:25 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/25 19:27:44 by sfranc           ###   ########.fr       */
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
//	else
//		alst = &temp;
}

/*void		read_names(int ac, char **av, t_file **names)
{
	t_file	*temp;
	DIR		*dir_ptr;

	ft_putendl("--- read_names 1");
	while (ac)
	{
		ft_putendl(*av);
		if ((dir_ptr = opendir(*av)))
			read_inside(dir_ptr, names);
		else
			temp = ft_filenew(*av);
		if (*names != NULL)
			ft_fileadd_last(names, temp);
		else
			*names = temp;
		if (ac--)
			av++;
	}
}

void	read_inside(DIR	*dir_ptr, t_file **names)
{
	struct dirent	*dir_temp;
	t_file			*temp;

	ft_putendl("--- read_inside 1");
	while ((dir_temp = readdir(dir_ptr)) != NULL)
	{
	ft_putendl("--- read_inside 2");
		temp = ft_filenew(dir_temp->d_name);
	ft_putendl("--- read_inside 3");
		if (*names == NULL)
		{
			ft_putendl("--- read_inside 4");
			*names = temp;
		}
		else
		{
			ft_putendl("--- read_inside 5");
			if ((*names)->inside != NULL)
			{
				ft_putendl("--- read_inside 6");
				ft_fileadd_last(&(*names)->inside, temp);
			}
			else
			{
				ft_putendl("--- read_inside 7");
				(*names)->inside = temp;
			}
		}
	ft_putendl("--- read_inside 8");
	}
	closedir(dir_ptr);
}*/

int		parsing(int ac, char **av, t_file **names, char *options)
{
	int		ac_tmp;
	char	**av_tmp;

	(void)options;
	(void)names;
	if (ac == 1)
	{
		ft_putendl("--- open . et lis");
		return (1);
	}
	ac_tmp = ac;
	av_tmp = av;
	while (--ac_tmp)
	{
		++av_tmp;
		if (ft_strequ(*av_tmp, ""))
		{
			ft_putendl("ft_ls: fts_open: No such file or directory");
			return (0);
		}
	}
	while (--ac)
	{
		++av;
		if (**av != '-')
		{
			ft_putendl("--- read names");
			return (1);
		}
		else
		{
			if (ft_strequ(*av, "--"))
			{
				ft_putendl("-- skip -- et read_names");
				return (1);
			}
			ft_putendl("--- read_option");
		}
	}
	return (0);
}

//int		read_options(int ac, char **av, char *options)
