/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 18:18:54 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:46:35 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itoa(int n)
{
	int			size;
	char		*s;
	long int	nb;

	size = ft_intsize(n);
	if (!(s = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	*(s + size) = '\0';
	nb = (long int)n;
	if (nb == 0)
		*s = '0';
	if (nb < 0)
	{
		*s = '-';
		nb = -nb;
	}
	while (nb != 0 && size-- > 0)
	{
		*(s + size) = nb % 10 + 48;
		nb = nb / 10;
	}
	return (s);
}
