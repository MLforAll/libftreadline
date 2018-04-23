/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_linekeys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/23 19:48:13 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

int			rl_input_add_text(char *buff, char **line, t_readline *rl)
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

int			rl_input_rm_text(char **line, char *buff, t_readline *rl)
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
