/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:20:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/06 19:02:35 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_exit(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

// void	display_options(t_opt *option)
// {
// 	ft_putstr("option : ");
// 	write(1, (char*)option, 11);
// 	write(1, "\n", 1);
// }

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

int		read_only(t_file *files, t_opt *option)
{
	t_file	*temp;
	int		i;
	char	*dir;

	i = 0;
	temp = files;
	while (temp)
	{
		if (lstat(temp->path, &temp->lstat) == -1
			&& (option->l || option->u_g || option->u_s || option->t || option->u_r))
		{
			display_file_error(temp);
			i++;
		}
		temp = temp->next;
	}
	if (i && option->u_r)
	{
		dir = ft_strsub(files->path, 0, ft_strrchr(files->path, '/') - files->path);
		ft_putstr_fd(LS, 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(13), 2);
		free(dir);
	}
	return (i);
}
