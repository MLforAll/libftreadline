/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 03:45:43 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/22 16:41:35 by kdumarai         ###   ########.fr       */
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

void					rl_prompt_init(t_readline *rl, const char *prompt)
{
	rl->prlen = (prompt == NULL) ? 0 : ft_prompt_len(prompt);
	rl->prompt = (rl->dumb || tgetnum("Co") < 8) ? ft_prompt_nocolor(prompt)
								: ft_strdup((prompt == NULL) ? "" : prompt);
	if (rl->dumb && !ftrl_prompt_isvalid_dumb_core(rl->prlen))
	{
		free(rl->prompt);
		rl->prompt = ft_strdup("ft_readline$ ");
		rl->prlen = ft_strlen(rl->prompt);
	}
}
