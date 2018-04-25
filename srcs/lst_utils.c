/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 01:47:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 15:48:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftrl_internal.h"

void	free_tlist(void *content, size_t size)
{
	(void)size;
	free(content);
}

int		ft_lstsortalpha(t_list *a, t_list *b)
{
	if (!a || !b || !a->content || !b->content)
		return (FALSE);
	if (ft_strcmp(a->content, b->content) > 0)
		return (TRUE);
	return (FALSE);
}
