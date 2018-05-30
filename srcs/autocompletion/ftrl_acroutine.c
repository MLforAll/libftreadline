/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_acroutine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:12:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/30 19:56:06 by kdumarai         ###   ########.fr       */
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

inline static t_list	*get_ac_result(t_readline *rl)
{
	if (rl->opts->ac_get_result)
		return ((rl->opts->ac_get_result)(rl->line, &rl->csr));
	return (get_ac_result_bltn(rl->line, &rl->csr));
}

inline static char		*show_ac_result(t_list **res, t_readline *rl)
{
	char	*ret;

	outcap("ke");
	rl_set_opost(TRUE);
	if (rl->opts->ac_show_result)
		ret = (rl->opts->ac_show_result)(res);
	else
		ret = show_ac_result_bltn(res);
	ft_putstr_fd(rl->prompt, rl->opts->outfd);
	ft_putstr_fd(rl->line, STDIN_FILENO);
	rl_set_opost(FALSE);
	outcap("ks");
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

t_keyact				rl_acroutine(t_readline *rl)
{
	t_list		*res;
	char		*diff;
	char		*base;
	uint8_t		basemalloc;

	if (!(res = get_ac_result(rl)))
		return (kKeyFail);
	base = (res && !res->next)
		? ((t_acres*)res->content)->str : get_highest_common(res);
	basemalloc = (base != ((t_acres*)res->content)->str);
	if (!(diff = get_diff(rl->line, base, rl->csr.pos)))
	{
		if (basemalloc)
			ft_strdel(&base);
		base = show_ac_result(&res, rl);
		basemalloc = FALSE;
		diff = get_diff(rl->line, base, rl->csr.pos);
	}
	if (diff)
		rl_line_add(diff, rl);
	if (basemalloc)
		ft_strdel(&base);
	ft_lstdel(&res, &ft_acres_free);
	return (kKeyOK);
}
