/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:38:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/11 16:26:08 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include "color.h"
# include <errno.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>

# define OPTIONS	"GRSUaflrtu1"
# define USAGE		"\nusage: ft_ls [-"OPTIONS"] [file ...]"
# define ILLEGAL	"ft_ls: illegal option -- "
# define LS			"ft_ls: "

# define FT_MAJ(x) (int)(((unsigned int)(x) >> 24) & 0x000000ff)
# define FT_MIN(x) (int)((unsigned int)(x) & 0x00ffffff)

typedef struct	s_len
{
	int				nblink;
	int				user;
	int				group;
	int				size;
	int				maj;
	int				min;
	int				total;
}				t_len;

typedef struct	s_max
{
	int				nblink;
	int				user;
	int				group;
	int				size;
	int				maj;
	int				min;
}				t_max;

typedef struct	s_file
{
	char			*path;
	char			*name;
	char			*color_name;
	char			*long_format;
	int				error;
	int				error_stat;
	struct stat		lstat;
	struct stat		stat;
	struct passwd	*usr;
	struct group	*grp;
	t_len			len;
	struct s_file	*inside;
	struct s_file	*next;
}				t_file;

typedef struct	s_dim
{
	int				colwidth;
	int				col;
	int				row;
	int				nb_file;
}				t_dim;

/*
** R	recursive search into folder
** a	hidden files
** l	long format
** r	reverse any sorting (except no sorting)
** t	sort by modification time
** -- BONUS --
** G	bonus color, 11 special colors, same as LS
** S	sort by size, bigger to smaller
** U	sort by birth time with -t and -l, no effect otherwise
** u	sort by last access time with -t and -l, no effect otherwise
** f	no acsii sorting + option 'a' active
** 1	display in a single column
*/

typedef struct	s_options
{
	char	u_g;
	char	u_r;
	char	u_s;
	char	u_u;
	char	a;
	char	f;
	char	l;
	char	r;
	char	t;
	char	u;
	char	c1;
}				t_opt;

typedef void	(*t_comp)(t_file **temp, t_file **left, t_file **right);

/*
** parsing_options.c
*/
void			init_options(t_opt *option);
void			is_options(char *s, t_opt *option);
void			save_option(char c, t_opt *option);
int				check_priority(char c, t_opt *option);
int				read_options(int ac, char ***av, t_opt *option);

/*
** parsing_names.c
*/
t_file			*file_new(char *name, t_opt *option);
void			file_add_last(t_file **begin, t_file *new);
void			walk_dir(char *av_dir, t_file **files, t_opt *option);
void			read_names(int ac, char **av, t_file **names, t_opt *option);

/*
** parsing_misc.c
*/
void			check_arg_vide(int ac, char **av);
int				set_current_dir(int ac, char ***av);
void			file_init(t_file *elem);
char			*create_path(char *s1, char *s2, char *s3);
void			get_len(t_file *elem);

/*
** display_errors.c
*/
void			ft_exit(char *s);
void			display_illegal_option(char c);
void			display_file_error(t_file *file);
int				display_errors(t_file *files);
int				read_only(t_file *files);

/*
** classic_display.c
*/
int				display_non_dir(t_file *files, t_opt *option);
void			display_dir(int nb_file, int ac, t_file *files, t_opt *option);
void			display_inside(t_file *files, t_opt *option);
void			classic_display(int ac, t_file *files, t_opt *option);

/*
** recursive_search.c
*/
void			readndisplay_inside(t_file *files_inside, t_opt *option);
int				go_recursive(t_file *file);
void			recursive_display(t_file *files, t_opt *option);
int				not_searchable(t_file *files, t_opt *option);
int				not_sortable(t_file *files, t_opt *option);

/*
** merge_sorting.c
*/
t_file			*which_sort(t_file *files, t_opt *option);
t_file			*merge_sort(t_file *files, void (*f)(t_file**,
				t_file**, t_file**));
t_file			*merge(t_file *left, t_file *right, void (*f)(t_file**,
				t_file**, t_file**));
int				file_list_len(t_file *files);
void			pick_last_elem(t_file **temp, t_file **side);

/*
** sorting.c
*/
void			sort_ascii(t_file **temp, t_file **left, t_file **right);
void			sort_time_modified(t_file **temp, t_file **left,
				t_file **right);
void			sort_size(t_file **temp, t_file **left, t_file **right);
void			sort_last_access(t_file **temp, t_file **left,
				t_file **right);
void			sort_birth_time(t_file **temp, t_file **left, t_file **right);

/*
** reverse_sorting.c
*/
void			reverse_sort_ascii(t_file **temp, t_file **left,
				t_file **right);
void			reverse_sort_time_modified(t_file **temp, t_file **left,
				t_file **right);
void			reverse_sort_last_access(t_file **temp, t_file **left,
				t_file **right);
void			reverse_sort_size(t_file **temp, t_file **left, t_file **right);
void			reverse_sort_birth_time(t_file **temp, t_file **left,
				t_file **right);

/*
** long_format.c
*/
void			get_usr_group_struct(t_file *elem);
void			init_max(t_max *max);
void			set_max_len(t_file *files, t_max *max);
void			fill_long_format(t_file *files, t_opt *option);
char			*get_long_format(t_file *file, t_max *max, t_opt *option);

/*
** long_format_details_part1.c
*/
void			get_type(char *long_format, t_file *file);
void			get_perms(char *long_format, t_file *file);
void			get_attr_acl(char *long_format, t_file *file);
void			get_nblink(char *long_format, t_file *file, t_max *max);
void			get_user_owner(char *long_format, t_file *file, t_max *max);

/*
** long_format_details_part2.c
*/
void			get_size(char *long_format, t_file *file, t_max *max);
void			get_maj_min(char *long_format, t_file *file, t_max *max);
void			get_timestamp(char *long_format, t_file *file,
				t_opt *options, t_max *max);
void			get_name(char *long_format, t_file *file, t_max *max);
void			display_totalblocks(t_file *file);

/*
** long_display.c
*/
int				long_display_non_dir(t_file *files, t_opt *option);
void			long_display_dir(int nb_file, int ac, t_file *files,
				t_opt *option);
void			long_display_inside(t_file *files, t_opt *option);
void			long_display(int ac, t_file *files, t_opt *option);
void			long_display_path(t_file *temp, t_opt *option);

/*
** display_colors.c
*/
char			*which_color(t_file *file);
char			*type_color(t_file *file);
void			join_color(t_file *file, char *s);
void			ft_putendl2(char *s1, char *s2);

/*
** column.c
*/
int				get_colwidth(t_file *files, int i);
char			**create_tab_name(t_file *files, int nb_file, int i);
void			print_column(char **tab_ref, char **tab, t_dim *dim);
int				display_column(t_file *files, t_opt *option);

/*
** column_part2.c
*/
int				display_non_dir_column(t_file *files, t_opt *option);
t_file			*copy_file(char *path);

/*
** free.c
*/
void			free_file(t_file **files);
void			del_file(t_file *file);

#endif
