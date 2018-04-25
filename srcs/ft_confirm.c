/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_confirm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:50:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 04:15:02 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

static int			get_ret(char c, t_dflact dfl)
{
	if (c == '\n')
		return ((dfl == kDefaultYes));
	if (ft_tolower(c) == 'y')
		return (1);
	if (ft_tolower(c) == 'n')
		return (0);
	return (-1);
}

inline static void	print_message(const char *msg, int outfd, t_dflact dfl)
{
	ft_putstr_fd(msg, outfd);
	ft_putstr_fd(" (", outfd);
	ft_putstr_fd((dfl == kDefaultYes) ? "Y" : "y", outfd);
	ft_putchar_fd('/', outfd);
	ft_putstr_fd((dfl == kDefaultNo) ? "N" : "n", outfd);
	ft_putstr_fd(") ", outfd);
}

int					ft_confirm(const char *msg, int outfd, t_dflact dfl)
{
	char	buff[5];
	int		reset_after;
	int		ret;

	ret = 0;
	tgetent(NULL, getenv("TERM"));
	reset_after = rl_set_term(NULL, NO);
	print_message(msg, outfd, dfl);
	ft_bzero(buff, sizeof(buff));
	while (read(STDIN_FILENO, buff, 4) > 0)
	{
		if (ft_strlen(buff) == 1 && (ret = get_ret(*buff, dfl)) != -1)
			break ;
		ft_bzero(buff, sizeof(buff));
	}
	outcap("cr");
	ft_putchar_fd('\n', outfd);
	if (reset_after)
		rl_set_term(NULL, YES);
	return (ret);
}
