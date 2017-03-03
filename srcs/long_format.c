/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:40:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/03 13:04:24 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_llong_struct(t_file *elem)
{	
		elem->len.nblink = ull_len(elem->lstat.st_nlink);
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
		
		elem->len.size = ull_len(elem->lstat.st_size);
//		ft_putnbr_endl(elem->len.size);
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
	max.total = max.nblink + max.user + max.group + max.size + 31;
	temp = files;
	while (temp)
	{
		temp->max = max;
		temp = temp->next;
	}
//	ft_putstr("MAX LEN = ");
//	ft_putnbr_endl(files->max.total);
	return (max.total);
}

void	fill_long_format(t_file *files, t_opt *options)
{
	t_file	*temp;
	int		max_len;

	max_len = set_max_len(files);
	temp = files;
	while (temp)
	{
		temp->long_format = get_long_format(temp, max_len, options);
		temp = temp->next;
	}
}

char	*get_long_format(t_file *file, int max_len, t_opt *options)
{
	char	*long_format;

	long_format = ft_strnew(max_len + ft_strlen(file->name));
	ft_memset(long_format, ' ', max_len + ft_strlen(file->name));

	get_type(&long_format, file);
	get_perms(&long_format, file);
	get_nblink(&long_format, file);
	get_user_owner(&long_format, file);
	get_size(&long_format, file);
	get_timestamp(&long_format, file, options);
	get_name(&long_format, file);
	(void)options;
	return (long_format);
}
