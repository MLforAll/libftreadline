/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/29 02:10:58 by kdumarai         ###   ########.fr       */
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

void		ftrl_histadd(t_dlist **headref, char *line);
void		ftrl_histdelf(void *data, size_t size);
void		ftrl_histdellast(t_dlist **headref);

t_list		*get_ac_result_bltn(char *line, t_cursor *csr);
char		*show_ac_result_bltn(t_list **res);
void		ft_acres_free(void *content, size_t size);
int			ft_acres_sortalpha(t_list *a, t_list *b);

/*
** ft_confirm -- Ask for user confirmation (y/n)
*/

int			ft_confirm(const char *msg, int outfd, t_dflact dfl);

#endif
