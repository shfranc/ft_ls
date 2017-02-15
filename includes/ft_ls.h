/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:38:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/15 18:47:24 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <errno.h> /*errno */
# include <sys/stat.h> /* stat + struct stat */
# include <stdio.h> /* strerror */
# include <dirent.h> /* opendir + DIR, readdir + struct dirent */

# define OPTIONS	"Raflrt"
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
}				t_file;

/*
** R	recursive
** S	sort by size
** a	hidden files
** f	no acsii sorting + option 'a' active
** l	long format
** r	reverse sorting
** t	sort by modification time
** u	sort by last access time
*/

typedef struct	s_options
{
	char	u_r;
	char	u_s;
	char	a;
	char	f;
	char	l;
	char	r;
	char	t;
	char	u;
}				t_opt;

/*
** parsing_options.c
*/
void			init_options(t_opt *options);
int				is_options(char *s, t_opt *options);
void			save_option(char c, t_opt *options);
int				check_priority(char c, t_opt *options);
int				read_options(int ac, char ***av, t_opt *options);
int				set_current_dir(int ac, char ***av);

/*
** parsing_names.c
*/
t_file			*file_new(char *name);
void			file_add(t_file **begin, t_file *new); /* a supprimer eventuellement */
void			file_add_last(t_file **begin, t_file *new);
void			walk_dir(char *av_dir, t_file **names, t_opt *options);
void			read_names(int ac, char **av, t_file **names, t_opt *options);

/*
** display_errors.c
*/
void			display_options(t_opt *options); /* pour debug */
void			display_illegal_option(char c);
void			display_file_error(t_file *file);
void			display_errors(t_file *names);

/*
** classic_display.c
*/
int				display_non_dir(t_file *files);
void			display_dir(int nb_file, int ac, t_file *files, t_opt *options);
void			display_inside(t_file *files);
void			classic_display(int ac, t_file *files, t_opt *options);

/*
** options_upper_r.c 
*/
void			readndisplay_inside(t_file *files_inside, t_opt *options);

/*
** merge_sorting.c
*/
t_file			*which_sort(t_file *files, t_opt *options);
t_file			*merge_sort(t_file *files, void (*f)(t_file**, t_file**, t_file**));
t_file			*merge(t_file *left, t_file *right, void (*f)(t_file**, t_file**, t_file**));
int				file_list_len(t_file *files);

/*
** sorting.c
*/
void			sort_ascii(t_file **temp, t_file **left, t_file **right);
void			sort_time_modified(t_file **temp, t_file **left, t_file **right);
void			sort_size(t_file **temp, t_file **left, t_file **right);
//void			sort_time_last_access(t_file **temp, t_file **left, t_file **right);

#endif
