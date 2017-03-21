/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_details_part2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:04:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/13 18:27:34 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_size(char *long_format, t_file *file, t_max *max)
{
	int		padd;
	char	*size;

	if (*long_format == 'c' || *long_format == 'b')
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

	if (*long_format != 'c' && *long_format != 'b')
		return ;

	ft_putnbr_endl(max->maj);
	ft_putnbr_endl(max->min);
	// ft_putnbr_endl(file->len.size);
	ft_putnbr_endl(max->size);
	// padd_maj = (max->size - file->len.size) + max->maj - file->len.maj; 
	padd_maj = max->maj - file->len.maj; 
	// ft_putnbr_endl(padd_maj);

	s_maj = ft_itoa(FT_MAJ(file->lstat.st_rdev));
	temp = ft_strjoin(s_maj, ", ");
	ft_memcpy(long_format + 12
	+ max->nblink + 1
	+ max->user + 2
	+ max->group + 2
	+ padd_maj, temp, file->len.maj + 2);
	
	// ft_memcpy(long_format + 12
	// + max->nblink + 1
	// + max->user + 2
	// + max->group + 2
	// + max->maj, ", ", 2);

	padd_min = max->min - file->len.min;

	s_min = ft_itoa(FT_MIN(file->lstat.st_rdev));
	ft_memcpy(long_format + 12
	+ max->nblink + 1
	+ max->user + 2
	+ max->group + 2
	+ max->maj + 2 + padd_min, s_min, file->len.min);
	free(temp);
	free(s_maj);
	free(s_min);
}

void	get_timestamp(char *long_format, t_file *file, t_opt *option, t_max *max)
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
		ft_memcpy(timestamp + 7, t_time + 19, 5);
	ft_memcpy(long_format + 12
		+ max->nblink + 1
		+ max->user + 2
		+ max->group + 2
		+ max->size + 1, timestamp, 12);
	//free(t_time);
	free(timestamp);
}

void	get_name(char *long_format, t_file *file, t_max *max)
{
	char	*link_name;
	char	*arrow;
	int		len_name;
	int		padd;

	len_name = ft_strlen(file->name);
	padd = 12 + max->nblink + 1 + max->user + 2
		+ max->group + 2 + max->size + 1 + 12 + 1;
	ft_memcpy(long_format + padd, file->name, len_name);
	if (*long_format == 'l')
	{
		if (!(link_name = (char*)malloc(sizeof(char) * (file->lstat.st_size + 1))))
			ft_exit("Unable to malloc link_name");
		if ((readlink(file->path, link_name, file->lstat.st_size + 1)) == -1)
			ft_exit("Unable to get link name");
		*(link_name + file->lstat.st_size) = 0;
		arrow = ft_strjoin(" -> ", link_name);
		ft_memcpy(long_format + padd + len_name, arrow, file->lstat.st_size + 4);
		free(link_name);
		free(arrow);
	}
}
