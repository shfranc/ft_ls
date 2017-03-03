/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ull_toa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 12:09:39 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/03 12:15:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ull_toa(unsigned long long nb)
{
	int		len;
	char	*s;

	len = ull_len(nb);
	s = ft_strnew(len);
	if (nb == 0)
		*(s + len - 1) = '0';
	while (nb > 0 && len-- > 0)
	{
		*(s + len) = nb % 10 + '0';
		nb = nb / 10;
	}
	return (s);
}
