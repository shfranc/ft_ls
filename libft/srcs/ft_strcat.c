/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:48:56 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:46:57 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char *temp;

	temp = s1;
	while (*temp)
		temp++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	return (s1);
}
