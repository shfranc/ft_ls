/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:30:51 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:46:25 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlen(t_list *list)
{
	t_list	*temp;
	int		len;

	len = 0;
	temp = list;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}
