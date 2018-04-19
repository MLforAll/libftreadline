/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:20:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/20 00:55:36 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

static int			putcf(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (1);
}

int					outcap(char *name)
{
	char	*cap;

	cap = tgetstr(name, NULL);
	if (!cap || tputs(cap, 1, &putcf) == -1)
		return (FALSE);
	return (TRUE);
}

int					outcapstr(char *cstr)
{
	if (tputs(cstr, 1, &putcf) == -1)
		return (FALSE);
	return (TRUE);
}

int					outcap_arg_fb(char *cstr, char *fb, int arg)
{
	char	*prog;

	if (cstr)
	{
		if ((prog = tgoto(cstr, arg, arg)))
			return (outcapstr(prog));
	}
	while (arg--)
	{
		if (!outcapstr(fb))
			return (FALSE);
	}
	return (TRUE);
}
