/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_cpypaste.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:03:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/25 16:25:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ftrl_internal.h"

static t_keyact	rl_leftcpy_key(char **line, t_readline *rl)
{
	(void)line;
	if (!rl || rl->cpypste.mkrs[1] <= rl->cpypste.mkrs[0]
		|| rl->cpypste.mkrs[1] == 0)
		return (kKeyFail);
	rl_left_key(*line, rl);
	ft_putchar_fd((*line)[rl->csr.pos], STDIN_FILENO);
	rl->csr.pos++;
	rl_left_key(*line, rl);
	rl->cpypste.mkrs[1]--;
	return (kKeyOK);
}

static t_keyact	rl_rightcpy_key(char **line, t_readline *rl)
{
	static uint8_t	idx = 0;

	(void)line;
	if (!rl)
		return (kKeyFail);
	rl->cpypste.mkrs[idx] = rl->csr.pos + (idx == 1);
	idx = 1;
	outcap("mr");
	ft_putchar_fd((*line)[rl->csr.pos], STDIN_FILENO);
	outcap("me");
	rl->csr.pos++;
	return (kKeyOK);
}

static t_keyact	rl_cpy_key(char **line, t_readline *rl)
{
	char	*cpy;
	size_t	len;

	if (!rl || !line
		|| !(len = rl->cpypste.mkrs[1] - rl->cpypste.mkrs[0]))
		return (kKeyFail);
	if (!(cpy = ft_strsub(*line, rl->cpypste.mkrs[0], len)))
		return (kKeyFail);
	if (ft_strequ(rl->cpypste.dat, cpy))
	{
		go_to_pos(rl->cpypste.mkrs[1], rl->csr.pos, rl);
		rl_line_rm(line, len, rl);
	}
	else
	{
		go_to_pos(rl->cpypste.mkrs[0], rl->csr.pos, rl);
		ft_putstr_fd(cpy, STDIN_FILENO);
		go_to_pos(rl->csr.pos, rl->cpypste.mkrs[1], rl);
	}
	ft_strdel(&rl->cpypste.dat);
	rl->cpypste.dat = cpy;
	return (kKeyOK);
}

static t_keyact	rl_paste_key(char **line, t_readline *rl)
{
	if (!rl || !line || !rl->cpypste.dat)
		return (kKeyFail);
	rl_line_add(line, rl->cpypste.dat, rl);
	ft_bzero(&rl->cpypste.mkrs, sizeof(rl->cpypste.mkrs));
	return (kKeyOK);
}

t_keyact		cpypaste_keys(char **line, char *buff, t_readline *rl)
{
	unsigned int	idx;
	static t_keyact	(*f[5])(char**, t_readline*) =
	{&rl_leftcpy_key, &rl_rightcpy_key, &rl_cpy_key, &rl_paste_key, NULL};
	const char		*keys[5] = {"\033[1;2D", "\033[1;2C",
								"\033[1;2A", "\033[1;2B", NULL};

	if (!line || !*line || !buff)
		return (kKeyFail);
	idx = 0;
	while (f[idx] && keys[idx])
	{
		if (ft_strequ(keys[idx], buff)
			&& f[idx](line, rl) == kKeyFail)
			return (kKeyFail);
		idx++;
	}
	return (kKeyOK);
}
