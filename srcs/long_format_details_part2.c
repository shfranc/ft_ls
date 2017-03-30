/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_details_part2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:04:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/30 18:37:51 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_size(char *long_format, t_file *file, t_max *max)
{
	int		padd;
	char	*size;

	if (((file->lstat.st_mode & S_IFMT) ^ S_IFCHR) == 0
			|| ((file->lstat.st_mode & S_IFMT) ^ S_IFBLK) == 0)
		return ;
	padd = max->size - file->len.size;
	size = ull_toa(file->lstat.st_size);
	ft_memcpy(long_format + 12
		+ max->nblink + 1
		+ max->user + 2
		+ max->group + 2
		+ padd, size, file->len.size);
	free(size);
}

void	get_maj_min(char *long_format, t_file *file, t_max *max)
{
	int		padd_maj;
	int		padd_min;
	char	*s_maj;
	char	*s_min;
	char	*temp;

	if (((file->lstat.st_mode & S_IFMT) ^ S_IFCHR) != 0
			&& ((file->lstat.st_mode & S_IFMT) ^ S_IFBLK) != 0)
		return ;
	padd_maj = max->maj - file->len.maj;
	s_maj = ft_itoa(FT_MAJ(file->lstat.st_rdev));
	temp = ft_strjoin(s_maj, ", ");
	ft_memcpy(long_format + 12 + max->nblink + 1
		+ max->user + 2 + max->group + 2
		+ padd_maj, temp, file->len.maj + 2);
	padd_min = max->min - file->len.min;
	s_min = ft_itoa(FT_MIN(file->lstat.st_rdev));
	ft_memcpy(long_format + 12 + max->nblink + 1
		+ max->user + 2 + max->group + 2
		+ max->maj + 2 + padd_min, s_min, file->len.min);
	free(temp);
	free(s_maj);
	free(s_min);
}

void	get_timestamp(char *long_format, t_file *file,
	t_opt *option, t_max *max)
{
	char	*t_time;
	char	*timestamp;

	if (option->u)
		file->lstat.st_mtimespec.tv_sec = file->lstat.st_atimespec.tv_sec;
	if (option->u_u)
		file->lstat.st_mtimespec.tv_sec = file->lstat.st_birthtimespec.tv_sec;
	t_time = ctime(&file->lstat.st_mtimespec.tv_sec);
	timestamp = ft_strnew(12);
	ft_memcpy(timestamp, t_time + 4, 12);
	if ((time(NULL) - file->lstat.st_mtimespec.tv_sec) > 15811200
		|| file->lstat.st_mtimespec.tv_sec > time(NULL))
		ft_memcpy(timestamp + 7, t_time + 19, 5);
	ft_memcpy(long_format + 12
		+ max->nblink + 1
		+ max->user + 2
		+ max->group + 2
		+ max->size + 1, timestamp, 12);
	free(timestamp);
}

void	get_name(char *long_format, t_file *file, t_max *max)
{
	char	*link_name;
	char	*arrow;
	int		len_name;
	int		padd;
	int		ret;

	len_name = ft_strlen(file->name);
	padd = 12 + max->nblink + 1 + max->user + 2
		+ max->group + 2 + max->size + 1 + 12 + 1;
	ft_memcpy(long_format + padd, file->name, len_name);
	if (((file->lstat.st_mode & S_IFMT) ^ S_IFLNK) == 0)
	{
		if (!(link_name = ft_strnew(1024)))
			ft_exit("Unable to malloc link_name");
		if ((ret = readlink(file->path, link_name, 1024)) == -1)
			ft_exit("Unable to get link name");
		arrow = ft_strjoin(" -> ", link_name);
		ft_memcpy(long_format + padd + len_name, arrow, ft_strlen(arrow));
		*(long_format + padd + len_name + ft_strlen(arrow)) = 0;
		free(link_name);
		free(arrow);
	}
}
