/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:20:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/11 14:04:21 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_exit(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
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
	ft_putstr_fd(file->name, 2);
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
			ft_putstr_fd(LS, 2);
			ft_putstr_fd(temp->path, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(temp->error), 2);
			nb_error++;
		}
		temp = temp->next;
	}
	return (nb_error);
}

int		read_only(t_file *files)
{
	t_file	*temp;
	int		i;

	i = 0;
	
	temp = files;
	while (temp)
	{
		if (lstat(temp->path, &temp->lstat) == -1)
			i++;	
		temp = temp->next;
	}
	return (i);
}
