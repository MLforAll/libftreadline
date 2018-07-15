/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_linekeys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/15 03:15:02 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

t_keyact	rl_input_add_text(char *buff, t_readline *rl)
{
	char			add[RL_READBUFFSIZE + 1];
	unsigned int	idx;

	if (*buff == 27)
		return (kKeyNone);
	idx = 0;
	ft_bzero(add, sizeof(add));
	while (*buff)
	{
		if (ft_isprint(*buff))
		{
			add[idx] = *buff;
			idx++;
		}
		buff++;
	}
	rl_line_add(add, rl);
	return ((idx > 0) ? kKeyOK : kKeyFail);
}

t_keyact	rl_input_rm_text(char *buff, t_readline *rl)
{
	int				keys[2];

	keys[0] = (*buff == 127);
	keys[1] = (ft_strequ(buff, rl->keys.delk));
	if (!keys[0] && !keys[1])
		return (kKeyNone);
	if (keys[0] && rl->csr.pos > 0)
	{
		rl_line_rm(1, rl);
		return (kKeyOK);
	}
	else if (keys[1] && rl->csr.pos < rl->csr.max)
	{
		rl_right_key(rl);
		rl_line_rm(1, rl);
		return (kKeyOK);
	}
	return (kKeyFail);
}

t_keyact	rl_clear_line(t_readline *rl)
{
	if (rl->dumb)
		return (kKeyFail);
	(void)outcap("cr");
	(void)outcapstr(rl->movs.cecap);
	free(rl->line);
	if (!rl_linebuff_create(rl))
		return (kKeyFatal);
	ft_putstr_fd(rl->prompt, rl->opts->outfd);
	ft_bzero(&rl->csr, sizeof(t_cursor));
	return (kKeyOK);
}
