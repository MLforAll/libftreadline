/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/02 04:41:17 by kdumarai         ###   ########.fr       */
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

inline static void	rl_line_rm_dumb(size_t len, t_point *csrm, t_readline *rl)
{
	t_point		back;
	size_t		nspaces;

	back = *csrm;
	nspaces = g_ws.ws_col - csrm->x - 2 - ((back.y == 1) ? rl->prlen : 0);
	back.x += nspaces;
	ft_putnchar_fd(' ', nspaces, STDIN_FILENO);
	go_to_point(rl->csr.pos, csrm, &back, rl);
	if (*rl->line)
		ft_putstr_fd(rl->line + rl->csr.pos + len, STDIN_FILENO);
	get_line_info_for_pos(&back, rl->csr.max, rl);
	go_to_point(rl->csr.max, csrm, &back, rl);
}

t_uint8				rl_line_rm(size_t len, t_readline *rl)
{
	t_point			coords;
	t_point			csrm;

	if (len == 0 || !rl || len > rl->csr.max)
		return (TRUE);
	get_line_info(&coords, rl);
	if (rl->csr.pos > 0)
		rl->csr.pos -= len;
	rl->csr.max -= len;
	get_line_info(&csrm, rl);
	go_to_point(rl->csr.pos + len, &csrm, &coords, rl);
	if (rl->dumb)
		rl_line_rm_dumb(len, &csrm, rl);
	else
	{
		clr_lines(&coords, (int)csrm.x, rl);
		(void)outcap("sc");
		if (*rl->line)
			ft_putstr_fd(rl->line + rl->csr.pos + len, STDIN_FILENO);
		(void)outcap("rc");
	}
	return ((t_uint8)rl_linebuff_rm(len, rl));
}

inline static void	line_add_border(t_readline *rl)
{
	if (rl->dumb)
		rl_erase_dumb_line();
	else
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		(void)outcapstr(rl->movs.leftm);
	}
}

t_uint8				rl_line_add(char *add, t_readline *rl)
{
	size_t			len;
	t_point			coords;

	if (!add || !rl || (len = ft_strlen(add)) == 0)
		return (TRUE);
	get_line_info(&coords, rl);
	(void)outcapstr(rl->movs.cecap);
	(!rl->dumb) ? ft_putstr_fd(add, STDIN_FILENO) : 0;
	(coords.x + len + rl->dumb == g_ws.ws_col) ? line_add_border(rl) : 0;
	(rl->dumb) ? ft_putstr_fd(add, STDIN_FILENO) : 0;
	if (rl->csr.pos < rl->csr.max)
	{
		(!rl->dumb) ? (void)outcap("sc") : 0;
		ft_putstr_fd(rl->line + rl->csr.pos, STDIN_FILENO);
		if (rl->dumb)
			go_to_pos(rl->csr.pos + len, rl->csr.max + len, rl);
		else
			(void)outcap("rc");
	}
	if (!rl_linebuff_add(add, len, rl))
		return (FALSE);
	rl->csr.pos += len;
	rl->csr.max += len;
	return (TRUE);
}
