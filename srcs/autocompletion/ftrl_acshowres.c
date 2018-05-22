/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_acshowres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:47:08 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/22 14:56:27 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ftrl_internal.h"

static void	ft_putlst_custom(t_list *lst)
{
	char	*visible;

	while (lst)
	{
		visible = (((t_acres*)lst->content)->visible_str)
				? ((t_acres*)lst->content)->visible_str
				: ((t_acres*)lst->content)->str;
		ft_putstr_fd(visible, STDIN_FILENO);
		ft_putstr_fd("\r\n", STDIN_FILENO);
		lst = lst->next;
	}
}

static int	lot_of_ch(t_list *res, struct winsize *ws)
{
	char	buff[23];
	size_t	len;

	if ((len = ft_lstlen(res)) < ws->ws_col / 4 * 3)
		return (TRUE);
	ft_strcpy(buff, "Show all ");
	if (len < 10000)
		ft_nbrcat(buff, len);
	ft_strcat(buff, " results");
	return (ft_confirm(buff, STDIN_FILENO, kDefaultNo));
}

char		*show_ac_result_bltn(t_list **res, struct winsize *ws)
{
	if (!res || !*res)
		return (NULL);
	ft_putstr_fd("\r\n", STDIN_FILENO);
	if (!lot_of_ch(*res, ws))
		return (NULL);
	ft_lstmergesort(res, &ft_acres_sortalpha, NO);
	ft_putlst_custom(*res);
	return (NULL);
}
