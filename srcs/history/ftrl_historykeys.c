/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_historykeys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:06:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 17:11:32 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftrl_internal.h"

t_keyact	rl_history_keys(char *buff, t_readline *rl, t_rl_hist **history)
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
