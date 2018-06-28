/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/14 04:52:44 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTREADLINE_H
# define LIBFTREADLINE_H

# include "libft.h"
# include "ftrl_data.h"

/*
** ft_readine -- Read a line from stdin
*/

char		*ft_readline(const char *prompt, t_rl_opts *opts, t_dlist *hist);

t_uint8		ftrl_quit(void);
t_uint8		ftrl_insert_msg(char *msg, int fd, t_uint8 free_msg);

void		ftrl_histadd(t_dlist **headref, char *line);
void		ftrl_histdelf(void *data, size_t size);
void		ftrl_histdellast(t_dlist **headref);

/*
** ft_confirm -- Ask for user confirmation (y/n)
*/

int			ft_confirm(const char *msg, int outfd, t_dflact dfl);

#endif
