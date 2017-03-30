/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:35:01 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/30 15:38:02 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew_set(size_t size, char c)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	*(str + size) = 0;
	ft_memset(str, c, size);
	return (str);
}
