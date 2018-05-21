/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/21 20:37:30 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTREADLINE_H
# define LIBFTREADLINE_H

# include "libft.h"
# include "ftrl_data.h"

/*
** ft_readine -- Read a line from stdin
*/

char		*ft_readline(const char *prompt, t_rl_opts *opts, t_rl_hist *hist);
t_rl_hist	*ft_histnew(char *line);
void		ft_histadd(t_rl_hist **headref, char *line);
void		ft_histdelone(t_rl_hist	**hist);
void		ft_histdel(t_rl_hist **headref);

/*
** ft_confirm -- Ask for user confirmation (y/n)
*/

int			ft_confirm(const char *msg, int outfd, t_dflact dfl);

/*
** List utilities (Autocompletion extensions)
*/

void		free_tlist(void *content, size_t size);
int			ft_lstsortalpha(t_list *a, t_list *b);

#endif
