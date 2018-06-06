/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 23:37:55 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/06 23:59:20 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "ftrl_internal.h"

uint8_t	ftrl_quit(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return (FALSE);
	t.c_cc[VMIN] = 0;
	t.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	return (TRUE);
}
