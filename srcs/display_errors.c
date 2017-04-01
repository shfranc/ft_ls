/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:20:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/01 18:01:31 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_exit(char *s)
{
	ft_putendl_fd(s, 2);
	exit(0);
}

void	display_options(t_opt *option)
{
	ft_putstr("option : ");
	write(1, (char*)option, 11);
	write(1, "\n", 1);
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
	ft_putstr_fd(file->path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(file->error), 2);
}

int		display_errors(t_file *files)
{
	t_file	*temp;
	int		nb_error;

	nb_error = 0;
	temp = files;
	while (temp)
	{
		if (temp->error != 13 && temp->error != 0 && temp->error != 20)
		{
			display_file_error(temp);
			nb_error++;
		}
		temp = temp->next;
	}
	return (nb_error);
}
