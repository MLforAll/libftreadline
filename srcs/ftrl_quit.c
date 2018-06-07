/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 23:37:55 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/07 02:34:58 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "ftrl_internal.h"

static uint8_t	quit_with_reason(t_abort reason)
{
	struct termios	t;
	t_readline		*rl;

	if (!(rl = rl_latest_session(NULL)) || tcgetattr(STDIN_FILENO, &t) == -1)
		return (FALSE);
	t.c_cc[VMIN] = 0;
	t.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	rl->abort_reason = reason;
	return (TRUE);
}

uint8_t			ftrl_quit(void)
{
	return (quit_with_reason(kAbortQuit));
}


uint8_t			ftrl_insert_msg(const char *msg, int fd)
{
	if (!quit_with_reason(kAbortReload))
		return (FALSE);
	ft_putendlsec_fd(msg, fd);
	return (TRUE);
}
