/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 15:22:18 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/16 20:10:13 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** Un programme qui prend un fichier en parametre et affiche ses informations.
 */

#include "libft.h"
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>

void	print_type(mode_t st_mode)
{
	unsigned short	mask;
	static unsigned short type[7] = {S_IFIFO, S_IFCHR, S_IFDIR, S_IFBLK, S_IFREG, S_IFLNK, S_IFSOCK};
	static char *type2[30] = {"Pipe", "Peripherique caratere", "Dossier", "Peripherique block", "Fichier", "Lien symbolique", "Socket"};
	int	i;

	mask = st_mode & S_IFMT;
	printf("st_mode fichier %o\n", st_mode);
	printf("& mask global %o\n", S_IFMT);
	printf("= %o\n", mask);
	printf("^ S_IFREG %o\n", mask ^ S_IFREG);
	i = 0;
	while (i < 7)
	{
		if (((st_mode & S_IFMT) ^ type[i]) == 0)
			printf("%s\n", type2[i]);
		i++;
	}
}

int		main(int ac, char **av)
{
	//	DIR				*dir_ptr;
	//	struct dirent	*dir;
	struct stat		*stat_file;
	int				ret_stat;

	(void)ac;
	if(!(stat_file = (struct stat*)malloc(sizeof(struct stat))))
		return (0);
	if ((ret_stat = stat(av[1], stat_file) == -1))
		return (0);
	ft_putstr("Nom: ");
	ft_putendl(av[1]);

	ft_putstr("Type: ");
	print_type(stat_file->st_mode);
	ft_putstr("Modes: ");
	ft_putstr("Nombre de liens: ");
	ft_putstr("Propietaire: ");
	ft_putstr("Groupe: ");
	ft_putstr("Taille: ");
	ft_putnbr_endl(stat_file->st_size);
	ft_putstr("Date de derniere modification: ");
	printf("%lu\n",stat_file->st_mtimespec.tv_sec);
	return (0);
}

