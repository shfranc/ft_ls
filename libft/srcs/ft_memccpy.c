/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:18:56 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:46:17 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *temp_dst;

	temp_dst = (unsigned char*)dst;
	while (n-- > 0)
	{
		*temp_dst = *(unsigned char*)src;
		dst++;
		if (*(unsigned char*)src == (unsigned char)c)
			return (dst);
		temp_dst++;
		src++;
	}
	return (NULL);
}
