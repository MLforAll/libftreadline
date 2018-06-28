/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_cpypaste.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:03:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/28 18:27:50 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ftrl_internal.h"

t_keyact	rl_leftcpy_key(t_readline *rl)
{
	if (!rl || rl->cpypste.mkrs[1] <= rl->cpypste.mkrs[0]
		|| rl->cpypste.mkrs[1] == 0)
		return (kKeyFail);
	rl_left_key(rl);
	ft_putchar_fd(rl->line[rl->csr.pos], STDIN_FILENO);
	rl->csr.pos++;
	rl_left_key(rl);
	rl->cpypste.mkrs[1]--;
	return (kKeyOK);
}

t_keyact	rl_rightcpy_key(t_readline *rl)
{
	static uint8_t	idx = 0;
	t_point			pos;

	if (!rl)
		return (kKeyFail);
	rl->cpypste.mkrs[idx] = rl->csr.pos + (idx == 1);
	idx = 1;
	if (rl->dumb)
	{
		get_line_info(&pos, rl);
		if (pos.x + 2 == g_ws.ws_col)
			go_to_pos(rl->csr.pos + 1, rl->csr.pos, rl);
		ft_putchar_fd(ft_toupper(rl->line[rl->csr.pos]), STDIN_FILENO);
	}
	else
	{
		(void)outcap("mr");
		ft_putchar_fd(rl->line[rl->csr.pos], STDIN_FILENO);
		(void)outcap("me");
	}
	rl->csr.pos++;
	return (kKeyOK);
}

t_keyact	rl_cpy_key(t_readline *rl)
{
	char	*cpy;
	size_t	len;

	if (!rl || !*rl->line
		|| !(len = rl->cpypste.mkrs[1] - rl->cpypste.mkrs[0]))
		return (kKeyFail);
	if (!(cpy = ft_strsub(rl->line, (unsigned int)rl->cpypste.mkrs[0], len)))
		return (kKeyFail);
	if (ft_strequ(rl->cpypste.dat, cpy))
	{
		go_to_pos(rl->cpypste.mkrs[1], rl->csr.pos, rl);
		rl_line_rm(len, rl);
	}
	else
	{
		go_to_pos(rl->cpypste.mkrs[0], rl->csr.pos, rl);
		ft_putstr_fd(cpy, STDIN_FILENO);
		go_to_pos(rl->csr.pos, rl->cpypste.mkrs[1], rl);
	}
	ft_strdel(&rl->cpypste.dat);
	rl->cpypste.dat = cpy;
	return (kKeyOK);
}

t_keyact	rl_paste_key(t_readline *rl)
{
	if (!rl || !rl->cpypste.dat)
		return (kKeyFail);
	rl_line_add(rl->cpypste.dat, rl);
	ft_bzero(&rl->cpypste.mkrs, sizeof(rl->cpypste.mkrs));
	return (kKeyOK);
}
