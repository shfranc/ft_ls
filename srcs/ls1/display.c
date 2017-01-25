/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:54:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/25 11:41:25 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_names(t_file *names)
{
	t_file	*temp;

	temp = names;
	while (temp)
	{
		if (temp->error == 0)
			ft_putendl(temp->name);
		if (temp->inside != NULL)
		{
			ft_putendl("--- inside");
			display_names(temp->inside);
		}
		temp = temp->next;
	}
}

void	display_errors(t_file *names)
{
	t_file	*temp;

	temp = names;
	while (temp)
	{
		if (temp->error != 0)
		{
			ft_putstr("ft_ls :");
			ft_putstr(temp->name);
			ft_putstr(": ");
			ft_putendl(strerror(temp->error));
		}
		temp = temp->next;
	}
}
