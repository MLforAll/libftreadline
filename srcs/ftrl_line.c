/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/20 18:19:57 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

inline static void	clr_lines(t_point *coords, t_readline *rl)
{
	t_point	maxc;

	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	outcap("ce");
	if (coords->y >= maxc.y)
		return ;
	outcapstr(rl->movs.downm);
	outcap_arg_fb(tgetstr("DL", NULL), tgetstr("dl", NULL), maxc.y - 1);
	outcapstr(rl->movs.upm);
}

void				rl_line_rm(char **line, size_t len, t_readline *rl)
{
	char			*tmp;
	t_point			coords;
	t_point			csrm;

	if (!line || len == 0 || !rl)
		return ;
	get_line_info(&coords, rl);
	rl->csr.pos -= len;
	get_line_info(&csrm, rl);
	go_to_point(&csrm, &coords, rl);
	clr_lines(&coords, rl);
	outcap("sc");
	if (rl->csr.pos + len < rl->csr.max)
		ft_putstr_fd(*line + rl->csr.pos + len, STDIN_FILENO);
	outcap("rc");
	tmp = *line;
	*line = ft_strsub(tmp, 0, rl->csr.pos);
	if (rl->csr.pos + len < rl->csr.max)
		ft_stradd(line, tmp + rl->csr.pos + len);
	ft_strdel(&tmp);
	rl->csr.max -= len;
}

void				rl_line_add(char **line, char *add, t_readline *rl)
{
	char			*tmp;
	size_t			len;
	t_point			coords;

	if (!line || !add || !rl || !(len = ft_strlen(add)))
		return ;
	get_line_info(&coords, rl);
	outcap("ce");
	ft_putstr_fd(add, STDIN_FILENO);
	if (coords.x + len == rl->ws.ws_col)
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		outcapstr(rl->movs.leftm);
		outcap("ce");
	}
	if (rl->csr.pos < rl->csr.max)
	{
		outcap("sc");
		ft_putstr_fd(*line + rl->csr.pos, STDIN_FILENO);
		outcap("rc");
	}
	tmp = *line;
	*line = ft_strsub(tmp, 0, rl->csr.pos);
	ft_stradd(line, add);
	if (rl->csr.pos < rl->csr.max)
		ft_stradd(line, tmp + rl->csr.pos);
	ft_strdel(&tmp);
	rl->csr.max += len;
	rl->csr.pos += len;
}
