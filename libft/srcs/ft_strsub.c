/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 09:53:07 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/13 16:44:48 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	i;

	if (s)
	{
		if (!(new_s = ft_strnew(len)))
			return (NULL);
		i = 0;
		while (i < len)
			*(new_s + i++) = *(s + start++);
		*(new_s + i) = '\0';
		return (new_s);
	}
	else
		return (NULL);
}
