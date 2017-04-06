/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 10:36:41 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/13 17:50:11 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_new;
	size_t	i;

	if (s1 && s2)
	{
		if (!(s_new = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
			return (NULL);
		i = 0;
		while (*s1)
			*(s_new + i++) = *s1++;
		while (*s2)
			*(s_new + i++) = *s2++;
		*(s_new + i) = '\0';
		return (s_new);
	}
	else
		return (NULL);
}
