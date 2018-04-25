/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_historykeys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 11:06:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 12:40:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftrl_internal.h"

/*t_keyact	rl_history_keys(t_rl_hist **history, char *buff, char **line)
{
	int		ret;
	int		keys[2];

	keys[0] = (buff && ft_strcmp("\033[A", buff) == 0);
	keys[1] = (buff && ft_strcmp("\033[B", buff) == 0);
	if (!line || !history || (!keys[0] && !keys[1]))
		return (kKeyNone);
	if (!*history)
		return (kKeyFail);
	ret = -1;
	if (keys[0] && (*history)->next)
	{
		*history = (*history)->next;
		ret = 1;
	}
	if (keys[1] && (*history)->prev)
	{
		*history = (*history)->prev;
		ret = 1;
	}
	if (ret == -1)
		return (kKeyFail);
	ft_strdel(line);
	*line = ft_strdup((*history)->line);
	return (kKeyOK);
}*/

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

/*t_keyact	rl_historybu_key(t_rl_hist **history, t_readline *rl)
{
	if (!history || !*history || !(*history)->next)
		return (kKeyFail);
	return (kKeyOK);
}

t_keyact	rl_historybd_key(t_rl_hist **history, t_readline *rl)
{
	if (!history || !*history || !(*history)->prev)
		return (kKeyFail);
	return (kKeyOK);	
}*/
