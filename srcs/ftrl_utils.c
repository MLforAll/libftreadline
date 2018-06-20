/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:49:05 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/20 03:42:51 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

void		get_line_info_for_pos(t_point *pt,
								unsigned long pos,
								t_readline *rl)
{
	pt->x = (pos + rl->prlen) % g_ws.ws_col;
	pt->y = (pos + rl->prlen) / g_ws.ws_col + 1;
}

void		get_line_info(t_point *pt, t_readline *rl)
{
	get_line_info_for_pos(pt, rl->csr.pos, rl);
}

static void	go_to_point_dumb(t_point *to, t_point *from, t_readline *rl)
{
	const t_direct		dir = to->x > from->x ? kDirectRight : kDirectLeft;
	unsigned long		pos;

	if (to->y != from->y)
	{
		ft_putchar_fd('\r', STDIN_FILENO);
		ft_putnchar_fd(' ', g_ws.ws_col, STDIN_FILENO);
		ft_putchar_fd('\r', STDIN_FILENO);
		// print line + g_ws.ws_col * (to->y - 1) with g_ws.ws_col chars max
		pos = g_ws.ws_col - 1;
	}
	else
		pos = from->x;
	while (pos != to->x)
	{
		if (dir == kDirectRight)
			ft_putchar_fd(rl->line[pos], STDIN_FILENO);
		else
			ft_putchar_fd(8, STDIN_FILENO);
		(dir == kDirectRight) ? pos++ : pos--;
	}
}

void		go_to_point(t_point *to, t_point *from, t_readline *rl)
{
	char		*tch;
	char		*tcv;
	int			lenh;
	int			lenv;

	if (from->x == to->x && from->y == to->y)
		return ;
	if (rl->dumb)
	{
		go_to_point_dumb(to, from, rl);
		return ;
	}
	tcv = (from->y < to->y) ? rl->movs.downm : rl->movs.upm;
	lenv = (from->y < to->y) ? (int)(to->y - from->y) : (int)(from->y - to->y);
	if (lenv > 0)
		outcap_arg_fb(NULL, tcv, lenv, lenv);
	if (lenv == 0)
	{
		tch = (from->x < to->x) ? rl->movs.rightm : rl->movs.leftm;
		lenh = (from->x < to->x) ? (int)(to->x - from->x)
								: (int)(from->x - to->x);
		outcap_arg_fb(NULL, tch, lenh, 1);
		return ;
	}
	outcap_arg_fb(NULL, rl->movs.rightm, (int)to->x, 1);
}

void		go_to_pos(unsigned long to, unsigned long from, t_readline *rl)
{
	t_point		toc;
	t_point		fromc;

	get_line_info_for_pos(&toc, to, rl);
	get_line_info_for_pos(&fromc, from, rl);
	go_to_point(&toc, &fromc, rl);
}

t_readline	*rl_latest_session(uint8_t set, t_readline *new_session)
{
	static t_readline	*session = NULL;

	if (set)
		session = new_session;
	return (session);
}
