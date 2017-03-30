/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 10:41:01 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/30 17:30:16 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_ascii(t_file **temp, t_file **left, t_file **right)
{
	if ((ft_strcmp((*left)->name, (*right)->name)) < 0)
	{
		*temp = *left;
		*left = (*left)->next;
	}
	else
	{
		*temp = *right;
		*right = (*right)->next;
	}
}

void	sort_time_modified(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_mtimespec.tv_sec
		== (*right)->lstat.st_mtimespec.tv_sec)
		sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_mtimespec.tv_sec
			> (*right)->lstat.st_mtimespec.tv_sec)
		{
			*temp = *left;
			*left = (*left)->next;
		}
		else
		{
			*temp = *right;
			*right = (*right)->next;
		}
	}
}

void	sort_last_access(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_atimespec.tv_sec
		== (*right)->lstat.st_atimespec.tv_sec)
		sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_atimespec.tv_sec
			> (*right)->lstat.st_atimespec.tv_sec)
		{
			*temp = *left;
			*left = (*left)->next;
		}
		else
		{
			*temp = *right;
			*right = (*right)->next;
		}
	}
}

void	sort_size(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_size == (*right)->lstat.st_size)
		sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_size > (*right)->lstat.st_size)
		{
			*temp = *left;
			*left = (*left)->next;
		}
		else
		{
			*temp = *right;
			*right = (*right)->next;
		}
	}
}
