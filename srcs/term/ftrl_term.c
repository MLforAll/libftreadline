/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 02:01:46 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/06 15:36:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <limits.h>
#include "ftrl_internal.h"

int					rl_set_term(uint8_t echo)
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

/*int					rl_set_opost(uint8_t opost)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return (FALSE);
	if (opost)
		t.c_oflag |= OPOST;
	else
		t.c_oflag &= ~OPOST;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	return (TRUE);
}*/
