/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:03:17 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/05 19:06:02 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_nb_column(int colwidth)
{
	struct winsize	w;
	int				col;

	if ((ioctl(0, TIOCGWINSZ, &w)) == -1)
		ft_exit("Unable to fetch term width");
	if (colwidth && colwidth < w.ws_col)
		col = w.ws_col / colwidth;
	else
		col = 1;
	return (col);
}

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

void	display_column(t_file *files, t_opt *option)
{
	int		i;
	t_dim	dim;
	char	**tab;
	char	**tab_ref;

	i = 1;
	if (option->u_g)
		i = 2;
	dim.nb_file = file_list_len(files);
	// ft_putstr("nb_file : ");
	// ft_putnbr_endl(dim.nb_file);

	dim.colwidth = get_colwidth(files, i);
	// ft_putstr("colwidth : ");
	// ft_putnbr_endl(dim.colwidth);

	dim.col = get_nb_column(dim.colwidth);
	// ft_putstr("col : ");
	// ft_putnbr_endl(dim.col);

	dim.row = file_list_len(files) / dim.col;


	if (dim.row * dim.col < dim.nb_file)
		dim.row += 1;
	// ft_putstr("row : ");
	// ft_putnbr_endl(dim.row);

	tab = create_tab_name(files, dim.nb_file, i);
	tab_ref = create_tab_name(files, dim.nb_file, 1);
	print_column(tab_ref, tab, &dim);
}
