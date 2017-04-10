/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 10:55:01 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:50:55 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	len;

	if (!s)
		return (NULL);
	start = 0;
	while (*(s + start) == ' ' || *(s + start) == '\t'
		|| *(s + start) == '\n')
		start++;
	len = ft_strlen(s);
	if (len != start)
	{
		while (*(s + len - 1) == ' ' || *(s + len - 1) == '\t'
			|| *(s + len - 1) == '\n')
			len--;
	}
	len = len - start;
	return (ft_strsub(s, (int)start, len));
}
