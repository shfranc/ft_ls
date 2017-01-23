/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:38:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/23 19:18:41 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"
#include <errno.h> /*errno */
#include <sys/stat.h> /* stat + struct stat */
#include <stdio.h> /* strerror */

int		parsing(int ac, char **av, t_list **names, char *options);
void	read_names(int ac, char **av, t_list **names);

void	display_names(t_list *names);
void	set_errors(char **errors, char *message, char *file, int nb_err);
void	put_errors(char **errors, int nb_err);

#endif
