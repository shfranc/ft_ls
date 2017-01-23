/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:54:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/23 19:22:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_names(t_list *names)
{
	while (names)
	{
		ft_putendl(names->content);
		names = names->next;
	}
}

void	set_errors(char **errors, char *message, char *file, int nb_err)
{
	char	*temp;

	(void)errors;
	(void)message;
	(void)nb_err;
	temp = ft_strjoin(file, " :");
//	*(errors + nb_err - 1) = ft_strjoin(temp, message);
}

void	put_errors(char **errors, int nb_err)
{
	while (nb_err--)
	{
		ft_putendl(*errors);
		errors++;
	}
}
