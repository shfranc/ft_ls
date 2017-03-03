/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_details_part1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:01:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/03 15:10:43 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_type(char *long_format, t_file *file)
{
	((file->lstat.st_mode & S_IFMT) ^ S_IFBLK) == 0 ? *long_format = 'b' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFCHR) == 0 ? *long_format = 'c' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFDIR) == 0 ? *long_format = 'd' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFLNK) == 0 ? *long_format = 'l' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFSOCK) == 0 ? *long_format = 's' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFIFO) == 0 ? *long_format = 'p' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFREG) == 0 ? *long_format = '-' : 0;
}

void	get_perms(char *long_format, t_file *file)
{
	ft_memset(long_format + 1, '-', 9);
	(file->lstat.st_mode & S_IRUSR) == S_IRUSR ? *(long_format + 1) = 'r' : 0;
	(file->lstat.st_mode & S_IWUSR) == S_IWUSR ? *(long_format + 2) = 'w' : 0;
	(file->lstat.st_mode & S_IXUSR) == S_IXUSR ? *(long_format + 3) = 'x' : 0;
	(file->lstat.st_mode & S_IRGRP) == S_IRGRP ? *(long_format + 4) = 'r' : 0;
	(file->lstat.st_mode & S_IWGRP) == S_IWGRP ? *(long_format + 5) = 'w' : 0;
	(file->lstat.st_mode & S_IXGRP) == S_IXGRP ? *(long_format + 6) = 'x' : 0;
	(file->lstat.st_mode & S_IROTH) == S_IROTH ? *(long_format + 7) = 'r' : 0;
	(file->lstat.st_mode & S_IWOTH) == S_IWOTH ? *(long_format + 8) = 'w' : 0;
	(file->lstat.st_mode & S_IXOTH) == S_IXOTH ? *(long_format + 9) = 'x' : 0;
}

void	get_nblink(char *long_format, t_file *file)
{
	int	padd;

	padd = file->max.nblink - file->len.nblink;
	ft_memcpy(long_format + 12 + padd, ull_toa(file->stat.st_nlink), file->len.nblink);
}

void	get_user_owner(char *long_format, t_file *file)
{
	ft_memcpy(long_format + 12 + file->max.nblink + 1, file->usr->pw_name, file->len.user);
	ft_memcpy(long_format + 12 + file->max.nblink + 1 + file->max.user + 2, file->grp->gr_name, file->len.group);
}
