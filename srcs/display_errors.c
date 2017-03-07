/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:20:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/07 18:10:19 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_exit(char *s)
{
	ft_putendl_fd(s, 2);
	exit(0);
}

void	display_option(t_opt *option)
{
	ft_putstr("option : ");
	write(1, (char*)option, 8);
	write(1, "\n", 1);
/*	ft_putchar(option->u_r);
	ft_putchar(option->u_s);
	ft_putchar(option->a);
	ft_putchar(option->f);
	ft_putchar(option->l);
	ft_putchar(option->r);
	ft_putchar(option->t);
	ft_putchar(option->u);
//	if (option->u_r || option->a || option->l || option->r || option->t)
		ft_putchar('\n');*/
}

void	display_illegal_option(char c)
{
	ft_putstr_fd(ILLEGAL, 2);
	ft_putchar_fd(c, 2);
	ft_exit(USAGE);
}

void	display_file_error(t_file *file)
{
	ft_putstr_fd(LS, 2);
//	if ((ft_strrchr(ifile->name, '/')))
		ft_putstr_fd(file->name, 2);
//	else
//		ft_putstr_fd(file->name, 2);
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
