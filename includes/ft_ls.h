/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:38:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/31 18:07:12 by sfranc           ###   ########.fr       */
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
# define LS			"ft_ls: "

typedef struct	s_file
{
	char			*name;
	int				error;
	struct stat		lstat;
	struct stat		stat;
	struct s_file	*inside;
	struct s_file	*next;
} 				t_file;

/*
** R	recursive
** a	hidden files
** f	no acsii sorting
** l	long format
** r	reverse sorting
** t	sort by modification time
*/

typedef struct s_options
{
	char	u_r;
	char	a;
	char	f;
	char	l;
	char	r;
	char	t;
}				t_opt;

/*
** parsing_options.c
*/
void			init_options(t_opt *options);
int				is_options(char *s, t_opt *options);
void			save_option(char c, t_opt *options);
int				read_options(int ac, char ***av, t_opt *options);
int				arg_vide(int ac, char **av);

/*
** parsing_names.c
*/
t_file			*file_new(char *name);
void			file_add(t_file **begin, t_file *new);
void			file_add_last(t_file **begin, t_file *new);
void			walk_dir(char *av_dir, t_file **names);
void			read_names(int ac, char **av, t_file **names);

/*
** display.c
*/
void			display_options(t_opt *options); /* pour debug */
void			display_illegal_option(char c);
void			display_file_error(t_file *file);
void			display_errors(t_file *names);
void			display_names(int ac, t_file *files);
void			display_dirnondir(int ac, t_file *files);

#endif
