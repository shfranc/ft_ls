/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:54:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/31 18:07:14 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_options(t_opt *options)
{
	ft_putstr("options : ");
	ft_putchar(options->u_r);
	ft_putchar(options->a);
	ft_putchar(options->l);
	ft_putchar(options->r);
	ft_putchar(options->t);
	if (options->u_r || options->a || options->l || options->r || options->t)
		ft_putchar('\n');
}

void	display_illegal_option(char c)
{
	ft_putstr(ILLEGAL);
	ft_putchar(c);
	ft_putendl(USAGE);
}

void	display_file_error(t_file *file)
{
	if (file->error != 0 && file->error != 20)
	{
		ft_putstr(LS);
		ft_putstr(file->name);
		ft_putstr(": ");
		ft_putendl(strerror(file->error));
	}
}

void	display_errors(t_file *names)
{
	t_file	*temp;

	temp = names;
	while (temp)
	{
		display_file_error(temp);
		temp = temp->next;
	}
}

void	display_names(int ac, t_file *files) /* on laisse de cote pour l'instant */
{
	t_file	*temp;
	t_file	*temp2;
	int		i;

	temp = files;
	i = 1;
	while (temp)
	{
		if (temp->error == 0 || temp->error == 20)
		{
			ft_putstr(temp->name);
			ft_putendl(":");
		}
		if (temp->inside != NULL)
		{
			temp2 = temp->inside;
			while (temp2)
			{
				ft_putendl(ft_strrchr(temp2->name, '/') + 1);
				temp2 = temp2->next;
			}
		}
		if (i != ac)
			ft_putchar('\n');
		temp = temp->next;
		++i;
	}
}

void	display_dirnondir(int ac, t_file *files)
{
	t_file	*temp;
	t_file	*temp2;
	int		file;

	temp = files;
	file = 0;
	while (temp)
	{
		if (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) != 0)
		{
			ft_putendl(temp->name);
			file++;
		}
		temp = temp->next;
	}
	if (file != 0)
		write(1, "\n", 1);
	temp = files;
	while (temp)
	{
		if (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
		{
			if (ac != 1)
			{
				ft_putstr(temp->name);
				ft_putendl(":");
			}
			file++;
			if (temp->inside != NULL)
			{
				temp2 = temp->inside;
				while (temp2)
				{
					ft_putendl(ft_strrchr(temp2->name, '/') + 1);
					temp2 = temp2->next;
				}
				if (file != ac)
					write(1, "\n",1);
			}
		}
		temp = temp->next;	
	}
}
