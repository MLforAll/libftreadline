/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_acshowres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:47:08 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/21 22:24:56 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

void			show_choices(t_list **res, char *line, t_readline *rl)
{
	ft_putchar_fd('\n', STDIN_FILENO);
	ft_lstmergesort(res, &ft_lstsortalpha, NO);
	ft_putlst_fd(*res, STDIN_FILENO);
	ft_putstr_fd(rl->prompt, STDIN_FILENO);
	ft_putstr_fd(line, STDIN_FILENO);
}
