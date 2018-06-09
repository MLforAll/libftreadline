/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 02:01:46 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/09 03:00:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "ftrl_internal.h"

int			rl_set_term(uint8_t echo)
{
	static struct termios	saved_t;
	struct termios			t;
	static uint8_t			state = 0;

	if (state != echo || (!echo && tcgetattr(STDIN_FILENO, &saved_t) == -1))
		return (FALSE);
	ospeed = saved_t.c_ospeed;
	if (!echo)
	{
		t = saved_t;
		t.c_lflag &= ~(ICANON | ECHO | ISIG);
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
		state = 1;
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_t);
		state = 0;
	}
	return (TRUE);
}

uint8_t		rl_set_timeout(uint8_t enable, cc_t timeout)
{
	struct termios		t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return (FALSE);
	t.c_cc[VMIN] = !enable;
	t.c_cc[VTIME] = timeout;
	return (tcsetattr(STDIN_FILENO, TCSANOW, &t) != -1);
}
