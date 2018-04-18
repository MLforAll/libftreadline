/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_csrkeys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 09:00:17 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/18 01:32:50 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ftrl_internal.h"

t_keyact	rl_right_key(char *buff, t_readline *rl)
{
	t_point	coords;

	(void)buff;
	get_line_info(&coords, rl);
	if (rl->csr.pos >= rl->csr.max)
		return (kKeyFail);
	if (coords.x + 1 == rl->ws.ws_col)
	{
		outcap("cr");
		outcapstr(rl->movs.downm);
	}
	else
		outcapstr(rl->movs.rightm);
	rl->csr.pos++;
	return (kKeyOK);
}

t_keyact	rl_left_key(char *buff, t_readline *rl)
{
	(void)buff;
	if (rl->csr.pos <= 0)
		return (kKeyFail);
	rl->csr.pos--;
	outcapstr(rl->movs.leftm);
	return (kKeyOK);
}

static void	go_to_x(unsigned int to, unsigned int from, t_readline *rl)
{
	char			*tc;
	size_t			len;
	unsigned int	prog;

	if (from == to)
		return ;
	tc = (from < to) ? rl->movs.rightm : rl->movs.leftm;
	len = (from < to) ? to - from : from - to;
	prog = 0;
	while (prog++ < len)
		outcapstr(tc);
}

t_keyact	rl_home_key(char *buff, t_readline *rl)
{
	t_point	coords;

	(void)buff;
	get_line_info(&coords, rl);
	if (rl->csr.pos <= 0)
		return (kKeyFail);
	go_to_x(rl->prlen, coords.x, rl);
	while (coords.y > 1)
	{
		outcapstr(rl->movs.upm);
		coords.y--;
	}
	rl->csr.pos = 0;
	return (kKeyOK);
}

t_keyact	rl_end_key(char *buff, t_readline *rl)
{
	t_point	coords;
	t_point	maxc;

	(void)buff;
	get_line_info(&coords, rl);
	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	if (rl->csr.pos >= rl->csr.max)
		return (kKeyFail);
	go_to_x(maxc.x, coords.x, rl);
	while (coords.y < maxc.y)
	{
		outcapstr(rl->movs.downm);
		coords.y++;
	}
	rl->csr.pos = rl->csr.max;
	return (kKeyOK);
}
