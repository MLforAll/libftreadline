/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_linebuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 22:59:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 17:44:06 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

static int	buffrealloc(char **line, size_t size)
{
	char	*newline;

	if (!(newline = ft_strnew(size)))
		return (FALSE);
	ft_strcpy(newline, *line);
	free(*line);
	*line = newline;
	return (TRUE);
}

int			rl_linebuff_add(char **line,
							char *add,
							size_t addlen,
							t_readline *rl)
{
	char	backup[512];
	size_t	goal;

	if (rl->csr.max + addlen > rl->bufflen)
	{
		goal = rl->bufflen + addlen;
		rl->bufflen += (rl->bufflen == 0);
		while (rl->bufflen < goal)
			rl->bufflen *= 2;
		buffrealloc(line, rl->bufflen);
	}
	if (rl->csr.pos >= rl->csr.max)
		ft_strcpy(*line + rl->csr.max, add);
	else
	{
		ft_strcpy(backup, *line + rl->csr.pos);
		ft_strcpy(*line + rl->csr.pos, add);
		ft_strcpy(*line + rl->csr.pos + addlen, backup);
	}
	return (TRUE);
}

int			rl_linebuff_rm(char **line, size_t len, t_readline *rl)
{
	if (rl->csr.max <= rl->bufflen / 2 && rl->csr.max >= DFL_LINEBUFFSIZE)
		buffrealloc(line, rl->bufflen /= 2);
	ft_memset(*line + rl->csr.pos, '\0', len);
	if (rl->csr.pos + len < rl->csr.max)
		ft_strcpy(*line + rl->csr.pos, *line + rl->csr.pos + len);
	return (TRUE);
}

size_t		rl_linebuff_create(char **line)
{
	if (!(*line = ft_strnew(DFL_LINEBUFFSIZE)))
		return (0);
	return (DFL_LINEBUFFSIZE);
}
