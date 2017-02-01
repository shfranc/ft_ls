/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 11:50:25 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/01 11:05:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_options(t_opt *options)
{
	options->u_r = 0;
	options->a = 0;
	options->f = 0;
	options->l = 0;
	options->r = 0;
	options->t = 0;
}

int		is_option(char *s, t_opt *options)
{
	s++;
	while (*s)
	{
		if (*s != 'R' && *s != 'a' && *s != 'f' && *s != 'l' && *s != 'r'
				&& *s != 't')
		{
			display_illegal_option(*s);
			return (0);
		}
		else
			save_option(*s, options);
		s++;
	}
	return (1);
}

void	save_option(char c, t_opt *options)
{
	c == 'R' ? options->u_r = 'R' : 0;
	c == 'a' ? options->a = 'a' : 0;
	c == 'f' ? options->f = 'f' : 0;
	c == 'l' ? options->l = 'l' : 0;
	c == 'r' ? options->r = 'r' : 0;
	c == 't' ? options->t = 't' : 0;
}

int		read_options(int ac, char ***av, t_opt *options)
{
	while (--ac)
	{
		++*av;
		if (ft_strequ(**av, "-"))
			break ;
		if (ft_strequ(**av, "--"))
		{
			++*av;
			--ac;
			break ;
		}
		if (***av != '-')
			break ;
		else
		{
			if (!(is_option(**av, options)))
				return (-1);
		}
	}
	ac = set_current_dir(ac, av);
	return (ac);
}

int		set_current_dir(int ac, char ***av)
{
	if (ac == 0)
	{
		ac++;
		**av = ".";
	}
	return (ac);
}
