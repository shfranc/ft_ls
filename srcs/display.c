/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:54:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/27 12:54:18 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_options(t_opt *options)
{
	ft_putstr("options : ");
	ft_putchar(options->R);
	ft_putchar(options->a);
	ft_putchar(options->l);
	ft_putchar(options->r);
	ft_putchar(options->t);
	if (options->R || options->a || options->l || options->r || options->t)
		ft_putchar('\n');
}

void	display_illegal_option(char c)
{
	ft_putstr(ILLEGAL);
	ft_putchar(c);
	ft_putendl(USAGE);
}
