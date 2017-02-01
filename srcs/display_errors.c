/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:54:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/01 12:58:42 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_options(t_opt *options)
{
	ft_putstr("options : ");
	ft_putchar(options->u_r);
	ft_putchar(options->a);
	ft_putchar(options->f);
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

void	display_errors(t_file *names) /* hors Permission Denied */
{
	t_file	*temp;

	temp = names;
	while (temp)
	{
		if (temp->error != 13)
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
