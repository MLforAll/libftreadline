/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:49:05 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/17 18:55:00 by kdumarai         ###   ########.fr       */
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
	pt->y = (pos + rl->prlen) / rl->ws.ws_col + (pt->x != 0);
}

void	get_line_info(t_point *pt, t_readline *rl)
{
	get_line_info_for_pos(pt, rl->csr.pos, rl);
}
