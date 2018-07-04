/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 02:01:46 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/04 18:10:32 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "ftrl_internal.h"

int			rl_set_term(t_uint8 echo)
{
	static struct termios	saved_t;
	struct termios			t;
	static t_uint8			state = 0;

	if (state != echo || (!echo && tcgetattr(STDIN_FILENO, &saved_t) == -1))
		return (FALSE);
	ospeed = (short)saved_t.c_ospeed;
	if (!echo)
	{
		t = saved_t;
		t.c_lflag &= (unsigned long)~(ICANON | ECHO | ISIG);
		(void)tcsetattr(STDIN_FILENO, TCSANOW, &t);
		state = 1;
	}
	else
	{
		(void)tcsetattr(STDIN_FILENO, TCSANOW, &saved_t);
		state = 0;
	}
	return (TRUE);
}

t_uint8		rl_set_timeout(t_uint8 enable, cc_t timeout)
{
	struct termios		t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return (FALSE);
	t.c_cc[VMIN] = !enable;
	t.c_cc[VTIME] = timeout;
	return (tcsetattr(STDIN_FILENO, TCSANOW, &t) != -1);
}
