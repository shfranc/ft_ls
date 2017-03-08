/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_details_part2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:04:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/08 12:28:13 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_size(char *long_format, t_file *file)
{
	int		padd;
	char	*size;

	// faire majeur mineur

	padd = file->max.size - file->len.size;
	size = ull_toa(file->lstat.st_size);
	ft_memcpy(long_format + 12
		+ file->max.nblink + 1
		+ file->max.user + 2
		+ file->max.group + 2
		+ padd, size, file->len.size);
	free(size);
}

void	get_timestamp(char *long_format, t_file *file, t_opt *option)
{
	char	*t_time;
	char	*timestamp;

	if (option->u)
		file->lstat.st_mtimespec.tv_sec = file->lstat.st_atimespec.tv_sec;
	t_time = ctime(&file->lstat.st_mtimespec.tv_sec);
	timestamp = ft_strnew(12);
	ft_memcpy(timestamp, t_time + 4, 12);
	if ((time(NULL) - file->lstat.st_mtimespec.tv_sec) > 15811200
		|| file->lstat.st_mtimespec.tv_sec > time(NULL))
		ft_memcpy(timestamp + 7, t_time + 19, 4);
	ft_memcpy(long_format + 12
		+ file->max.nblink + 1
		+ file->max.user + 2
		+ file->max.group + 2
		+ file->max.size + 1, timestamp, 12);
	//free(t_time);
	free(timestamp);
}

void	get_name(char *long_format, t_file *file)
{
	char	*link_name;
	char	*arrow;
	int		len_name;

	len_name = ft_strlen(file->name);
	ft_memcpy(long_format + 12
			+ file->max.nblink + 1
			+ file->max.user + 2
			+ file->max.group + 2
			+ file->max.size + 1 + 12 + 1, file->name, len_name);
	if (*long_format == 'l')
	{
		if (!(link_name = (char*)malloc(sizeof(char) * (file->lstat.st_size + 1))))
			ft_exit("Unable to malloc link_name");
		readlink(file->name, link_name, file->lstat.st_size + 1);
		*(link_name + file->lstat.st_size) = 0;
		arrow = ft_strjoin(" -> ", link_name);
		ft_memcpy(long_format + 12
			+ file->max.nblink + 1
			+ file->max.user + 2
			+ file->max.group + 2
			+ file->max.size + 1
			+ 12 + 1 + len_name, arrow, file->lstat.st_size + 4);
		free(link_name);
		free(arrow);
	}
}
