/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_confirm_tester.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 03:42:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 08:11:22 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftreadline.h"

int		main(int ac, char **av)
{
	int			ans;
	char		*msg;
	t_dflact	dfl;

	msg = (ac < 2) ? "Default message?" : av[1];
	if (ac < 3)
		dfl = kDefaultYes;
	else
	{
		if (ft_strequ(av[2], "no"))
			dfl = kDefaultNo;
		else if (ft_strequ(av[2], "yes"))
			dfl = kDefaultYes;
		else
		{
			ft_putendl_fd("Argument error: should be yes or no", STDERR_FILENO);
			return (1);
		}
	}
	ans = ft_confirm(msg, STDOUT_FILENO, dfl);
	ft_putstr("The user said ");
	ft_putstr(ans ? "YES" : "NO");
	ft_putstr("!\n");
	return (0);
}

