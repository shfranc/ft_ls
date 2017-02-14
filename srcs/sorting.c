/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 10:41:01 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/14 18:31:02 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*which_sort(t_file *files, t_opt *options)
{
	t_file	*new;
	int		len;

	if ((len = file_list_len(files)) < 2 || options->f)
		return (files);
	if (!options->f)
		new = divide_list(files, &sort_ascii);
	if (options->u_s)
		new = divide_list(files, &sort_size);
	if (options->t)
		new = divide_list(files, &sort_time_modified);
	return (new);
}


t_file	*divide_list(t_file *files, void (*f)(t_file**, t_file**, t_file**))
{
	t_file	*left;
	t_file	*right;
	int		len;
	int		half;
	int		i;

	if (files->next == NULL) // si un seul element, on retourne la liste, fin de la division
		return (files);
	len = file_list_len(files);
	half = len / 2;
	i = 0;
	left = files;
	while (i < half - 1)
	{
		left = left->next;
		i++;
	}
	right = left->next; // on separe la liste en 2.
	left->next = NULL;
	left = files;
	left = divide_list(left, f);
	right = divide_list(right, f);
	return (merge(left, right, f));
}

t_file	*merge(t_file *left, t_file *right, void (*f)(t_file**, t_file**, t_file**))
{
	t_file	*head;
	t_file	*temp;
	t_file	*tail;

	head = NULL;
	while (left || right) // tant que les deux listes ne sont pqs finies
	{
		if (!left) // si left est fini, on raccroche le dernier maillon de right
		{
			temp = right;
			right = right->next;
		}
		else
		{
			if (!right) // si right est finie on raccroche le dernier maillon de left
			{
				temp = left;
				left = left->next;
			}
			else
				f(&temp, &left, &right);
		}
		if (!head)
			head = temp; // creation ou ajout a la suite du maillon selectionne
		else
			tail->next = temp;
		tail = temp;
	}
	return (head);
}

void	pick_elem(t_file **temp, t_file **elem);
{
	*temp = *elem;

}

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
	if ((*left)->lstat.st_mtimespec.tv_sec >= (*right)->lstat.st_mtimespec.tv_sec)
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

/*
void	sort_time_last_access(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_atimespec.tv_sec >= (*right)->lstat.st_atimespec.tv_sec)
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
*/

void	sort_size(t_file **temp, t_file **left, t_file **right)
{
	if ((*left)->lstat.st_size >= (*right)->lstat.st_size)
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

int		file_list_len(t_file *files)
{
	t_file *temp;
	int		len;

	if (!files)
		return (0);

	len = 0;
	temp = files;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}
