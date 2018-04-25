/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_confirm_tester.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 03:42:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 03:46:08 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftreadline.h"

int		main(void)
{
	int	ans;

	ans = ft_confirm("Do you want to show all files?",
					STDOUT_FILENO, kDefaultYes);
	ft_putstr("The user said ");
	ft_putstr(ans ? "YES" : "NO");
	ft_putstr("!\n");
}

