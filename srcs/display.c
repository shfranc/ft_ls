/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:54:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/23 18:53:40 by sfranc           ###   ########.fr       */
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

void	set_errors(char **errors, char *message, char *file)
{
	char	*temp;

	while (*errors != 0)
		errors++;
	temp = ft_strjoin(file, " :");
	*errors = ft_strjoin(temp, message);
}

void	put_errors(char *errors)
{
	while (errors)
	{
		ft_putendl(errors);
		errors++;
	}
}
