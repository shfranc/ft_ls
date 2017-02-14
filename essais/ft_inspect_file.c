/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 15:22:18 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/14 12:07:55 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** Un programme qui prend un fichier en parametre et affiche ses informations.
 */

#include "libft.h"
#include <sys/stat.h> /* stat */
#include <stdio.h> /* printf */
#include <time.h> /* ctime */
#include <pwd.h> /* getpwuid, type struct passwd */
#include <grp.h> /*getgrid, type struct group */

void	print_type(mode_t st_mode)
{
	unsigned short	mask;
	static unsigned short type[7] = {S_IFIFO, S_IFCHR, S_IFDIR, S_IFBLK, S_IFREG, S_IFLNK, S_IFSOCK};
	static char *type2[30] = {"Pipe", "Peripherique caratere", "Dossier", "Peripherique block", "Fichier", "Lien symbolique", "Socket"};
	int	i;

	mask = st_mode & S_IFMT;
//	printf("st_mode fichier %o\n", st_mode);
//	printf("& mask global %o\n", S_IFMT);
//	printf("= %o\n", mask);
//	printf("^ S_IFREG %o\n", mask ^ S_IFREG);
	i = 0;
	while (i < 7)
	{
		if (((st_mode & S_IFMT) ^ type[i]) == 0)
			printf("%s\n", type2[i]);
		i++;
	}
}

void	get_permissions(mode_t st_mode)
{
	char	*perm;

	perm = ft_strnew(9);
	ft_memset(perm, '-', 9);
//	if ((st_mode & S_IRUSR) == S_IRUSR)
	if (((st_mode & S_IRUSR) ^ S_IRUSR) == 0)
		perm[0] = 'r';
	if ((st_mode & S_IWUSR) == S_IWUSR)
		perm[1] = 'w';
	if ((st_mode & S_IXUSR) == S_IXUSR)
		perm[2] = 'x';
	if ((st_mode & S_IRGRP) == S_IRGRP)
		perm[3] = 'r';
	if ((st_mode & S_IWGRP) == S_IWGRP)
		perm[4] = 'w';
	if ((st_mode & S_IXGRP) == S_IXGRP)
		perm[5] = 'x';
	if ((st_mode & S_IROTH) == S_IROTH)
		perm[6] = 'r';
	if ((st_mode & S_IWOTH) == S_IWOTH)
		perm[7] = 'w';
	if ((st_mode & S_IXOTH) == S_IXOTH)
		perm[8] = 'x';
	ft_putendl(perm);
}

int		main(int ac, char **av)
{
	struct stat		*stat_file;
	int				ret_stat;
	char			*date_full;
	char			*date_short;
	struct passwd	*uid;
	struct group	*group;

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
	get_permissions(stat_file->st_mode);

	ft_putstr("Nombre de liens: ");
	ft_putnbr_endl(stat_file->st_nlink);

	if(!(uid = (struct passwd*)malloc(sizeof(struct passwd))))
		return (0);
	uid = getpwuid(stat_file->st_uid);
	ft_putstr("Propietaire: ");
	ft_putendl(uid->pw_name);
	
	if(!(group = (struct group*)malloc(sizeof(struct group))))
		return (0);
	group = getgrgid(stat_file->st_gid);
	ft_putstr("Groupe: ");
	ft_putendl(group->gr_name);
	
	ft_putstr("Taille: ");
	ft_putnbr(stat_file->st_size);
	ft_putendl(" octects");
	
	ft_putstr("Date de derniere modification: ");
	date_full = ctime(&stat_file->st_mtimespec.tv_sec);
	date_short = ft_strjoin(ft_strsub(date_full, 4, 12), "\n");
	printf("%s", date_short);
	return (0);
}

