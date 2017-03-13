/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:14:49 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/13 12:16:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_options(t_opt *option)
{
	option->u_r = 0;
	option->u_s = 0;
	option->a = 0;
	option->f = 0;
	option->l = 0;
	option->r = 0;
	option->t = 0;
	option->u = 0;
}

void	is_options(char *s, t_opt *option)
{
	s++;
	while (*s)
	{
		if (*s != 'R' && *s != 'S' && *s != 'a' && *s != 'f' && *s != 'l'
				&& *s != 'r' && *s != 't' && *s != 'u')
			display_illegal_option(*s);
		else if (check_priority(*s, option))
			save_option(*s, option);
		s++;
	}
}

int		check_priority(char c, t_opt *option)
{
	if (c == 'f')
		option->a = 'a';
	if ((c == 't' || c == 'u') && option->u_s)
		return (0);
	if (c == 'S' && (option->t || option->u))
	{
		option->t = 0;
		option->u = 0;
	}
	return (1);
}

void	save_option(char c, t_opt *option)
{
	c == 'R' ? option->u_r = 'R' : 0;
	c == 'S' ? option->u_s = 'S' : 0;
	c == 'a' ? option->a = 'a' : 0;
	c == 'f' ? option->f = 'f' : 0;
	c == 'l' ? option->l = 'l' : 0;
	c == 'r' ? option->r = 'r' : 0;
	c == 't' ? option->t = 't' : 0;
	c == 'u' ? option->u = 'u' : 0;
}

int		read_options(int ac, char ***av, t_opt *option)
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
			is_options(**av, option);
	}
	ac = set_current_dir(ac, av);
	return (ac);
}
