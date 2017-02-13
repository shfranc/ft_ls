/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 10:41:01 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/13 17:55:09 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*which_sort(t_file *files, t_opt *options)
{
	int		len;

	if ((len = file_list_len(files)) > 2)
		return (files);
	if ((options->a))
		return (divide_list(files->inside));
	return (files);
}


t_file	*divide_list(t_file *files)
{
	t_file	*left;
	t_file	*right;
	int		len;
	int		half;
	int		i;

	t_file	*temp;


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

	ft_putstr("\n --left : ");
	ft_putnbr_endl(file_list_len(left));
	display_inside(left);
	ft_putstr("\n --right : ");
	ft_putnbr_endl(file_list_len(right));
	display_inside(right);
	
	temp = merge(&left, &right);
	ft_putendl("\n ==== result left");
	display_inside(temp);
	ft_putendl("\n ==== result right");
	display_inside(right);
	
//	left = divide_list(left);
//	right = divide_list(right);

	return (NULL);
//	return (merge(left, right)); // c'est dans merge qu'on aura l'application du tri.
//	return (merge(divide_list(left), divide_list(right)));
}

t_file	*merge(t_file **left, t_file **right)
{
//	t_file	*head;
	t_file	*temp;

	ft_putendl("\n====== MERGE ");
	ft_putendl("\n --left :");
	display_inside(*left);
	ft_putendl("\n --right :");
	display_inside(*right);
	ft_putendl("\n====== END MERGE ");

//	if (left->next == NULL || right->next == NULL)
//	{
		if ((ft_strcmp((*left)->name, (*right)->name)) < 0)
		{
			temp = (*right)->next;
			(*right)->next = (*left)->next;
			(*left)->next = *right;
			*right = temp;
		}
//	}
	return (*left);
}

/*
void	insert_elem(t_file **new, t_file *elem)
{
}
*/
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
