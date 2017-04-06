/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 11:48:25 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/23 11:49:06 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char *new;

	new = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	new = ft_strcat(ft_strcat(ft_strcpy(new, s1), s2), s3);
	return (new);
}
