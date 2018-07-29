/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_dumb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 20:05:35 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/28 20:08:28 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

inline void	rl_erase_dumb_line(void)
{
	ft_putchar_fd('\r', STDIN_FILENO);
	ft_putnchar_fd(' ', g_ws.ws_col - 2, STDIN_FILENO);
	ft_putchar_fd('\r', STDIN_FILENO);
}