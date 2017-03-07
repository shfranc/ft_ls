/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_details_part2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:04:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/07 19:07:19 by sfranc           ###   ########.fr       */
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

void	get_timestamp(char *long_format, t_file *file, t_opt *option)
{
	char	*time;
	char	*timestamp;

	// definir les tailles sup a 6 mois pour mettre l'annee uniquement)	
	
	time = ft_strnew(26);
	if (option->u)
		ft_memcpy(time, ctime(&file->lstat.st_atimespec.tv_sec), 26);
	else
		time = ctime(&file->lstat.st_mtimespec.tv_sec);
	timestamp = ft_strnew(12);
	ft_memcpy(timestamp, time + 4, 12);
	ft_memcpy(long_format + 12
		+ file->max.nblink + 1
		+ file->max.user + 2
		+ file->max.group + 2
		+ file->max.size + 1, timestamp, 12);
//	free(time);
//	free(timestamp);
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
