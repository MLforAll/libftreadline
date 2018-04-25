/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_confirm_tester.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 03:42:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 04:06:35 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftreadline.h"

int		main(int ac, char **av)
{
	int		ans;
	char	*msg;

	msg = (ac < 2) ? "Default message?" : av[1];
	ans = ft_confirm(msg, STDOUT_FILENO, kDefaultYes);
	ft_putstr("The user said ");
	ft_putstr(ans ? "YES" : "NO");
	ft_putstr("!\n");
}

