/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 11:50:25 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/28 12:48:05 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_options(t_opt *options)
{
	options->u_r = 0;
	options->u_s = 0;
	options->a = 0;
	options->f = 0;
	options->l = 0;
	options->r = 0;
	options->t = 0;
	options->u = 0;
}

int		is_option(char *s, t_opt *options)
{
	s++;
	while (*s)
	{
		if (*s != 'R' && *s != 'S' && *s != 'a' && *s != 'f' && *s != 'l'
				&& *s != 'r' && *s != 't' && *s != 'u')
		{
			display_illegal_option(*s);
			return (0);
		}
		else
			if (check_priority(*s, options))
				save_option(*s, options);
		s++;
	}
	return (1);
}

int		check_priority(char c, t_opt *options)
{
	if (c == 'f')
		options->a = 'a';
	if ((c == 't' || c == 'u') && options->u_s)
		return (0);
	if (c == 'S' && (options->t || options->u))
	{
		options->t = 0;
		options->u = 0;
	}
	return (1);
}

void	save_option(char c, t_opt *options)
{
	c == 'R' ? options->u_r = 'R' : 0;
	c == 'S' ? options->u_s = 'S' : 0;
	c == 'a' ? options->a = 'a' : 0;
	c == 'f' ? options->f = 'f' : 0;
	c == 'l' ? options->l = 'l' : 0;
	c == 'r' ? options->r = 'r' : 0;
	c == 't' ? options->t = 't' : 0;
	c == 'u' ? options->u = 'u' : 0;
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

int		set_current_dir(int ac, char ***av) // a basculer dans parsing_names.c ?
{
	if (ac == 0)
	{
		ac++;
		**av = ".";
	}
	return (ac);
}
