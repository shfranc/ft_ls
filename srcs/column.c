/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:03:17 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/11 14:03:51 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		get_colwidth(t_file *files, int i)
{
	int				colwidth;
	int				tab;
	int				len;
	t_file			*temp;

	colwidth = 0;
	temp = files;
	while (temp)
	{
		if (i == 2)
			join_color(temp, temp->name);
		len = ft_strlen(temp->name);
		colwidth < len ? colwidth = len : 0;
		temp = temp->next;
	}
	if (i != 2)
		tab = 8;
	else
		tab = 1;
	colwidth = (colwidth + tab) & ~(tab - 1);
	return (colwidth);
}

char	**create_tab_name(t_file *files, int nb_file, int i)
{
	char	**tab;
	t_file	*temp;
	char	**disp;
	int		j;

	if (!(tab = (char**)malloc(sizeof(char*) * (nb_file + 1))))
		ft_exit("Unable to malloc tab");
	tab[nb_file] = 0;
	temp = files;
	j = 0;
	while (temp)
	{
		disp = (char**)temp;
		tab[j] = *(disp + i);
		temp = temp->next;
		j++;
	}
	return (tab);
}

void	print_column(char **tab_ref, char **tab, t_dim *dim)
{
	int		j;
	int		k;
	char	*blank;

	if (!(blank = ft_strnew_set(dim->colwidth, ' ')))
		ft_exit("Unable to malloc blank");
	j = -1;
	while (++j < dim->row)
	{
		k = -1;
		while (++k < dim->col)
		{
			if ((j + k * dim->row) < dim->nb_file)
			{
				ft_putstr(tab[j + k * dim->row]);
				write(1, blank, dim->colwidth
					- ft_strlen(tab_ref[j + k * dim->row]));
			}
		}
		write(1, "\n", 1);
	}
	free(tab);
	free(tab_ref);
	free(blank);
}

int		display_column(t_file *files, t_opt *option)
{
	int				i;
	t_dim			dim;
	char			**tab;
	char			**tab_ref;
	struct winsize	w;

	if (option->c1 || file_list_len(files) <= 1
		|| (ioctl(1, TIOCGWINSZ, &w)) == -1 || read_only(files))
		return (1);
	i = 1;
	if (option->u_g)
		i = 2;
	dim.nb_file = file_list_len(files);
	dim.colwidth = get_colwidth(files, i);
	if (dim.colwidth && dim.colwidth < w.ws_col)
		dim.col = w.ws_col / dim.colwidth;
	else
		dim.col = 1;
	dim.row = file_list_len(files) / dim.col;
	if (dim.row * dim.col < dim.nb_file)
		dim.row += 1;
	tab = create_tab_name(files, dim.nb_file, i);
	tab_ref = create_tab_name(files, dim.nb_file, 1);
	print_column(tab_ref, tab, &dim);
	return (0);
}
