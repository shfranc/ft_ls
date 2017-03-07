/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_sorting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 10:31:09 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/07 17:43:41 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reverse_sort_ascii(t_file **temp, t_file **left, t_file **right)
{
	if ((ft_strcmp((*left)->name, (*right)->name)) > 0)
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

void	reverse_sort_time_modified(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_mtimespec.tv_sec
			< (*right)->lstat.st_mtimespec.tv_sec
			|| ((*left)->lstat.st_mtimespec.tv_sec
				== (*right)->lstat.st_mtimespec.tv_sec
				&& (*left)->lstat.st_mtimespec.tv_nsec
				<= (*right)->lstat.st_mtimespec.tv_nsec))
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

/*void	reverse_sort_time_modified(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_mtimespec.tv_sec == (*right)->lstat.st_mtimespec.tv_sec)
		reverse_sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_mtimespec.tv_sec < (*right)->lstat.st_mtimespec.tv_sec)
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
}*/

void	reverse_sort_last_access(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_atimespec.tv_sec == (*right)->lstat.st_atimespec.tv_sec)
		reverse_sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_atimespec.tv_sec < (*right)->lstat.st_atimespec.tv_sec)
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

void	reverse_sort_size(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_size == (*right)->lstat.st_size)
		reverse_sort_ascii(temp, left, right);
	else
	{
		if ((*left)->lstat.st_size < (*right)->lstat.st_size)
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
