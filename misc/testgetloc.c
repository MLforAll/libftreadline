/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testgetloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 05:14:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/30 00:50:09 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>

#ifdef TERMCAP
static int	putcf(int c)
{
	return (write(1, (void*)&c, 1));
}
#endif

int			main(void)
{
	struct termios t;
	struct termios saved;
	char	buff[20];
	char *ptr;

	write(1, "yolo", 4);
	tcgetattr(0, &saved);
	t = saved;
	t.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &t);
#ifdef TERMCAP
	tputs(tgetstr("RQ", NULL), 1, &putcf);
#else
	write(0, "\033[6n", 4);
#endif
	bzero(buff, sizeof(buff));
	read(0, buff, 20);
	//puts(buff + 2);
	tcsetattr(0, TCSANOW, &saved);
	if ((ptr = strrchr(buff, ';')) && atoi(ptr + 1) > 1)
		write(1, "%\n", 2);
	return 0;
}
