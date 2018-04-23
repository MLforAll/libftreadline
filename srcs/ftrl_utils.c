/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:49:05 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/21 22:27:15 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

size_t	ft_strlen_nocolor(const char *s)
{
	size_t			ret;
	size_t			chk;

	ret = 0;
	while (*s)
	{
		if (*s == '\033')
		{
			chk = 0;
			while (chk++ < 7 && s && *s != 'm')
				s++;
			ret--;
		}
		ret++;
		s++;
	}
	return (ret);
}

void	get_line_info_for_pos(t_point *pt, unsigned int pos, t_readline *rl)
{
	pt->x = (pos + rl->prlen) % rl->ws.ws_col;
	pt->y = (pos + rl->prlen) / rl->ws.ws_col + 1;
}

void	get_line_info(t_point *pt, t_readline *rl)
{
	get_line_info_for_pos(pt, rl->csr.pos, rl);
}

void	go_to_point(t_point *to, t_point *from, t_readline *rl)
{
	char			*tch;
	char			*tcv;
	int				lenh;
	int				lenv;

	if (from->x == to->x && from->y == to->y)
		return ;
	tch = (from->x < to->x) ? rl->movs.rightm : rl->movs.leftm;
	tcv = (from->y < to->y) ? rl->movs.downm : rl->movs.upm;
	lenh = (from->x < to->x) ? to->x - from->x : from->x - to->x;
	lenv = (from->y < to->y) ? to->y - from->y : from->y - to->y;
	outcap_arg_fb(NULL, tch, lenh, 1);
	outcap_arg_fb(NULL, tcv, lenv, lenv);
}
