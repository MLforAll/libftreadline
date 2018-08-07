/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_csrkeys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 09:00:17 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/07 18:10:00 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ftrl_internal.h"

t_keyact	rl_right_key(t_readline *rl)
{
	t_point		coords;
	t_point		gtc;

	if (rl->csr.pos >= rl->csr.max)
		return (kKeyFail);
	get_line_info(&coords, rl);
	rl->csr.pos++;
	get_line_info(&gtc, rl);
	go_to_point(rl->csr.pos - 1, &gtc, &coords, rl);
	return (kKeyOK);
}

t_keyact	rl_left_key(t_readline *rl)
{
	t_point		coords;
	t_point		gtc;

	if (rl->csr.pos <= 0)
		return (kKeyFail);
	get_line_info(&coords, rl);
	get_line_info_for_pos(&gtc, rl->csr.pos - 1, rl);
	if (!check_height(&gtc, rl))
		return (kKeyFail);
	go_to_point(rl->csr.pos, &gtc, &coords, rl);
	rl->csr.pos--;
	return (kKeyOK);
}

t_keyact	rl_home_key(t_readline *rl)
{
	t_point	coords;
	t_point	homec;

	get_line_info(&coords, rl);
	get_line_info_for_pos(&homec, 0, rl);
	if (rl->csr.pos <= 0 || !check_height(&homec, rl))
		return (kKeyFail);
	go_to_point(rl->csr.pos, &homec, &coords, rl);
	rl->csr.pos = 0;
	return (kKeyOK);
}

t_keyact	rl_end_key(t_readline *rl)
{
	t_point	coords;
	t_point	maxc;

	get_line_info(&coords, rl);
	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	if (rl->csr.pos >= rl->csr.max)
		return (kKeyFail);
	go_to_point(rl->csr.pos, &maxc, &coords, rl);
	rl->csr.pos = rl->csr.max;
	return (kKeyOK);
}
