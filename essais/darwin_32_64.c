/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darwin_32_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 15:51:51 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/16 15:55:23 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		main(void)
{
	if (_DARWIN_FEATURE_64_BIT_INODE)
		printf("64bits\n");
	else
		printf("32bits\n");
	return (0);
}