/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_cpypaste.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:03:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 18:29:57 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftrl_internal.h"

static t_keyact	rl_putmrk_key(char **line, t_readline *rl)
{
	static uint8_t	idx = 0;

	(void)line;
	if (!rl)
		return (kKeyFail);
	rl->cpypste.mkrs[idx] = rl->csr.pos;
	idx = !idx;
	return (kKeyOK);
}

static t_keyact	rl_cpy_key(char **line, t_readline *rl)
{
	if (!rl || !line)
		return (kKeyFail);
	ft_strdel(&rl->cpypste.dat);
	if (!(rl->cpypste.dat = ft_strsub(*line,
									rl->cpypste.mkrs[0],
									rl->cpypste.mkrs[1] - rl->cpypste.mkrs[0])))
		return (kKeyFail);
	return (kKeyOK);
}

static t_keyact	rl_paste_key(char **line, t_readline *rl)
{
	if (!rl || !line || !rl->cpypste.dat)
		return (kKeyFail);
	rl_line_add(line, rl->cpypste.dat, rl);
	return (kKeyOK);
}

t_keyact		cpypaste_keys(char **line, char *buff, t_readline *rl)
{
	unsigned int	idx;
	static t_keyact	(*f[7])(char**, t_readline*) =
	{&rl_putmrk_key, &rl_cpy_key, &rl_paste_key, NULL};
	const char		*keys[7] = {"\033[1;2D", "\033[1;2A", "\033[1;2B", NULL};

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
