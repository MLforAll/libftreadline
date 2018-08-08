/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_lineinfo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 04:59:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/08 05:01:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftrl_internal.h"

inline static void	adapt_multiple_lines(t_point *pt,
										unsigned long pos,
										t_readline *rl)
{
	char			*bw;

	pt->x = rl->prlen;
	bw = rl->line;
	while (*bw && bw != rl->line + pos)
	{
		if (*(bw++) == '\n')
		{
			pt->y++;
			pt->x = 0;
		}
		else
			pt->x++;
	}
}

void				get_line_info_for_pos(t_point *pt,
										unsigned long pos,
										t_readline *rl)
{
	const char		*chrret;
	unsigned long	ypos;

	if (g_ws.ws_col == 0 || g_ws.ws_row == 0)
		return ;
	chrret = ft_strchr(rl->line, '\n');
	ypos = (chrret) ? (size_t)(chrret - rl->line) : pos;
	pt->y = (ypos + rl->prlen) / (g_ws.ws_col - rl->dumb) + 1;
	if (!rl->line || rl->dumb)
	{
		pt->x = (pos + rl->prlen) % (g_ws.ws_col - rl->dumb);
		return ;
	}
	adapt_multiple_lines(pt, pos, rl);
	pt->x = pt->x % g_ws.ws_col;
}

inline void			get_line_info(t_point *pt, t_readline *rl)
{
	get_line_info_for_pos(pt, rl->csr.pos, rl);
}
