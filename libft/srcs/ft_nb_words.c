/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 14:47:36 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:46:07 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_nb_words(char const *s, char c)
{
	int	nb_words;

	nb_words = 0;
	while (*s)
	{
		if (*s != c)
		{
			nb_words++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (nb_words);
}
