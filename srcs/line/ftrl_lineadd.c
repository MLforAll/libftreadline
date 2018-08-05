/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_lineadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:20:51 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/05 05:47:34 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

static void			rl_line_add_multiple(char *add, t_readline *rl)
{
	size_t		len;
	const char	*chr;
	const char	*tmp;

	tmp = add;
	if (rl->opts->prompt_perline)
	{
		while ((chr = ft_strchr(tmp, '\n')))
		{
			len = (size_t)(chr - tmp) + 1;
			(void)ft_putstrmax_fd(tmp, len, STDIN_FILENO);
			ft_putstr_fd(rl->prompt, rl->opts->outfd);
			tmp += len;
		}
	}
	ft_putstr_fd(tmp, STDIN_FILENO);
}

inline static void	restore_line(size_t len, t_point *coords, t_readline *rl)
{
	size_t	n;
	size_t	p;

	if (rl->dumb)
	{
		n = g_ws.ws_col - coords->x - 2 - len;
		if (n > 0)
			p = ft_putstrmax_fd(rl->line + rl->csr.pos + len, n, STDIN_FILENO);
		else
			p = 0;
		go_to_pos(rl->csr.pos + len, rl->csr.pos + p + 1, rl);
		return ;
	}
	(void)outcap("sc");
	ft_putstr_fd(rl->line + rl->csr.pos + len, STDIN_FILENO);
	(void)outcap("rc");
}

inline static void	print_add(char *add,
							size_t len,
							t_point *coords,
							t_readline *rl)
{
	size_t			n;

	if (!rl->dumb)
	{
		(void)outcapstr(rl->movs.cecap);
		rl_line_add_multiple(add, rl);
		if (coords->x + len >= g_ws.ws_col)
		{
			ft_putchar_fd(' ', STDIN_FILENO);
			(void)outcapstr(rl->movs.leftm);
		}
		return ;
	}
	n = g_ws.ws_col - coords->x - 2;
	if (len > n)
	{
		rl_erase_dumb_line();
		ft_putstr_fd(add + n, STDIN_FILENO);
		get_line_info_for_pos(coords, rl->csr.pos + len, rl);
		return ;
	}
	ft_putstr_fd(add, STDIN_FILENO);
}

t_uint8				rl_line_add(char *add, t_readline *rl)
{
	size_t			len;
	t_point			coords;

	if (!add || !rl || (len = ft_strlen(add)) == 0)
		return (TRUE);
	if (!rl_linebuff_add(add, len, rl))
		return (FALSE);
	rl->csr.max += len;
	get_line_info(&coords, rl);
	print_add(add, len, &coords, rl);
	if (rl->csr.pos < rl->csr.max - len)
		restore_line(len, &coords, rl);
	rl->csr.pos += len;
	return (TRUE);
}
