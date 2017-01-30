/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:54:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/30 19:11:43 by sfranc           ###   ########.fr       */
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

int		display_file_error(t_file *file)
{
	if (file->error != 0 && file->error != 20)
	{
		ft_putstr(LS);
		ft_putstr(file->name);
		ft_putstr(": ");
		ft_putendl(strerror(file->error));
		return (1);
	}
	return (0);
}

void	display_names(int ac, t_file *files)
{
	t_file	*temp;
	t_file	*temp2;

	(void)ac;
	temp = files;
	while (temp)
	{
		if (!(display_file_error(temp)) && ac != 1)
			ft_putendl(temp->name);
		if (temp->inside != NULL)
		{
			temp2 = temp->inside;
			while (temp2)
			{
				ft_putendl(temp2->name);
				temp2 = temp2->next;
			}
			ft_putchar('\n');
		}
		temp = temp->next;
	}
}
