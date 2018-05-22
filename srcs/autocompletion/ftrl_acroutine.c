/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_acroutine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:12:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/22 15:22:00 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "ftrl_internal.h"

inline static char		*get_highest_common(t_list *lst)
{
	uint8_t			first;
	size_t			len;
	size_t			new;

	if (!lst)
		return (NULL);
	first = TRUE;
	len = 0;
	while (lst->next)
	{
		new = ft_strcmpi(((t_acres*)lst->content)->str,
			((t_acres*)lst->next->content)->str);
		len = (new < len || first) ? new : len;
		if (first)
			first = FALSE;
		lst = lst->next;
	}
	return (len == 0 ? NULL : ft_strsub(((t_acres*)lst->content)->str, 0, len));
}

inline static t_list	*get_ac_result(char *line, t_readline *rl)
{
	if (rl->opts->ac_get_result)
		return ((rl->opts->ac_get_result)(line, &rl->csr));
	return (get_ac_result_bltn(line, &rl->csr));
}

inline static char		*show_ac_result(char *line, t_list **res,
										t_readline *rl)
{
	char	*ret;

	if (rl->opts->ac_get_result)
		ret = (rl->opts->ac_show_result)(res, &rl->ws);
	else
		ret = show_ac_result_bltn(res, &rl->ws);
	ft_putstr_fd(rl->prompt, rl->opts->outfd);
	ft_putstr_fd(line, STDIN_FILENO);
	go_to_pos(rl->csr.pos, rl->csr.max, rl);
	return (ret);
}

static char				*get_diff(char *line, char *ch, unsigned int pos)
{
	char			*res;
	unsigned int	idx;

	if (!ch || !line)
		return (NULL);
	while (pos--)
	{
		if (*ch != line[pos])
			continue ;
		res = ch;
		idx = pos;
		while (*res && line[idx] && *res == line[idx++])
			res++;
		return ((!res || !*res) ? NULL : res);
	}
	return (NULL);
}

t_keyact				rl_acroutine(char **line, t_readline *rl)
{
	t_list		*res;
	char		*diff;
	char		*base;

	if (!(res = get_ac_result(*line, rl)))
		return (kKeyFail);
	base = (res && !res->next)
		? ((t_acres*)res->content)->str : get_highest_common(res);
	if (!(diff = get_diff(*line, base, rl->csr.pos)))
	{
		if (base != ((t_acres*)res->content)->str)
			ft_strdel(&base);
		base = show_ac_result(*line, &res, rl);
		diff = get_diff(*line, base, rl->csr.pos);
	}
	if (diff)
		rl_line_add(line, diff, rl);
	if (base != ((t_acres*)res->content)->str)
		ft_strdel(&base);
	ft_lstdel(&res, &ft_acres_free);
	return (kKeyOK);
}
