/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/28 02:02:54 by kdumarai         ###   ########.fr       */
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
	outcapstr(rl->movs.cecap);
	if (coords->y >= maxc.y)
		return ;
	cnt = (int)maxc.y - 1;
	outcapstr(rl->movs.downm);
	outcap_arg_fb(tgetstr("DL", NULL), tgetstr("dl", NULL), cnt, cnt);
	outcapstr(rl->movs.upm);
	outcap_arg_fb(NULL, rl->movs.rightm, (int)rl->csr.pos, 1);
}

void				rl_line_rm(size_t len, t_readline *rl)
{
	t_point			coords;
	t_point			csrm;
	t_point			back;

	if (len == 0 || !rl)
		return ;
	get_line_info(&coords, rl);
	rl->csr.pos -= len;
	get_line_info(&csrm, rl);
	go_to_point(&csrm, &coords, rl);
	if (rl->dumb)
	{
		ft_putnchar_fd(' ', g_ws.ws_col - csrm.x - 1, STDIN_FILENO);
		back = csrm;
		back.x = g_ws.ws_col - 1;
		go_to_point(&csrm, &back, rl);
	}
	else
		clr_lines(&coords, rl);
	outcap("sc");
	if (rl->csr.pos + len < rl->csr.max)
		ft_putstr_fd(rl->line + rl->csr.pos + len, STDIN_FILENO);
	outcap("rc");
	rl_linebuff_rm(len, rl);
	rl->csr.max -= len;
}

inline static void	line_add_border(t_readline *rl)
{
	if (rl->dumb)
	{
		ft_putchar_fd('\r', STDIN_FILENO);
		ft_putnchar_fd(' ', g_ws.ws_col, STDIN_FILENO);
		ft_putchar_fd('\r', STDIN_FILENO);
	}
	else
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		outcapstr(rl->movs.leftm);
	}
}

void				rl_line_add(char *add, t_readline *rl)
{
	size_t			len;
	t_point			coords;

	if (!add || !rl || !(len = ft_strlen(add)))
		return ;
	get_line_info(&coords, rl);
	outcapstr(rl->movs.cecap);
	if (!rl->dumb)
		ft_putstr_fd(add, STDIN_FILENO);
	if (coords.x + len + rl->dumb == g_ws.ws_col)
		line_add_border(rl);
	if (rl->dumb)
		ft_putstr_fd(add, STDIN_FILENO);
	if (rl->csr.pos < rl->csr.max)
	{
		outcap("sc");
		ft_putstr_fd(rl->line + rl->csr.pos, STDIN_FILENO);
		outcap("rc");
	}
	rl_linebuff_add(add, len, rl);
	rl->csr.pos += len;
	rl->csr.max += len;
}
