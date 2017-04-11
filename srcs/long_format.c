/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:40:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/11 15:47:40 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	get_len(t_file *elem)
{
	elem->len.nblink = ull_len(elem->lstat.st_nlink);
	get_usr_group_struct(elem);
	if (S_ISCHR(elem->lstat.st_mode) || S_ISBLK(elem->lstat.st_mode))
	{
		elem->len.maj = ft_intsize(FT_MAJ(elem->lstat.st_rdev));
		elem->len.min = ft_intsize(FT_MIN(elem->lstat.st_rdev));
		elem->len.size = elem->len.maj + elem->len.min + 2;
	}
	else
		elem->len.size = ull_len(elem->lstat.st_size);
}

void	init_max(t_max *max)
{
	max->nblink = 0;
	max->user = 0;
	max->group = 0;
	max->size = 0;
	max->maj = 0;
	max->min = 0;
}

void	set_max_len(t_file *files, t_max *max)
{
	t_file		*temp;

	init_max(max);
	temp = files;
	while (temp)
	{
		max->nblink < temp->len.nblink ? max->nblink = temp->len.nblink : 0;
		max->user < temp->len.user ? max->user = temp->len.user : 0;
		max->group < temp->len.group ? max->group = temp->len.group : 0;
		if (S_ISCHR(temp->lstat.st_mode) || S_ISBLK(temp->lstat.st_mode))
		{
			max->maj < temp->len.maj ? max->maj = temp->len.maj : 0;
			max->min < temp->len.min ? max->min = temp->len.min : 0;
			temp->len.size < 8 ? max->size = 8 : 0;
		}
		max->size < temp->len.size ? max->size = temp->len.size : 0;
		temp = temp->next;
	}
	temp = files;
	while (temp)
	{
		temp->len.total = max->nblink + max->user + max->group + max->size + 31;
		temp = temp->next;
	}
}

void	fill_long_format(t_file *files, t_opt *option)
{
	t_file	*temp;
	t_max	max;

	temp = files;
	set_max_len(files, &max);
	while (temp)
	{
		if ((temp->error == 0 || temp->error == 20 || temp->error == 2))
			temp->long_format = get_long_format(temp, &max, option);
		temp = temp->next;
	}
}

char	*get_long_format(t_file *file, t_max *max, t_opt *option)
{
	char	*long_format;
	int		len;

	len = file->len.total + ft_strlen(file->name);
	if (S_ISLNK(file->lstat.st_mode))
		len += 1024;
	if (!(long_format = ft_strnew_set(len, ' ')))
		ft_exit("Unable to malloc long_format");
	get_type(long_format, file);
	get_perms(long_format, file);
	get_attr_acl(long_format, file);
	get_nblink(long_format, file, max);
	get_user_owner(long_format, file, max);
	get_size(long_format, file, max);
	get_maj_min(long_format, file, max);
	get_timestamp(long_format, file, option, max);
	get_name(long_format, file, max);
	ft_putendl(file->long_format);
	return (long_format);
}
