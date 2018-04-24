/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/24 12:54:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTREADLINE_H
# define LIBFTREADLINE_H

# include "libft.h"
# include "ftrl_data.h"

/*
** ft_readine -- Reading a line from stdin
*/

char	*ft_readline(const char *prompt, t_rl_opts *opts);

/*
** ft_confirm -- Ask for user confirmation (y/n)
*/

int		ft_confirm(const char *msg, int outfd, t_dflact dfl);

/*
** Generic functions
*/

char	*get_basedir(const char *f_path);
t_list	*search_files_begin(const char *f_path, const char *s_dir, int exec);
char	*get_last_component(const char *str, char c);
char	*get_name_from_path(const char *path);
char	*get_name_from_path_2(const char *path);

#endif
