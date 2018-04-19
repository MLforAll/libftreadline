/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/20 00:05:31 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

void	rl_line_rm(char **line, size_t len, t_readline *rl)
{
	char			*tmp;
	t_point			coords;
	t_point			csrm;

	if (!line || len == 0 || !rl)
		return ;
	get_line_info(&coords, rl);
	rl->csr.pos -= len;
	get_line_info(&csrm, rl);
	go_to_point(&csrm, &coords, rl);
	outcap("ce");
	outcap("sc");
	if (rl->csr.pos + len < rl->csr.max)
		ft_putstr_fd(*line + rl->csr.pos + len, STDIN_FILENO);
	outcap("rc");
	tmp = *line;
	*line = ft_strsub(tmp, 0, rl->csr.pos);
	if (rl->csr.pos + len < rl->csr.max)
		ft_stradd(line, tmp + rl->csr.pos + len);
	ft_strdel(&tmp);
	rl->csr.max -= len;
}

void	rl_line_add(char **line, char *add, t_readline *rl)
{
	char			*tmp;
	size_t			len;
	t_point			coords;

	if (!line || !add || !rl || !(len = ft_strlen(add)))
		return ;
	get_line_info(&coords, rl);
	outcap("ce");
	ft_putstr_fd(add, STDIN_FILENO);
	if (coords.x + 1 >= rl->ws.ws_col)
	{
		outcap("cr");
		outcapstr(rl->movs.downm);
	}
	if (rl->csr.pos < rl->csr.max)
	{
		outcap("sc");
		ft_putstr_fd(*line + rl->csr.pos, STDIN_FILENO);
		outcap("rc");
	}
	tmp = *line;
	*line = ft_strsub(tmp, 0, rl->csr.pos);
	ft_stradd(line, add);
	if (rl->csr.pos < rl->csr.max)
		ft_stradd(line, tmp + rl->csr.pos);
	ft_strdel(&tmp);
	rl->csr.max += len;
	rl->csr.pos += len;
}

int		rl_input_add_text(char *buff, char **line, t_readline *rl)
{
	char			add[5];
	unsigned int	idx;

	if (*buff == 27)
		return (0);
	idx = 0;
	ft_bzero(add, sizeof(add));
	while (*buff)
	{
		if (ft_isprint(*buff))
		{
			add[idx] = *buff;
			idx++;
		}
		buff++;
	}
	rl_line_add(line, add, rl);
	return ((idx > 0));
}

int		rl_input_rm_text(char **line, char *buff, t_readline *rl)
{
	int				keys[2];

	keys[0] = (*buff == 127);
	keys[1] = (ft_strequ(buff, rl->keys.delk));
	if (!keys[0] && !keys[1])
		return (0);
	if (keys[0] && rl->csr.pos > 0)
	{
		rl_line_rm(line, 1, rl);
		return (1);
	}
	else if (keys[1] && rl->csr.pos < rl->csr.max)
	{
		outcapstr(rl->movs.rightm);
		rl->csr.pos++;
		rl_line_rm(line, 1, rl);
		return (1);
	}
	return (-1);
}
