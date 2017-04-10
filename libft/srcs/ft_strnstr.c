/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:44:26 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:56:12 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;
	size_t	i;

	n = ft_strlen(little);
	if (*little == 0)
		return ((char*)big);
	if (*big == 0)
		return (NULL);
	i = n;
	while (*big && i <= len)
	{
		if (ft_strncmp(big, little, n) == 0)
			return ((char*)big);
		else
		{
			big++;
			i++;
		}
	}
	return (NULL);
}
