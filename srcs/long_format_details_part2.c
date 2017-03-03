/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_details_part2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:04:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/03 15:28:46 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_size(char *long_format, t_file *file)
{
	int	padd;

	// faire majeur mineur

	padd = file->max.size - file->len.size;
	ft_memcpy(long_format + 12
		+ file->max.nblink + 1
		+ file->max.user + 2
		+ file->max.group + 2
		+ padd, ull_toa(file->lstat.st_size), file->len.size);

}

void	get_timestamp(char *long_format, t_file *file, t_opt *options)
{
	char	*time;
	char	*time_stamp;

	// definir les tailles sup a 6 mois pour mettre l'annee uniquement)	
	
	if (options->u)
		time = ctime(&file->lstat.st_atimespec.tv_sec);
	else
		time = ctime(&file->lstat.st_mtimespec.tv_sec);
	time_stamp = ft_strnew(12);
	ft_memcpy(time_stamp, time + 4, 12);
	ft_memcpy(long_format + 12
		+ file->max.nblink + 1
		+ file->max.user + 2
		+ file->max.group + 2
		+ file->max.size + 1, time_stamp, 12);
}

void	get_name(char *long_format, t_file *file)
{
	char	*file_name;
	char	*link_name;
	int		len_name;

	file_name = ft_strrchr(file->name, '/') +1;
	ft_putendl(file_name);
	len_name = ft_strlen(file_name);
	ft_memcpy(long_format + 12 + file->max.nblink + 1 + file->max.user + 2 + file->max.group + 2 + file->max.size + 1 + 12 + 1, file_name, len_name);
	if (*long_format == 'l')
	{
		if (!(link_name = (char*)malloc(sizeof(char) * (file->lstat.st_size + 1))))
			return ;
		readlink(file->name, link_name, file->lstat.st_size + 1);
		*(link_name + file->lstat.st_size) = 0;
		ft_putstr("LIEN = ");
		ft_putendl(link_name);
		ft_memcpy(long_format + 12
			+ file->max.nblink + 1
			+ file->max.user + 2
			+ file->max.group + 2
			+ file->max.size + 1
			+ 12 + 1 + len_name, " -> ", 4);
		ft_memcpy(long_format + 12
			+ file->max.nblink + 1
			+ file->max.user + 2
			+ file->max.group + 2
			+ file->max.size + 1
			+ 12 + 1 + len_name
			+ 4, link_name, file->lstat.st_size);
	}
	else
		ft_memcpy(long_format + 12
			+ file->max.nblink + 1
			+ file->max.user + 2
			+ file->max.group + 2
			+ file->max.size + 1
			+ 12 + 1, file_name, len_name);
}
