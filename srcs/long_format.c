/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:40:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/08 18:27:37 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_usr_group_struct(t_file *elem)
{	
		elem->len.nblink = ull_len(elem->lstat.st_nlink);
		elem->usr = getpwuid(elem->lstat.st_uid);	
		elem->len.user = ft_strlen(elem->usr->pw_name);
		elem->grp = getgrgid(elem->lstat.st_gid);	
		elem->len.group = ft_strlen(elem->grp->gr_name);
		elem->len.size = ull_len(elem->lstat.st_size);
}

int		set_max_len(t_file *files)
{
	t_file		*temp;
	t_max		max;

	max.nblink = 0;
	max.user = 0;
	max.group = 0;
	max.size = 0;
	temp = files;
	while (temp)
	{
		max.nblink < temp->len.nblink ? max.nblink = temp->len.nblink : 0;
		max.user < temp->len.user ? max.user = temp->len.user : 0;
		max.group < temp->len.group ? max.group = temp->len.group : 0;
		max.size < temp->len.size ? max.size = temp->len.size : 0;
		temp = temp->next;
	}
	temp = files;
	while (temp)
	{
		temp->max = max;
		temp = temp->next;
	}
	return (max.nblink + max.user + max.group + max.size + 31);
}

void	fill_long_format(t_file *files, t_opt *option)
{
	t_file	*temp;

	temp = files;
	while (temp)
	{
		temp->long_format = get_long_format(temp, set_max_len(files), option);
		temp = temp->next;
	}
}

char	*get_long_format(t_file *file, int max_len, t_opt *option)
{
	char	*long_format;
	int		len;

	len = max_len + ft_strlen(file->name);
	if (((file->lstat.st_mode & S_IFMT) ^ S_IFLNK) == 0)
		len += file->lstat.st_size + 4;
	long_format = ft_strnew(len);
	ft_memset(long_format, ' ', len);
	get_type(long_format, file);
	get_perms(long_format, file);
	get_nblink(long_format, file);
	get_user_owner(long_format, file);
	get_size(long_format, file);
	get_timestamp(long_format, file, option);
	get_name(long_format, file);
	return (long_format);
}
