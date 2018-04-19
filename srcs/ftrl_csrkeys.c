/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_csrkeys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 09:00:17 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/19 00:44:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ftrl_internal.h"

t_keyact	rl_right_key(char *line, t_readline *rl)
{
	t_point	coords;

	(void)line;
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

t_keyact	rl_left_key(char *line, t_readline *rl)
{
	(void)line;
	if (rl->csr.pos <= 0)
		return (kKeyFail);
	rl->csr.pos--;
	outcapstr(rl->movs.leftm);
	return (kKeyOK);
}

t_keyact	rl_home_key(char *line, t_readline *rl)
{
	t_point	coords;
	t_point	homec;

	(void)line;
	get_line_info(&coords, rl);
	if (rl->csr.pos <= 0)
		return (kKeyFail);
	homec.x = rl->prlen;
	homec.y = 1;
	go_to_point(&homec, &coords, rl);
	rl->csr.pos = 0;
	return (kKeyOK);
}

t_keyact	rl_end_key(char *line, t_readline *rl)
{
	t_point	coords;
	t_point	maxc;

	(void)line;
	get_line_info(&coords, rl);
	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	if (rl->csr.pos >= rl->csr.max)
		return (kKeyFail);
	go_to_point(&maxc, &coords, rl);
	rl->csr.pos = rl->csr.max;
	return (kKeyOK);
}
