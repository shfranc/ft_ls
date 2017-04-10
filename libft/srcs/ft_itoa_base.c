/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:45:33 by exam              #+#    #+#             */
/*   Updated: 2017/01/11 16:38:19 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		value_size(int value, int base)
{
	int	size;

	size = 0;
	if (value == 0)
		++size;
	if (value < 0 && base == 10)
		++size;
	while (value != 0)
	{
		++size;
		value /= base;
	}
	return (size);
}

char			*ft_itoa_base(int value, int base)
{
	int			size;
	long int	value_long;
	char		*result;
	char		*tab_base;

	if (base <= 1 || base >= 17)
		return (NULL);
	tab_base = ft_strdup("0123456789ABCDEF");
	size = value_size(value, base);
	if (!(result = ft_strnew(size)))
		return (NULL);
	result[0] = '0';
	if (value < 0 && base == 10)
		result[0] = '-';
	value_long = (long)value;
	if (value < 0)
		value_long *= -1;
	while (size--)
	{
		result[size] = tab_base[value_long % base];
		value_long /= base;
	}
	return (result);
}
