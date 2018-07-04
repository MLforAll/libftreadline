/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/04 18:49:52 by kdumarai         ###   ########.fr       */
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
	unsigned int	idx;
	static t_keyact	(*f[])(t_readline*) =
	{&rl_right_key, &rl_left_key, &rl_home_key, &rl_end_key,
	&rl_movl_key, &rl_movr_key, &rl_leftcpy_key, &rl_rightcpy_key,
	&rl_cpy_key, &rl_paste_key, NULL};
	const char		*keys[] = {rl->keys.rightk, rl->keys.leftk,
								rl->keys.homek, rl->keys.endk,
								ESC_MOVL, ESC_MOVR, "\033[1;2D", "\033[1;2C",
								"\033[1;2A", "\033[1;2B", NULL};

	if (!rl || !buff)
		return (kKeyFail);
	idx = 0;
	while (f[idx] && keys[idx])
	{
		if (ft_strequ(keys[idx], buff)
			&& f[idx](rl) == kKeyFail)
			return (kKeyFail);
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
	char			buff[RL_READBUFFSIZE + 1];

	ft_putstrsec_fd(rl->prompt, rl->opts->outfd);
	ft_putstrsec_fd(rl->line, STDIN_FILENO);
	ft_bzero(buff, sizeof(buff));
	while (rl->line && read(STDIN_FILENO, buff, RL_READBUFFSIZE) > 0)
	{
		if (ft_strequ(buff, "\n") || *buff == 3)
			break ;
		if ((nav_keys(buff, rl) == kKeyFail
			|| hist_nav(buff, rl, hist) == kKeyFail
			|| edit_keys(buff, rl) == kKeyFail) && rl->opts->bell && !rl->dumb)
			(void)outcap("bl");
		ft_bzero(buff, sizeof(buff));
	}
	print_end_newlines(rl);
}

char			*ft_readline(const char *prompt,
							t_rl_opts *opts, t_dlist *hist)
{
	t_readline		rl;
	t_readline		*bak;

	if (!rl_init(&rl, prompt, opts) || (bak = rl_latest_session(NO, NULL)))
		return (NULL);
	(void)rl_latest_session(YES, &rl);
	if (!rl_linebuff_create(&rl))
		return (NULL);
	while (TRUE)
	{
		ft_readline_core(&rl, &hist);
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
