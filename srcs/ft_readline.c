/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/15 19:39:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

static void		print_end_newlines(t_readline *rl)
{
	t_point			coords;
	t_point			maxc;
	size_t			times;
	char			*nlb;

	if (!rl)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		return ;
	}
	get_line_info(&coords, rl);
	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	times = maxc.y - coords.y + 1;
	if (!(nlb = (char*)malloc(sizeof(char) * (times + 1))))
		return ;
	(void)ft_memset(nlb, '\n', times);
	nlb[times] = '\0';
	ft_putstr_fd(nlb, STDIN_FILENO);
	free(nlb);
}

static t_keyact	nav_keys(char *buff, t_readline *rl)
{
	t_keyact		status;
	unsigned int	idx;
	static t_keyact	(*f[])(t_readline*) =
	{&rl_leftcpy_key, &rl_rightcpy_key, &rl_cpy_key, &rl_paste_key,
	&rl_right_key, &rl_left_key, &rl_home_key, &rl_end_key, &rl_movl_key,
	&rl_movr_key, NULL};
	const char		*keys[] = {"\033[1;2D", "\033[1;2C", "\033[1;2A",
								"\033[1;2B", rl->keys.rightk, rl->keys.leftk,
								rl->keys.homek, rl->keys.endk, ESC_MOVL,
								ESC_MOVR, NULL};

	if (!rl || !buff)
		return (kKeyFail);
	idx = 0;
	while (f[idx] && keys[idx])
	{
		if (ft_strequ(keys[idx], buff))
		{
			(idx > 3) ? check_selection(rl) : 0;
			if ((status = f[idx](rl)) >= kKeyFail)
				return (status);
		}
		idx++;
	}
	return (kKeyOK);
}

static t_keyact	edit_keys(char *buff, t_readline *rl)
{
	t_keyact	tmp;

	if (!rl || !buff)
		return (kKeyNone);
	if (*buff == 4 || *buff == 3)
	{
		rl->bufflen = 0;
		ft_strdel(&rl->line);
	}
	if (*buff == 3 && !rl_linebuff_create(rl))
		return (kKeyFatal);
	if (*buff == 4 || *buff == 3)
		return (kKeyOK);
	if (ft_strequ(buff, "\025"))
		return (rl_clear_line(rl));
	if (ft_strequ(buff, "\t"))
		return (rl_acroutine(rl));
	if ((tmp = rl_input_rm_text(buff, rl)) != kKeyNone)
		return (tmp);
	if ((tmp = rl_input_add_text(buff, rl)) != kKeyNone)
		return (tmp);
	return (kKeyNone);
}

static void		ft_readline_core(t_readline *rl, t_dlist **hist)
{
	t_keyact		status;
	char			buff[RL_READBUFFSIZE + 1];

	ft_putstr_fd(rl->prompt, rl->opts->outfd);
	ft_putstr_fd(rl->line, STDIN_FILENO);
	(rl->csr.pos != rl->csr.max) ? go_to_pos(rl->csr.pos, rl->csr.max, rl) : 0;
	while (rl->line)
	{
		ft_bzero(buff, sizeof(buff));
		if (read(STDIN_FILENO, buff, RL_READBUFFSIZE) < 1
			|| ft_strequ(buff, "\n") || *buff == 3)
			break ;
		if (((status = nav_keys(buff, rl)) >= kKeyFail
			|| (status = hist_nav(buff, rl, hist)) >= kKeyFail
			|| (status = edit_keys(buff, rl)) >= kKeyFail))
		{
			if (status == kKeyFail && rl->opts->bell && !rl->dumb)
				(void)outcap("bl");
			else if (status == kKeyFatal)
			{
				ft_putendl("\nft_readline(): Fatal error");
				break ;
			}
		}
	}
}

char			*ft_readline(const char *prompt,
							t_rl_opts *opts, t_dlist *hist)
{
	t_readline		rl;
	t_readline		*bak;

	if ((bak = rl_latest_session(NO, NULL)) || !rl_init(&rl, prompt, opts))
		return (NULL);
	(void)rl_latest_session(YES, &rl);
	while (TRUE)
	{
		ft_readline_core(&rl, &hist);
		check_selection(&rl);
		print_end_newlines(&rl);
		if (rl.quit.reason != kAbortReload)
			break ;
		if (rl.quit.func)
		{
			(rl.quit.func)(rl.quit.func_data);
			(rl.quit.free_func)(rl.quit.func_data);
		}
		(void)rl_set_timeout(NO, 0);
		ft_bzero(&rl.quit, sizeof(t_quit));
	}
	(void)rl_deinit(&rl);
	(void)rl_latest_session(YES, bak);
	return (rl.line);
}
