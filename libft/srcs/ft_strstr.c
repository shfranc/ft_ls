/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:26:31 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:56:07 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	n;

	n = ft_strlen(little);
	if (n == 0)
		return ((char*)big);
	while (*big)
	{
		if (ft_strncmp(big, little, n) == 0)
			return ((char*)big);
		else
			big++;
	}
	return (NULL);
}
