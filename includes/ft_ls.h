/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:38:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/03 13:07:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <errno.h> /* errno */
# include <sys/stat.h> /* stat + struct stat */
# include <stdio.h> /* strerror */
# include <dirent.h> /* opendir + DIR, readdir + struct dirent */
# include <sys/types.h> /* getpwuid */
# include <pwd.h> /* getpwuid */
# include <grp.h> /* getgrgid */
# include <uuid/uuid.h> /* getpwuid & getgrgid */
# include <time.h> /* ctime */

# define OPTIONS	"RSaflrtu"
# define USAGE		"\nusage: ft_ls [-"OPTIONS"] [file ...]"
# define ILLEGAL	"ft_ls: illegal option -- "
# define LS			"ft_ls: "

typedef struct	s_len
{
	int				nblink;
	int				user;
	int				group;
	int				size;
}				t_len;

typedef struct	s_max
{
	int				nblink;
	int				user;
	int				group;
	int				size;
	int				total;
}				t_max;

typedef struct	s_file
{
	char			*name;
	char			*long_format;
	int				error;
	struct stat		lstat;
	struct stat		stat;
	struct passwd	*usr;
	struct group	*grp;
	t_len			len;
	t_max			max;
	struct s_file	*inside;
	struct s_file	*next;
}				t_file;

/*
** R	recursive search into folder
** a	hidden files
** l	long format
** r	reverse any sorting (except no sorting)
** t	sort by modification time
** -- BONUS --
** S	sort by size, bigger to smaller
** u	sort by last access time with -t and -l, no effect otherwise
** f	no acsii sorting + option 'a' active
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

typedef void	(*t_comp)(t_file **temp, t_file **left, t_file **right);

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
t_file			*file_new(char *name, t_opt *options);
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
void			display_inside(t_file *files, t_opt *options);
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
void			sort_last_access(t_file **temp, t_file **left, t_file **right);

/*
** reverse_sorting.c
*/
void			reverse_sort_ascii(t_file **temp, t_file **left, t_file **right);
void			reverse_sort_time_modified(t_file **temp, t_file **left, t_file **right);
void			reverse_sort_last_access(t_file **temp, t_file **left, t_file **right);
void			reverse_sort_size(t_file **temp, t_file **left, t_file **right);

/*
** long_format.c 
*/
void			fill_llong_struct(t_file *elem);
int				set_max_len(t_file *files);
void			fill_long_format(t_file *files, t_opt *options);
char			*get_long_format(t_file *file, int max_len, t_opt *options);

/*
** long_format_details_part1.c
*/
void			get_type(char **long_format, t_file *file);
void			get_perms(char **long_format, t_file *file);
void			get_nblink(char **long_format, t_file *file);
void			get_user_owner(char **long_format, t_file *file);

/*
** long_format_details_part2.c
*/
void			get_size(char **long_format, t_file *file);
void			get_timestamp(char **long_format, t_file *file, t_opt *options);
void			get_name(char **long_format, t_file *file);

/*
** long_display.c
*/
int				long_display_non_dir(t_file *files);
void			long_display_dir(int nb_file, int ac, t_file *files, t_opt *options);
void			long_display_inside(t_file *files, t_opt *options);
void			long_display(int ac, t_file *files, t_opt *options);
#endif
