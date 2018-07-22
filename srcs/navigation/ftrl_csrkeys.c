/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_csrkeys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 09:00:17 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/22 14:39:52 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ftrl_internal.h"

void		check_selection(t_readline *rl)
{
	if (rl->cpypste.mkrs[0] == 0 && rl->cpypste.mkrs[1] == 0)
		return ;
	go_to_pos(rl->cpypste.mkrs[0], rl->csr.pos, rl);
	ft_putstrmax_fd(rl->line + rl->cpypste.mkrs[0],
		rl->cpypste.mkrs[1] - rl->cpypste.mkrs[0], STDIN_FILENO);
	go_to_pos(rl->csr.pos, rl->cpypste.mkrs[1], rl);
	ft_bzero(rl->cpypste.mkrs, sizeof(rl->cpypste.mkrs));
}

t_keyact	rl_right_key(t_readline *rl)
{
	t_point		coords;
	t_point		gtc;

	if (rl->csr.pos >= rl->csr.max)
		return (kKeyFail);
	get_line_info(&coords, rl);
	/*if (coords.x + 1 + rl->dumb == g_ws.ws_col)
	{
		if (rl->dumb)
			go_to_pos(rl->csr.pos + 1, rl->csr.pos, rl);
		else
		{
			(void)outcapstr(rl->movs.crcap);
			outcapstr(rl->movs.downm);
		}
	}
	else if (rl->dumb)
		ft_putchar_fd(rl->line[rl->csr.pos], STDIN_FILENO);
	else
		(void)outcapstr(rl->movs.rightm);*/
	rl->csr.pos++;
	get_line_info(&gtc, rl);
	go_to_point(&gtc, &coords, rl);
	return (kKeyOK);
}

t_keyact	rl_left_key(t_readline *rl)
{
	t_point		coords;
	t_point		gtc;

	if (rl->csr.pos <= 0)
		return (kKeyFail);
	get_line_info(&coords, rl);
	rl->csr.pos--;
	get_line_info(&gtc, rl);
	go_to_point(&gtc, &coords, rl);
	return (kKeyOK);
}

t_keyact	rl_home_key(t_readline *rl)
{
	t_point	coords;
	t_point	homec;

	get_line_info(&coords, rl);
	if (rl->csr.pos <= 0 || coords.y >= g_ws.ws_row)
		return (kKeyFail);
	get_line_info_for_pos(&homec, 0, rl);
	go_to_point(&homec, &coords, rl);
	rl->csr.pos = 0;
	return (kKeyOK);
}

t_keyact	rl_end_key(t_readline *rl)
{
	t_point	coords;
	t_point	maxc;

	get_line_info(&coords, rl);
	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	if (rl->csr.pos >= rl->csr.max)
		return (kKeyFail);
	go_to_point(&maxc, &coords, rl);
	rl->csr.pos = rl->csr.max;
	return (kKeyOK);
}
