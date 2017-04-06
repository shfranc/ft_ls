/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 13:35:05 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:46:21 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstprint(t_list *list)
{
	t_list *temp;

	temp = list;
	while (temp)
	{
		ft_putstr((char const*)temp->content);
		ft_putchar('\n');
		ft_putnbr((int)temp->content_size);
		ft_putchar('\n');
		ft_putnbr((int)temp->next);
		ft_putchar('\n');
		temp = temp->next;
	}
}
