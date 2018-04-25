/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_acshowres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:47:08 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 02:31:58 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ftrl_internal.h"

static void	ft_putlst_custom(t_list *lst)
{
	while (lst)
	{
		if (lst->content)
		{
			ft_putstr_fd(lst->content, STDIN_FILENO);
			ft_putstr_fd("\r\n", STDIN_FILENO);
		}
		lst = lst->next;
	}
}

char		*show_ac_result_bltn(t_list **res)
{
	ft_putstr_fd("\r\n", STDIN_FILENO);
	ft_lstmergesort(res, &ft_lstsortalpha, NO);
	ft_putlst_custom(*res);
	return (NULL);
}
