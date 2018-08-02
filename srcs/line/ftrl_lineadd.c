/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_lineadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:20:51 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/02 21:47:50 by kdumarai         ###   ########.fr       */
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
	if (!rl->dumb && rl->opts->prompt_perline)
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

t_uint8				rl_line_add(char *add, t_readline *rl)
{
	size_t			len;
	t_point			coords;

	if (!add || !rl || (len = ft_strlen(add)) == 0)
		return (TRUE);
	get_line_info(&coords, rl);
	(void)outcapstr(rl->movs.cecap);
	if (!rl->dumb)
		rl_line_add_multiple(add, rl);
	(coords.x + len + rl->dumb == g_ws.ws_col) ? line_add_border(rl) : 0;
	(rl->dumb) ? ft_putstr_fd(add, STDIN_FILENO) : 0;
	if (rl->csr.pos < rl->csr.max)
	{
		(!rl->dumb) ? (void)outcap("sc") : 0;
		ft_putstr_fd(rl->line + rl->csr.pos, STDIN_FILENO);
		if (rl->dumb)
			go_to_pos(rl->csr.pos + len, rl->csr.max + len, rl);
		else
			(void)outcap("rc");
	}
	if (!rl_linebuff_add(add, len, rl))
		return (FALSE);
	rl->csr.pos += len;
	rl->csr.max += len;
	return (TRUE);
}
