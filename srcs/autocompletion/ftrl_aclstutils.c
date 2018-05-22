/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 01:47:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/22 14:33:06 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftrl_internal.h"

void	ft_acres_free(void *content, size_t size)
{
	if (!content || size == 0)
		return ;
	ft_strdel(&((t_acres*)content)->visible_str);
	ft_strdel(&((t_acres*)content)->str);
	free(content);
}

int		ft_acres_sortalpha(t_list *a, t_list *b)
{
	if (!a || !b
		|| !a->content || !b->content
		|| !((t_acres*)a->content)->visible_str
		|| !((t_acres*)b->content)->visible_str)
		return (FALSE);
	if (ft_strcmp(((t_acres*)a->content)->visible_str,
		((t_acres*)b->content)->visible_str) > 0)
		return (TRUE);
	return (FALSE);
}
