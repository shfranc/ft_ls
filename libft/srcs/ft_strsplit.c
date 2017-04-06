/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 11:24:34 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:56:09 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_words_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		n;
	int		i;

	if (!s)
		return (NULL);
	n = ft_nb_words(s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	i = 0;
	*(tab + n) = 0;
	while (i < n)
	{
		while (*s && *s == c)
			s++;
		*tab++ = ft_strsub(s, 0, ft_words_len(s, c));
		while (*s && *s != c)
			s++;
		i++;
	}
	return (tab - n);
}
