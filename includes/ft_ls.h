/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:38:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/26 13:03:57 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"
#include <errno.h> /*errno */
#include <sys/stat.h> /* stat + struct stat */
#include <stdio.h> /* strerror */
#include <dirent.h> /* opendir + DIR, readdir + struct dirent */

typedef struct	s_file
{
	char			*name;
	int				error;
	struct stat		lstat;
//	struct stat		stat;
	struct s_file	*inside;
	struct s_file	*next;
} 				t_file;

/*
** parsing.c
*/
t_file	*ft_filenew(char *av);
void	ft_fileadd_last(t_file **alst, t_file *new);
int		parsing(int ac, char **av, t_file **names, char *options);
void	read_names(int ac, char **av, t_file **names);
void	read_inside(DIR *dir_ptr, t_file **names);

/*
** display.c
*/
void	display_names(t_file *names);
void	display_errors(t_file *names);

#endif
