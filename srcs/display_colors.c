/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:48:28 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/06 19:02:34 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*which_color(t_file *file)
{
	char *color;

	color = NULL;
	if ((file->lstat.st_mode & S_ISUID) == S_ISUID)
		color = ft_strjoin(BLACK, BGRED);
	else if ((file->lstat.st_mode & S_ISGID) == S_ISGID)
		color = ft_strjoin(BLACK, BGCYAN);
	else if (!(S_ISREG(file->lstat.st_mode)))
		color = type_color(file);
	else if ((file->lstat.st_mode & S_IXUSR) == S_IXUSR
		|| (file->lstat.st_mode & S_IXGRP) == S_IXGRP
		|| (file->lstat.st_mode & S_IXOTH) == S_IXOTH)
		color = ft_strdup(RED);
	else
		color = ft_strdup(RESET);
	return (color);
}

char	*type_color(t_file *file)
{
	char *color;

	if (S_ISCHR(file->lstat.st_mode))
		color = ft_strjoin(BLUE, BGYELLOW);
	if (S_ISBLK(file->lstat.st_mode))
		color = ft_strjoin(BLUE, BGCYAN);
	if (S_ISFIFO(file->lstat.st_mode))
		color = ft_strdup(YELLOW);
	if (S_ISSOCK(file->lstat.st_mode))
		color = ft_strdup(GREEN);
	if (S_ISLNK(file->lstat.st_mode))
		color = ft_strdup(MAGENTA);
	if (S_ISDIR(file->lstat.st_mode))
	{
		if ((file->lstat.st_mode & S_IWOTH) == S_IWOTH)
		{
			((file->lstat.st_mode & S_ISVTX) == S_ISVTX) ?
			color = ft_strjoin(BLACK, BGGREEN) : 0;
			((file->lstat.st_mode & S_ISVTX) != S_ISVTX) ?
			color = ft_strjoin(BLACK, BGYELLOW) : 0;
		}
		else
			color = ft_strdup(BLUE);
	}
	return (color);
}

void	join_color(t_file *file, char *s)
{
	char	*color;

	if ((lstat(file->path, &file->lstat)) == -1)
		file->color_name = ft_strdup(s);
	else
	{
		color = which_color(file);
		file->color_name = ft_strjoin3(color, s, RESET);
		free(color);
	}
}

void	ft_putendl2(char *s1, char *s2)
{
	ft_putstr(s1);
	ft_putendl(s2);
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
** 11. ad directory writable to others, without sticky bit = BLACK + BGYELLOW
** 			--> S_IFDIR && S_IWOTH
** 10. ac directory writable to others, with sticky bit = BLACK + BGGREEN
** 			--> S_IFDIR && S_IWOTH && S_ISVTX
*/
