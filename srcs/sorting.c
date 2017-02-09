/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 10:41:01 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/09 17:56:28 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	which_sort(t_file *files, t_opt *options)
{
	int	len;

	if (options->f)
		return ;
	if ((len = file_list_len(files->inside)) < 2)
		return ;
	if (options->a)
		sorting(files->inside, len);
}

t_file	*sorting(t_file *files, int len)
{
	t_file	*temp_1;
	t_file	*temp_2;
	t_file	*temp_3;
	int		half_1;
	int		half_2;

	temp_1 = files;
	half_1 = len / 2; // on split en 2 chaines
	half_2 = len - P;
	if (half_1 >= 2) // premiere moitie avec au moins 2 elements a trier
	{
		temp_2 = sorting(temp_1, half_1); //
		if (half_2 >= 2) // deuxieme moitie avec au mmoins 2 elements a trier  
		temp_3 = sorting(temp_2, half_2); // intervention de temp_3...
	}
	else
		temp_2 = temp_1->next; // on reconstitue la chaine
	merging(P, p, Q, q); // on decoupe notre liste en des petites listes de 1 ou 2 elements, qu'on fusionne ensuite.
}


/*void	merging()
{
}*/

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
