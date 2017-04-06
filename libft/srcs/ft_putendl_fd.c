/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 12:28:39 by sfranc            #+#    #+#             */
/*   Updated: 2016/12/06 16:46:46 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putendl_fd(char const *str, int fd)
{
	if (str && fd != -1)
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}
