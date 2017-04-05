/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_details_part1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:01:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/05 11:57:35 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_type(char *long_format, t_file *file)
{
	ft_memset(long_format, '-', 10);
	S_ISBLK(file->lstat.st_mode) ? *long_format = 'b' : 0;
	S_ISCHR(file->lstat.st_mode) ? *long_format = 'c' : 0;
	S_ISDIR(file->lstat.st_mode) ? *long_format = 'd' : 0;
	S_ISLNK(file->lstat.st_mode) ? *long_format = 'l' : 0;
	S_ISSOCK(file->lstat.st_mode) ? *long_format = 's' : 0;
	S_ISFIFO(file->lstat.st_mode) ? *long_format = 'p' : 0;
}

void	get_perms(char *long_format, t_file *file)
{
	(file->lstat.st_mode & S_IRUSR) == S_IRUSR ? *(long_format + 1) = 'r' : 0;
	(file->lstat.st_mode & S_IWUSR) == S_IWUSR ? *(long_format + 2) = 'w' : 0;
	(file->lstat.st_mode & S_IXUSR) == S_IXUSR ? *(long_format + 3) = 'x' : 0;
	(file->lstat.st_mode & S_IRGRP) == S_IRGRP ? *(long_format + 4) = 'r' : 0;
	(file->lstat.st_mode & S_IWGRP) == S_IWGRP ? *(long_format + 5) = 'w' : 0;
	(file->lstat.st_mode & S_IXGRP) == S_IXGRP ? *(long_format + 6) = 'x' : 0;
	(file->lstat.st_mode & S_IROTH) == S_IROTH ? *(long_format + 7) = 'r' : 0;
	(file->lstat.st_mode & S_IWOTH) == S_IWOTH ? *(long_format + 8) = 'w' : 0;
	(file->lstat.st_mode & S_IXOTH) == S_IXOTH ? *(long_format + 9) = 'x' : 0;
	if ((file->lstat.st_mode & S_ISUID) == S_ISUID)
	{
		*(long_format + 3) == '-' ? *(long_format + 3) = 'S' : 0;
		*(long_format + 3) == 'x' ? *(long_format + 3) = 's' : 0;
	}
	if ((file->lstat.st_mode & S_ISGID) == S_ISGID)
	{
		*(long_format + 6) == '-' ? *(long_format + 6) = 'S' : 0;
		*(long_format + 6) == 'x' ? *(long_format + 6) = 's' : 0;
	}
	if ((file->lstat.st_mode & S_ISVTX) == S_ISVTX)
	{
		*(long_format + 9) == '-' ? *(long_format + 9) = 'T' : 0;
		*(long_format + 9) == 'x' ? *(long_format + 9) = 't' : 0;
	}
}

void	get_attr_acl(char *long_format, t_file *file)
{
	acl_t	acl;

	if (S_ISLNK(file->lstat.st_mode))
	{
		acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
		acl ? *(long_format + 10) = '+' : 0;
		acl_free((void*)acl);
		listxattr(file->path, NULL, 0, XATTR_NOFOLLOW) > 0 ?
			*(long_format + 10) = '@' : 0;
	}
	else
	{
		acl = acl_get_file(file->path, ACL_TYPE_EXTENDED);
		acl ? *(long_format + 10) = '+' : 0;
		acl_free((void*)acl);
		listxattr(file->path, NULL, 0, 0) > 0 ? *(long_format + 10) = '@' : 0;
	}
}

void	get_nblink(char *long_format, t_file *file, t_max *max)
{
	int		padd;
	char	*nlink;

	nlink = ull_toa(file->stat.st_nlink);
	padd = max->nblink - file->len.nblink;
	ft_memcpy(long_format + 12 + padd, nlink, file->len.nblink);
	free(nlink);
}

void	get_user_owner(char *long_format, t_file *file, t_max *max)
{
	if (file->usr)
		ft_memcpy(long_format + 12 + max->nblink + 1,
			file->usr->pw_name, file->len.user);
	else
		ft_memcpy(long_format + 12 + max->nblink + 1,
			ft_itoa(file->lstat.st_uid), file->len.user);
	if (file->grp)
		ft_memcpy(long_format + 12 + max->nblink + 1 + max->user + 2,
			file->grp->gr_name, file->len.group);
	else
		ft_memcpy(long_format + 12 + max->nblink + 1 + max->user + 2,
			ft_itoa(file->lstat.st_gid), file->len.group);

}
