/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:03:17 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/29 19:40:25 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_nb_column(int colwidth)
{
	struct winsize	w;
	int				col;

	if ((ioctl(0, TIOCGWINSZ, &w)) == -1)
		ft_exit("Unable to fetch term width");
	col = w.ws_col / colwidth;
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
	char 	**tab;
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

void	print_column(char **tab_ref, char **tab, t_dim *dim, int i)
{
	int 	j;
	// int		k;
	char	*blank;

	(void)i;
	(void)tab_ref;

	blank = ft_strnew(dim->colwidth);
	ft_memset(blank, ' ', dim->colwidth);
	
	j = 0;
	while (j < dim->row)
	{
		k = 0;
		while (k < dim->col)
		{
			if ((j + k * dim->row) < dim->nb_file)
			{
				ft_putstr(tab[j + k * dim->row]);
				write(1, blank, dim->colwidth - ft_strlen(tab_ref[j + k * dim->row]));
			}
			++k;
		}
		write(1, "\n", 1);
		++j;
	}
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
	dim.colwidth = get_colwidth(files, i);
	dim.col = get_nb_column(dim.colwidth);
	dim.nb_file = file_list_len(files);

	dim.row = file_list_len(files) / dim.col;
	if (dim.row * dim.col < dim.nb_file)
		dim.row += 1;
	tab = create_tab_name(files, dim.nb_file, i);
	if (i == 2)
		tab_ref = create_tab_name(files, dim.nb_file, 1);
	else
		tab_ref = tab;
	print_column(tab_ref, tab, &dim, i);
}

// ===============================================================================

/*#include "ft_ls.h"

int		fetch_nb_column(t_file *files)
{
	struct winsize w;
	int	nb_col;
	int	max_len;
	int	tab;
	char	**temp;


	if ((ioctl(0, TIOCGWINSZ, &w)) == -1)
		ft_exit("Unable to fetch term width");
	// ft_putnbr_endl(w.ws_col);
	tab = 8;

	temp = (char**)files;
	ft_putendl(*(temp + 0));
	ft_putendl(*(temp + 1));
	ft_putendl(*(temp + 2));

	temp = (char**)files->next;
	ft_putendl(*(temp + 0));
	ft_putendl(*(temp + 1));
	ft_putendl(*(temp + 2));


	max_len = set_name_max(files);
	ft_putnbr_endl(max_len + tab);
	printbit(max_len + tab);
	write(1, "\n", 1);
	ft_putnbr_endl(~(tab - 1));
	printbit(~(tab - 1));
	write(1, "\n", 1);
	ft_putnbr_endl((max_len + tab) & ~(tab - 1));
	printbit((max_len + tab) & ~(tab - 1));
	write(1, "\n", 1);
	max_len = (max_len + tab) & ~(tab - 1);
	ft_putnbr_endl(max_len);

	nb_col = w.ws_col / max_len; // un critere si le max est plus grand que la largeur
	// nb_file = file_list_len(files);
	// ft_putnbr_endl(nb_file);

	// while (nb_col > 0)
	// {
	// 	if (nb_file % nb_col == 0 || nb_file % nb_col == nb_col - 1)
	// 		break ;
	// 	nb_col--;
	// }
	// on se prend un peu la tete la...
	return (nb_col);
}

int		set_name_max(t_file	*files)
{
	t_file	*temp;
	int 	max;

	temp = files;
	max = 0;
	
	while (temp)
	{
		temp->len.size = ft_strlen(temp->name);
		max < temp->len.size ? max = temp->len.size : 0;
		temp = temp->next;
	}
	return (max + 1);
}

int		get_max(char **tab)
{
	int	i;
	int	max;
	int	len;

	max = 0;
	i = 0;
	while (tab[i])
	{
		len = ft_strlen(tab[i++]);
		max < len ? max = len : 0;
	}
	return (max + 1);
}

char	**create_tab_name(t_file *files, int nb_file, t_opt *option)
{
	char 	**tab;
	t_file	*temp;
	int		i;

	if (!(tab = (char**)malloc(sizeof(char*) * (nb_file + 1))))
		ft_exit("Unable to malloc tab");
	tab[nb_file] = 0;
	temp = files;
	i = 0;
	while (temp)
	{
		if (option->u_g)
		{
			join_color(temp, temp->name);
			tab[i] = temp->color_name;
		}
		else
			tab[i] = temp->name;
		i++;
		temp = temp->next;
	}
	return (tab);
}


void	ft_print_column(char **tab, int col, int nb_file)
{
	char	*blank;
	int		max;
	int		row;
	int		i;
	int		j;
	int		tabwidth;

	tabwidth = 8;
	// max = set_name_max(files);
	max = get_max(tab);
	max = (max + tabwidth) & ~(tabwidth - 1);

	ft_putnbr_endl(col);
	// col = col - 1;
	// max = get_max(tab);
	// max += max /col;

	blank = ft_strnew(max);
	ft_memset(blank, ' ', max);
	row = nb_file / col;
	
	if (row * col < nb_file)
		row += 1;
	
	ft_putnbr_endl(row);

	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			if ((i + j * row) < nb_file)
			{
				// ft_putnbr_endl(i + j * row);
				ft_putstr(tab[i + j * row]);
				// ft_putchar(tab[i + j * row][0]);
				// ft_putchar(tab[i + j * row][1]);
				// ft_putchar(tab[i + j * row][2]);
				// ft_putchar(tab[i + j * row][3]);

				// ft_putnbr_endl(ft_strlen(tab[i + j * row]));
				// ft_putnbr_endl(strlen(tab[i + j * row]));
				write(1, blank, max - ft_strlen(tab[i + j * row]));
			}
			j++;
		}
		write(1, "\n", 1);
		// if ((i + j * row) != nb_file)
		// 	write(1, "\n", 1);
		i++;
	}
	free(blank);
}*/