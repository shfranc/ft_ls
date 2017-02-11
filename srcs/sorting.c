/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 10:41:01 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/11 16:12:05 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*which_sort(t_file *files, t_opt *options)
{
	t_file	*new;
	int		len;

	new = files;
	if (options->f)
		return (files);
	if ((len = file_list_len(files->inside)) < 2)
		return (files);
	if ((options->a))
		new = divide_list(files->inside);
	display_inside(new);
	return (new);
}


t_file	*divide_list(t_file *files)
{
	t_file	*left;
	t_file	*right;
	int		len;
	int		half;
	int		i;

	len = file_list_len(files);

	if (len == 0 || len == 1) // si plus d'element ou un seul element, on retourne la liste, fin de la division)
		return (files);
	
	half = len / 2; // on split en 2 chaines
	
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

	ft_putendl("\n --left :");
	display_inside(left);
	ft_putendl("\n --right :");
	display_inside(right);
	
	left = divide_list(left);
	right = divide_list(right);

	return (merge(left, right)); // c'est dans merge qu'on aura l'application du tri.

}

t_file	*merge(t_file *left, t_file *right)
{
	t_file	*new;
	
	ft_putendl("\n ----MERGE :");
	ft_putendl("\n --left :");
	display_inside(left);
	ft_putendl("\n --right :");
	display_inside(right);

	while (left != NULL && right != NULL)
	{
		ft_putendl("\n ----MERGE 1:");
		if (ft_strcmp(left->name, right->name) > 0)
		{
			ft_putendl("\n ----MERGE 1 left:");
			insert_elem(&new, left);

			ft_putendl("check new");
			display_inside(new);

			left = left->next;

//			ft_putnbr_endl((int)left);
		//	display_inside(left);
			ft_putendl("lol");
		}
		else
		{
			ft_putendl("\n ----MERGE 1 right:");
			insert_elem(&new, right);
			right = right->next;
			ft_putnbr_endl((int)right);
		}
	}

	ft_putendl("\n ----MERGE 2:");
//	if (left != NULL)
//	{
//		insert_elem(&new, left);
//		return (new);
//		left = left->next;
//	}

//	ft_putendl("\n ----MERGE 3:");
	if (right != NULL)
	{
		insert_elem(&new, right);
		return (new);
		right = right->next;
	}
	
	display_inside(new);

	return (new);
}

void	insert_elem(t_file **new, t_file *elem)
{
	ft_putendl("INSERT");
	if (*new == NULL)
	{
		ft_putendl("LOL");
		*new = elem;
		ft_putendl("LOL");
	}
	else
	{
		ft_putendl("LOLI");
		elem->next = *new;
		ft_putendl("LOLI");
		*new = elem;
		ft_putendl("LOLI");
	}
	display_inside(*new);
}

//void	ascii_sort(char *a, char *b)

int		file_list_len(t_file *files)
{
	t_file *temp;
	int		len;

	len = 0;
	temp = files;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}
