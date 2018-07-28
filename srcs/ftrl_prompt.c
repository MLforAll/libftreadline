/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 03:45:43 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/28 18:54:59 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

inline static t_uint8	ftrl_prompt_isvalid_dumb_core(size_t prlen)
{
	struct winsize	ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		return (FALSE);
	return ((prlen <= ws.ws_col * 3 / 4));
}

t_uint8					ftrl_prompt_isvalid_dumb(const char *prompt)
{
	return (ftrl_prompt_isvalid_dumb_core(ft_prompt_len(prompt)));
}

t_uint8					rl_prompt_init(t_readline *rl, const char *prompt)
{
	rl->prlen = (prompt == NULL) ? 0 : ft_prompt_len(prompt);
	if (!rl->dumb || rl->opts->dumb_prompt)
	{
		if (rl->dumb || tgetnum("Co") < 8)
			rl->prompt = ft_prompt_nocolor(prompt);
		else
			rl->prompt = ft_strdup((prompt == NULL) ? "" : prompt);
	}
	if (rl->dumb && (!rl->opts->dumb_prompt
					|| !ftrl_prompt_isvalid_dumb_core(rl->prlen)))
	{
		free(rl->prompt);
		rl->prompt = ft_strdup("$> ");
		rl->prlen = ft_strlen(rl->prompt);
	}
	return (rl->prompt != NULL);
}
