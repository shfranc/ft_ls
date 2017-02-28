/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:54:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/28 17:31:46 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_options(t_opt *options)
{
	ft_putstr("OPTIONS : ");
	write(1, (char*)options, 8);
	write(1, "\n", 1);
/*	ft_putchar(options->u_r);
	ft_putchar(options->u_s);
	ft_putchar(options->a);
	ft_putchar(options->f);
	ft_putchar(options->l);
	ft_putchar(options->r);
	ft_putchar(options->t);
	ft_putchar(options->u);
//	if (options->u_r || options->a || options->l || options->r || options->t)
		ft_putchar('\n');*/
}

void	display_illegal_option(char c)
{
	ft_putstr_fd(ILLEGAL, 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(USAGE, 2);
}

void	display_file_error(t_file *file)
{
	ft_putstr_fd(LS, 2);
	if ((ft_strrchr(file->name, '/')))
		ft_putstr_fd(ft_strrchr(file->name, '/') + 1, 2);
	else
		ft_putstr_fd(file->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(file->error), 2);
}

void	display_errors(t_file *names) /* hors Permission Denied */
{
	t_file	*temp;

	temp = names;
	while (temp)
	{
		if (temp->error != 13 && temp->error != 0 && temp->error != 20)
			display_file_error(temp);
		temp = temp->next;
	}
}
