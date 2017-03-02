/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:40:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/02 16:28:30 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_llong_struct(t_file *elem)
{	
		elem->len.nblink = ull_len(elem->stat.st_nlink);
//		ft_putnbr_endl(elem->len.nblink);

		if (!(elem->usr = (struct passwd*)malloc(sizeof(struct passwd))))
			return ; // configurer un exit ?
		elem->usr = getpwuid(elem->stat.st_uid);	
//		ft_putendl(elem->usr->pw_name);
		elem->len.user = ft_strlen(elem->usr->pw_name);
//		ft_putnbr_endl(elem->len.user);

		if (!(elem->grp = (struct group*)malloc(sizeof(struct group))))
			return ; // exit ?
		elem->grp = getgrgid(elem->stat.st_gid);	
//		ft_putendl(elem->grp->gr_name);
		elem->len.group = ft_strlen(elem->grp->gr_name);
//		ft_putnbr_endl(elem->len.group);
		
		elem->len.size = ull_len(elem->stat.st_size);
//		ft_putnbr_endl(elem->len.size);
}

int		set_max_len(t_file **files)
{
	t_file		*temp;
	t_max		max;

	max.nblink = 0;
	max.user = 0;
	max.group = 0;
	max.size = 0;
	temp = *files;
	while (temp)
	{
		max.nblink < temp->len.nblink ? max.nblink = temp->len.nblink : 0;
		max.user < temp->len.user ? max.user = temp->len.user : 0;
		max.group < temp->len.group ? max.group = temp->len.group : 0;
		max.size < temp->len.size ? max.size = temp->len.size : 0;
		temp = temp->next;
	}
	max.total = max.nblink + max.user + max.group + max.size + 31;
	temp = *files;
	while (temp)
	{
		temp->max = max;
		temp = temp->next;
	}
	ft_putstr("MAX LEN = ");
	ft_putnbr_endl((*files)->max.total);
	return (max.total);
}

void	fill_long_format(t_file **files)
{
	t_file	*temp;
	int		max_len;

	max_len = set_max_len(files);
	temp = *files;
	while (temp)
	{
		temp->long_format = get_long_format(temp, max_len);
		temp = temp->next;
	}
}

char	*get_long_format(t_file *file, int max_len)
{
	char	*long_format;

	long_format = ft_strnew(max_len + ft_strlen(file->name));
	ft_memset(long_format, ' ', max_len + ft_strlen(file->name));

	get_type(&long_format, file);
	get_perms(&long_format, file);
	get_nblink(&long_format, file);
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
//	temp[10] = ' ';
//	temp[11] = ' ';
}

void	get_nblink(char **long_format, t_file *file)
{
	int	padd;

	(void)file;
	padd = file->max.nblink - file->len.nblink;
	//padd = 3;
	ft_putnbr_endl(padd);
	*(long_format + 12) = ft_strncpy((*long_format + 12), ull_toa(file->stat.st_nlink), file->len.nblink);
	//*(long_format + 12 + padd) = ft_strncpy((*long_format + 12 + padd), ull_toa(file->stat.st_nlink), file->len.nblink);


	*(*long_format + 12 + file->max.nblink + 1) = 'u';
	*(*long_format + 12 + file->max.nblink + 1 + file->max.user + 2) = 'g';
	*(*long_format + 12 + file->max.nblink + 1 + file->max.user + 2 + file->max.group + 2) = 's';
	*(*long_format + 12 + file->max.nblink + 1 + file->max.user + 2 + file->max.group + 2 + file->max.size + 1) = 't';
	*(*long_format + 12 + file->max.nblink + 1 + file->max.user + 2 + file->max.group + 2 + file->max.size + 1 + 12 + 1) = 'N';
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

char	*ull_toa(unsigned long long nb)
{
	int		len;
	char	*s;

	len = ull_len(nb);
	s = ft_strnew(len);
	if (nb == 0)
		*(s + len - 1) = '0';
	while (nb > 0 && len-- > 0)
	{
		*(s + len) = nb % 10 + '0';
		nb = nb / 10;
	}
	return (s);
}

