/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_acroutine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:12:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/24 13:02:23 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "ftrl_internal.h"

static void				free_tlist(void *content, size_t size)
{
	(void)size;
	free(content);
}

inline static char		*get_highest_common(t_list *lst)
{
	int				first;
	size_t			len;
	size_t			new;

	if (!lst)
		return (NULL);
	first = TRUE;
	len = 0;
	while (lst->next)
	{
		new = 0;
		new = ft_strcmpi(lst->content, lst->next->content);
		len = (new < len || first) ? new : len;
		if (first)
			first = FALSE;
		lst = lst->next;
	}
	return (len == 0 ? NULL : ft_strsub(lst->content, 0, len));
}

inline static t_list	*get_ac_result(char *line, t_readline *rl)
{
	if (rl->opts->ac_get_result)
		return ((rl->opts->ac_get_result)(line, &rl->csr));
	return (get_ac_result_bltn(line, &rl->csr));
}

static char				*get_diff(char *line, char *ch, unsigned int pos)
{
	char			*res;

	while (pos--)
	{
		if ((res = ft_strstart(ch, line + pos)))
			return (res);
	}
	return (NULL);
}

t_keyact				rl_acroutine(char **line, t_readline *rl)
{
	t_list			*res;
	char			*diff;
	char			*base;

	if (!(res = get_ac_result(*line, rl)))
		return (kKeyFail);
	base = (res && !res->next) ? res->content : get_highest_common(res);
	if (base && (diff = get_diff(*line, base, rl->csr.pos)) && *diff)
		rl_line_add(line, diff, rl);
	if (base && base != res->content)
		ft_strdel(&base);
	ft_lstdel(&res, &free_tlist);
	return (kKeyOK);
}