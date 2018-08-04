/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_lineadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:20:51 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/04 06:03:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

inline static void	line_add_border(t_readline *rl)
{
	if (rl->dumb)
		rl_erase_dumb_line();
	else
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		(void)outcapstr(rl->movs.leftm);
	}
}

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

	if (rl->dumb)
	{
		n = g_ws.ws_col - coords->x - (coords->y == 1) * rl->prlen;
		if (n > 0)
			n = ft_putstrmax_fd(rl->line + rl->csr.pos + len, n, STDIN_FILENO);
		len += (coords->x == 0 && coords->y > 1);
		go_to_pos(rl->csr.pos + len, rl->csr.pos + n + 1, rl);
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

	n = g_ws.ws_col - coords->x - (coords->y == 1) * rl->prlen;
	n = ft_putstrmax_fd(add, n, STDIN_FILENO);
	if (!rl->dumb || n != 0)
		return ;
	line_add_border(rl);
	if (len > 1)
		go_to_pos(rl->csr.pos + n, rl->csr.pos + len, rl);
	else
	{
		coords->x = 0;
		coords->y++;
	}
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
	if (!rl->dumb)
	{
		(void)outcapstr(rl->movs.cecap);
		rl_line_add_multiple(add, rl);
	}
	if (!rl->dumb && coords.x + len + rl->dumb >= g_ws.ws_col)
		line_add_border(rl);
	if (rl->dumb)
		print_add(add, len, &coords, rl);
	if (rl->csr.pos < rl->csr.max - len)
		restore_line(len, &coords, rl);
	rl->csr.pos += len;
	return (TRUE);
}
