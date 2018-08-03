/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_linerm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/03 20:29:14 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

inline static void	clr_lines(t_point *coords, int x, t_readline *rl)
{
	t_point	maxc;
	int		cnt;

	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	(void)outcapstr(rl->movs.cecap);
	if (coords->y >= maxc.y)
		return ;
	cnt = (int)maxc.y - 1;
	(void)outcapstr(rl->movs.downm);
	(void)outcap_arg_fb(rl->movs.dlargcap, rl->movs.dlcap, cnt, cnt);
	(void)outcapstr(rl->movs.upm);
	(void)outcap_arg_fb(NULL, rl->movs.rightm, x, 1);
}

/*
** Note: -3 to compensate for +1 in nspaces
** Remember: We are not using the last 2 chars in a term line in dumb mode
*/

inline static void	rl_line_rm_dumb(size_t len, t_point *gtc, t_readline *rl)
{
	t_point			back;
	size_t			nspaces;
	unsigned long	pos;

	back = *gtc;
	nspaces = g_ws.ws_col - gtc->x + 1 - ((gtc->y == 1) ? rl->prlen : 3);
	back.x += nspaces;
	ft_putnchar_fd(' ', nspaces, STDIN_FILENO);
	go_to_point(rl->csr.pos, gtc, &back, rl);
	if (!*rl->line)
		return ;
	pos = rl->csr.pos;
	pos += ft_putstrmax_fd(rl->line + rl->csr.pos + len, nspaces, STDIN_FILENO);
	get_line_info_for_pos(&back, pos, rl);
	go_to_point(pos, gtc, &back, rl);
}

t_uint8				rl_line_rm(size_t len, t_readline *rl)
{
	t_point			coords;
	t_point			gtc;

	if (len == 0 || !rl || len > rl->csr.max)
		return (TRUE);
	get_line_info(&coords, rl);
	if (rl->csr.pos > 0)
		rl->csr.pos -= len;
	rl->csr.max -= len;
	get_line_info(&gtc, rl);
	go_to_point(rl->csr.pos + len, &gtc, &coords, rl);
	if (rl->dumb)
		rl_line_rm_dumb(len, &gtc, rl);
	else
	{
		clr_lines(&coords, (int)gtc.x, rl);
		(void)outcap("sc");
		if (*rl->line)
			ft_putstr_fd(rl->line + rl->csr.pos + len, STDIN_FILENO);
		(void)outcap("rc");
	}
	return ((t_uint8)rl_linebuff_rm(len, rl));
}
