/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 07:11:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 17:33:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftrl_internal.h"

t_rl_hist	*ft_histnew(char *line)
{
	t_rl_hist	*ret;

	if (!(ret = (t_rl_hist*)malloc(sizeof(t_rl_hist))))
		return (NULL);
	ft_bzero(ret, sizeof(t_rl_hist));
	if (!line)
		return (ret);
	if (!(ret->line = ft_strdup(line)))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

void		ft_histadd(t_rl_hist **headref, char *line)
{
	t_rl_hist	*new;

	if (!headref || !line || !(new = ft_histnew(line)))
		return ;
	if (!*headref)
		*headref = ft_histnew(NULL);
	if ((*headref)->next)
	{
		(*headref)->next->prev = new;
		new->next = (*headref)->next;
	}
	new->prev = *headref;
	(*headref)->next = new;
}

void		ft_histdelone(t_rl_hist **hist)
{
	t_rl_hist	*bak;

	if (!hist || !*hist)
		return ;
	bak = (*hist)->next;
	if ((*hist)->prev)
		(*hist)->prev->next = (*hist)->next;
	if ((*hist)->line)
		free((*hist)->line);
	free(*hist);
	*hist = bak;
}

void		ft_histdel(t_rl_hist **headref)
{
	if (!headref)
		return ;
	while (*headref)
	{
		ft_histdelone(headref);
		if (*headref)
			(*headref)->prev = NULL;
	}
	*headref = NULL;
}
