/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:40:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/01 17:54:08 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_llong_struct(t_file *elem)
{	
		elem->llong.len_nblink = ull_len(elem->stat.st_nlink);
//		ft_putnbr_endl(elem->llong.len_nblink);

		if (!(elem->llong.usr = (struct passwd*)malloc(sizeof(struct passwd))))
			return ; // configurer un exit ?
		elem->llong.usr = getpwuid(elem->stat.st_uid);	
//		ft_putendl(elem->llong.usr->pw_name);
		elem->llong.len_user = ft_strlen(elem->llong.usr->pw_name);
//		ft_putnbr_endl(elem->llong.len_user);

		if (!(elem->llong.grp = (struct group*)malloc(sizeof(struct group))))
			return ; // exit ?
		elem->llong.grp = getgrgid(elem->stat.st_gid);	
//		ft_putendl(elem->llong.grp->gr_name);
		elem->llong.len_group = ft_strlen(elem->llong.grp->gr_name);
//		ft_putnbr_endl(elem->llong.len_group);
		
		elem->llong.len_size = ull_len(elem->stat.st_size);
//		ft_putnbr_endl(elem->llong.len_size);
}

char	*get_long_format(t_file *file)
{
	char	*long_format;

	long_format = ft_strnew(1024);
	get_type(&long_format, file);
	get_perms(&long_format, file);
//	get_link
//	get_owner
//	get_group
//	get_size
//	get_timestamp
//	get_name
	return (long_format);
}

void	get_type(char **long_format, t_file *file)
{
	((file->lstat.st_mode & S_IFMT) ^ S_IFBLK) == 0 ? **long_format = 'b' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFCHR) == 0 ? **long_format = 'c' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFDIR) == 0 ? **long_format = 'd' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFLNK) == 0 ? **long_format = 'l' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFSOCK) == 0 ? **long_format = 's' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFIFO) == 0 ? **long_format = 'p' : 0;
	((file->lstat.st_mode & S_IFMT) ^ S_IFREG) == 0 ? **long_format = '-' : 0;
}

void	get_perms(char **long_format, t_file *file)
{
	char	*temp;

	temp = *long_format;
	ft_memset(*long_format + 1, '-', 9);
	(file->lstat.st_mode & S_IRUSR) == S_IRUSR ? temp[1] = 'r' : 0;
	(file->lstat.st_mode & S_IWUSR) == S_IWUSR ? temp[2] = 'w' : 0;
	(file->lstat.st_mode & S_IXUSR) == S_IXUSR ? temp[3] = 'x' : 0;
	(file->lstat.st_mode & S_IRGRP) == S_IRGRP ? temp[4] = 'r' : 0;
	(file->lstat.st_mode & S_IWGRP) == S_IWGRP ? temp[5] = 'w' : 0;
	(file->lstat.st_mode & S_IXGRP) == S_IXGRP ? temp[6] = 'x' : 0;
	(file->lstat.st_mode & S_IROTH) == S_IROTH ? temp[7] = 'r' : 0;
	(file->lstat.st_mode & S_IWOTH) == S_IWOTH ? temp[8] = 'w' : 0;
	(file->lstat.st_mode & S_IXOTH) == S_IXOTH ? temp[9] = 'x' : 0;
	temp[10] = ' ';
	temp[11] = ' ';
}

int		ull_len(unsigned long long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

/*
void	get_nblinks(char **long_format, t_file *file)
{

}*/
