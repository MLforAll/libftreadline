/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 23:37:55 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/09 03:00:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"
#include "ftrl_quit.h"

static void		quit_putmsg(void *data)
{
	t_quitmsgdat	*msg;

	if (!(msg = (t_quitmsgdat*)data))
		return ;
	ft_putendlsec_fd(msg->msg, msg->fd);
}

static uint8_t	quit_with_reason(t_abort reason,
								void (*func)(void *),
								void *data)
{
	t_readline		*rl;

	if (!(rl = rl_latest_session(NULL)) || !rl_set_timeout(YES, 0))
		return (FALSE);
	rl->quit.reason = reason;
	rl->quit.func = func;
	rl->quit.func_data = data;
	return (TRUE);
}

uint8_t			ftrl_quit(void)
{
	return (quit_with_reason(kAbortQuit, NULL, NULL));
}


uint8_t			ftrl_insert_msg(const char *msg, int fd)
{
	t_quitmsgdat	*data;

	if (!(data = (t_quitmsgdat*)malloc(sizeof(t_quitmsgdat))))
		return (FALSE);
	data->msg = msg;
	data->fd = fd;
	if (!quit_with_reason(kAbortReload, &quit_putmsg, data))
	{
		free(data);
		return (FALSE);
	}
	return (TRUE);
}
