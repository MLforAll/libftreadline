/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_historykeys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:06:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/28 03:13:29 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

static t_keyact	rl_history_keys(char *buff, t_readline *rl, t_dlist **history)
{
	int		keys[2];

	keys[0] = (ft_strequ(buff, rl->keys.upk));
	keys[1] = (ft_strequ(buff, rl->keys.downk));
	if (!keys[0] && !keys[1])
		return (kKeyNone);
	if (!history || !*history)
		return (kKeyFail);
	if (keys[0] && (*history)->next)
		*history = (*history)->next;
	else if (keys[1] && (*history)->prev)
		*history = (*history)->prev;
	else
		return (kKeyFail);
	return (kKeyOK);
}

static void		disp_new_line(t_point *maxc, t_readline *rl)
{
	if (rl->dumb)
	{
		ft_putchar('\r');
		ft_putnchar_fd(' ', g_ws.ws_col, STDIN_FILENO);
		ft_putchar_fd('\r', STDIN_FILENO);
		ft_putstr_fd(rl->prompt, STDIN_FILENO);
		ft_putstrmax_fd(rl->line, g_ws.ws_col - rl->prlen - 2, STDIN_FILENO);
		return ;	
	}
	outcap("cr");
	outcap_arg_fb(tgetstr("DL", NULL), tgetstr("dl", NULL),
		(int)maxc->y, (int)maxc->y);
	ft_putstr_fd(rl->prompt, rl->opts->outfd);
	ft_putstr_fd(rl->line, STDIN_FILENO);
}

t_keyact		hist_nav(char *buff, t_readline *rl, t_dlist **hist)
{
	t_point		maxc;
	t_keyact	retk;

	if ((retk = rl_history_keys(buff, rl, hist)) != kKeyOK)
		return (retk);
	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	go_to_pos(0, rl->csr.pos, rl);
	free(rl->line);
	if ((char*)(*hist)->content)
	{
		rl->line = ft_strdup((char*)(*hist)->content);
		rl->bufflen = ft_strlen(rl->line);
	}
	else
		rl->bufflen = rl_linebuff_create(&rl->line);
	rl->csr.max = ft_strlen(rl->line);
	rl->csr.pos = rl->csr.max;
	disp_new_line(&maxc, rl);
	return (kKeyOK);
}

/*
**t_keyact	rl_historybu_key(t_rl_hist **history, t_readline *rl)
**{
**	if (!history || !*history || !(*history)->next)
**		return (kKeyFail);
**	return (kKeyOK);
**}
**
**t_keyact	rl_historybd_key(t_rl_hist **history, t_readline *rl)
**{
**	if (!history || !*history || !(*history)->prev)
**		return (kKeyFail);
**	return (kKeyOK);
**}
*/
