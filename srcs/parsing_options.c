/* *****************9********************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 11:50:25 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/30 17:26:03 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_options(t_opt *options)
{
	options->u_r = 0;
	options->a = 0;
	options->l = 0;
	options->r = 0;
	options->t = 0;
}

int		is_option(char *s, t_opt *options)
{
	s++;
	while (*s)
	{
		if (*s != 'R' && *s != 'a' && *s != 'l' && *s != 'r' && *s != 't')
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
	if (c == 'R')
		options->u_r = c;
	if (c == 'a')
		options->a = c;
	if (c == 'l')
		options->l = c;
	if (c == 'r')
		options->r = c;
	if (c == 't')
		options->t = c;
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
	if (ac == 0)
	{
		ac++;
		**av = ".";
	}
	return (ac);
}

int		arg_vide(int ac, char **av)
{
	struct stat	av_stat;

	while (--ac)
	{
		++av;
		if ((ft_strequ(*av, "")))
		{
			stat("", &av_stat);
			ft_putstr(LS);
			ft_putstr(""":");
			perror(*av);
			return (0);
		}
	}
	return (1);
}
