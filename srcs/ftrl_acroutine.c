/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_acroutine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:12:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/21 18:29:55 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "ftrl_internal.h"

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
		return ((rl->opts->ac_get_result)(line, rl->csr));
	return (get_ac_result_bltn(line, rl->csr));
}

t_keyact				rl_acroutine(char **line, t_readline *rl)
{
	t_list			*res;
	char			*diff;
	char			*base;

	if (!(res = get_ac_result(*line, rl)))
		return (kKeyFail);
	base = (res && !res->next) ? res->content : get_highest_common(res);
	if (base && (diff = ft_strdiff(base, fname)) && *diff)
		rl_line_add(line, diff, rl);
	if (res && base && base == res->content && res->content_size != DT_LNK)
		rl_line_add(line, (res->content_size == DT_DIR) ? "/" : " ", rl);
	if (base && base != res->content)
		ft_strdel(&base);
	ft_lstdel(&res, &free_tlist);
	return (kKeyOK);
}
