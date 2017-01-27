/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:38:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/27 18:58:20 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <errno.h> /*errno */
# include <sys/stat.h> /* stat + struct stat */
# include <stdio.h> /* strerror */
# include <dirent.h> /* opendir + DIR, readdir + struct dirent */

# define OPTIONS	"Ralrt"
# define USAGE		"\nusage: ft_ls [-"OPTIONS"] [file ...]"
# define ILLEGAL	"ft_ls: illegal option -- "
# define ARG_VIDE	"ft_ls: fts_open: No such file or directory"	
typedef struct	s_file
{
	char			*name;
	char			*path;
	int				error;
	struct stat		lstat;
//	struct stat		stat;
	struct s_file	*inside;
	struct s_file	*next;
} 				t_file;

typedef struct s_options
{
	char	u_r;
	char	a;
	char	l;
	char	r;
	char	t;
}				t_opt;

/*
** parsing_options.c
*/
void	init_options(t_opt *options);
int		is_options(char *s, t_opt *options);
void	save_option(char c, t_opt *options);
int		read_options(int ac, char ***av, t_opt *options);
int		arg_vide(int ac, char **av);

/*
** display.c
*/
void	display_options(t_opt *options);
void	display_illegal_option(char c);
#endif
