/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:48:28 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/22 17:48:54 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*which_color(t_file *file)
{
	char *color;

	color = ft_strdup(RESET);
	if ((file->lstat.st_mode & S_ISUID) == S_ISUID)
		color = ft_strjoin(BLACK,BGRED);
	else if ((file->lstat.st_mode & S_ISGID) == S_ISGID)
		color = ft_strjoin(BLACK,BGCYAN);
	else if (((file->lstat.st_mode & S_IFMT) ^ S_IFREG) != 0)
		color = type_color(file);
	else if ((file->lstat.st_mode & S_IXUSR) == S_IXUSR
		|| (file->lstat.st_mode & S_IXGRP) == S_IXGRP
		|| (file->lstat.st_mode & S_IXOTH) == S_IXOTH)
		color = ft_strdup(RED);
	return (color);
}

char	*type_color(t_file *file)
{
	char *color;

	if (((file->lstat.st_mode & S_IFMT) ^ S_IFCHR) == 0)
		color = ft_strjoin(BLUE,BGYELLOW);
	if (((file->lstat.st_mode & S_IFMT) ^ S_IFBLK) == 0)
		color = ft_strjoin(BLUE,BGCYAN);
	if (((file->lstat.st_mode & S_IFMT) ^ S_IFIFO) == 0)
		color = ft_strdup(YELLOW) ;
	if (((file->lstat.st_mode & S_IFMT) ^ S_IFSOCK) == 0)
		color = ft_strdup(GREEN) ;
	if (((file->lstat.st_mode & S_IFMT) ^ S_IFLNK) == 0)
	 	color = ft_strdup(MAGENTA);
	if (((file->lstat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
	{
		if ((file->lstat.st_mode & S_IWOTH) == S_IWOTH)
		{
			((file->lstat.st_mode & S_ISVTX) == S_ISVTX) ?
			color = ft_strjoin(BLACK,BGGREEN) : 0;
			((file->lstat.st_mode & S_ISVTX) != S_ISVTX) ?
			color = ft_strjoin(BLACK,BGYELLOW) : 0;
		}
		else
			color = ft_strdup(BLUE);
	}
	 return (color);
}

void	join_color(t_file *file, t_opt *option)
{
	char	*new_name;
	char	*color;
	char	*temp;

	if (option->u_g)
	{
		color = which_color(file);
		new_name = ft_strnew(ft_strlen(file->name) + ft_strlen(color) + 7);
		new_name = ft_strcat(ft_strcat(ft_strcpy(new_name, color), file->name), RESET);
		temp = file->name;
		file->name = ft_strdup(new_name);
		// free(temp);
	}
}

/*
** 5. bx  executable = RED --> S_IXUSR || S_IXGRP || S_IXOTH
** 1. ex  directory = BLUE --> S_IFDIR
** 2. fx  symbolic link = MAGENTA --> S_IFLNK
** 3. cx  socket = GREEN --> S_IFSOCK
** 4. dx  pipe = YELLOW --> S_IFIFO
** 6. eg  block special = BLUE + BGCYAN --> S_IFBLK
** 7. ed  character special = BLUE + BGYELLOW --> S_IFCHR

** 8. ab  executable with setuid bit set = BLACK + BGRED --> S_ISUID
** 9. ag  executable with setgid bit set = BLACK + BGCYAN --> S_ISGID

** 11. ad directory writable to others, without sticky bit = BLACK + BGYELLOW --> S_IFDIR && S_IWOTH
** 10. ac directory writable to others, with sticky bit = BLACK + BGGREEN --> S_IFDIR && S_IWOTH && S_ISVTX
*/