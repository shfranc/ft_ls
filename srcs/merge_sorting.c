/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sorting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:57:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/03 17:58:09 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_comp 	g_comp[]=
{
	sort_ascii, 					// 0
	reverse_sort_ascii,				// 1 r
	sort_size,						// 2 S	-- S = 2
	reverse_sort_size,				// 3 Sr
	sort_time_modified,				// 4 t	-- t = 3			
	reverse_sort_time_modified,		// 5 tr				
	sort_last_access,				// 6 tu	u = +2
	reverse_sort_last_access,		// 7 tur
};

t_file	*which_sort(t_file *files, t_opt *option)
{
	int i;

	if ((file_list_len(files)) < 2 || option->f)
		return (files);
	i = 0;
	if (option->u_s)
		i = 2;
	if (option->t)
		i = 4;
	if (option->t && option->u)
		i += 2;
	if (option->r)
		i += 1;
	
//	ft_putnbr_endl(i);
	
	return (merge_sort(files, g_comp[i]));
}

t_file	*merge_sort(t_file *files, void (*f)(t_file**, t_file**, t_file**))
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
	left = merge_sort(left, f);
	right = merge_sort(right, f);
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
