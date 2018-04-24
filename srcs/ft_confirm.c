/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_confirm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:50:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/24 13:03:07 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftrl_internal.h"

int		ft_confirm(const char *msg, int outfd, t_dflact dfl)
{
	(void)dfl;
	ft_putstr_fd(msg, outfd);
	return (1);
}
