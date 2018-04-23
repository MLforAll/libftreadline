/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/23 19:49:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

inline static void	clr_lines(t_point *coords, t_readline *rl)
{
	t_point	maxc;
	int		cnt;

	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	outcap("ce");
	if (coords->y >= maxc.y)
		return ;
	cnt = maxc.y - 1;
	outcapstr(rl->movs.downm);
	outcap_arg_fb(tgetstr("DL", NULL), tgetstr("dl", NULL), cnt, cnt);
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
	rl->bufflen = ft_strlen(*line);
	rl->csr.max -= len;
}

inline static void	pos_csr_nl(t_point *coords, size_t len, t_readline *rl)
{
	if (coords->x + len == rl->ws.ws_col)
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		outcapstr(rl->movs.leftm);
		outcap("ce");
	}
}

void				rl_line_add(char **line, char *add, t_readline *rl)
{
	//char			*tmp;
	size_t			len;
	t_point			coords;

	if (!line || !add || !rl || !(len = ft_strlen(add)))
		return ;
	get_line_info(&coords, rl);
	outcap("ce");
	ft_putstr_fd(add, STDIN_FILENO);
	pos_csr_nl(&coords, len, rl);
	if (rl->csr.pos < rl->csr.max)
	{
		outcap("sc");
		ft_putstr_fd(*line + rl->csr.pos, STDIN_FILENO);
		outcap("rc");
	}
	/*tmp = *line;
	*line = ft_strsub(tmp, 0, rl->csr.pos);
	ft_stradd(line, add);
	if (rl->csr.pos < rl->csr.max)
		ft_stradd(line, tmp + rl->csr.pos);
	ft_strdel(&tmp);*/
	rl_linebuff_add(line, add, len, rl);
	rl->csr.max += len;
	rl->csr.pos += len;
}
