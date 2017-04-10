/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:18:32 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:46:14 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *temp_dst;
	char *temp_src;

	temp_dst = (char*)dst;
	temp_src = (char*)src;
	while (n-- > 0)
	{
		*temp_dst++ = *temp_src++;
	}
	return (dst);
}
