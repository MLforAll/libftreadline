/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_linebuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 22:59:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/28 03:25:25 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

static int		buffrealloc(char **line, size_t size)
{
	char	*newline;

	if (!(newline = ft_strnew(size)))
		return (FALSE);
	(void)ft_strcpy(newline, *line);
	free(*line);
	*line = newline;
	return (TRUE);
}

static t_uint8	insert_to_buff(char *add, size_t addlen, t_readline *rl)
{
	char	backup_static[512];
	char	*backup_dyn;
	char	*backup_ptr;

	backup_dyn = NULL;
	if (rl->csr.max - rl->csr.pos > sizeof(backup_static) / sizeof(char) - 1)
	{
		if (!(backup_dyn = ft_strnew(rl->csr.max - rl->csr.pos)))
			return (FALSE);
		backup_ptr = backup_dyn;
	}
	else
		backup_ptr = backup_static;
	(void)ft_strcpy(backup_ptr, rl->line + rl->csr.pos);
	(void)ft_strcpy(rl->line + rl->csr.pos, add);
	(void)ft_strcpy(rl->line + rl->csr.pos + addlen, backup_ptr);
	free(backup_dyn);
	return (TRUE);
}

int				rl_linebuff_add(char *add, size_t addlen, t_readline *rl)
{
	size_t	goal;

	if (rl->csr.max + addlen > rl->bufflen)
	{
		goal = rl->bufflen + addlen;
		rl->bufflen += (rl->bufflen == 0);
		while (rl->bufflen < goal)
			rl->bufflen *= 2;
		(void)buffrealloc(&rl->line, rl->bufflen);
	}
	if (rl->csr.pos >= rl->csr.max)
		(void)ft_strcpy(rl->line + rl->csr.max, add);
	else if (insert_to_buff(add, addlen, rl))
		return (FALSE);
	return (TRUE);
}

int				rl_linebuff_rm(size_t len, t_readline *rl)
{
	if (rl->csr.max <= rl->bufflen / 2 && rl->csr.max >= DFL_LINEBUFFSIZE)
		(void)buffrealloc(&rl->line, rl->bufflen /= 2);
	ft_memset(rl->line + rl->csr.pos, '\0', len);
	if (rl->csr.pos + len < rl->csr.max)
		(void)ft_strcpy(rl->line + rl->csr.pos, rl->line + rl->csr.pos + len);
	return (TRUE);
}

size_t			rl_linebuff_create(char **line)
{
	if (!(*line = ft_strnew(DFL_LINEBUFFSIZE)))
		return (0);
	return (DFL_LINEBUFFSIZE);
}
