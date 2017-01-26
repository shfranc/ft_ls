/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 11:50:25 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/26 13:03:59 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*ft_filenew(char *av)
{
	t_file		*elem;
	struct stat	l_stat;
	int			ret_lstat;

	if (!(elem = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	ret_lstat = lstat(av, &l_stat);
	elem->name = ft_strdup(av);
	elem->error = errno;
	elem->lstat = l_stat;
	elem->next = NULL;
	elem->inside = NULL;
	return (elem);
}

void	ft_fileadd_last(t_file **alst, t_file *new)
{
	t_file	*temp;

	temp = *alst;
	if (alst)
	{
		if (temp == NULL)
			temp = new;
		else
		{
			while (temp->next)
				temp = temp->next;
			temp->next = new;
		}
	}
//	else
//		alst = &temp;
}

