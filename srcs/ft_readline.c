/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 18:25:51 by kdumarai         ###   ########.fr       */
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
		outcap("cr");
		outcapstr(rl->movs.downm);
		return ;
	}
	get_line_info(&coords, rl);
	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	times = maxc.y - coords.y + 1;
	if (!(nlb = (char*)malloc(sizeof(char) * (times + 1))))
		return ;
	ft_memset(nlb, '\n', times);
	nlb[times] = '\0';
	outcap("cr");
	ft_putstr_fd(nlb, STDIN_FILENO);
	free(nlb);
}

static t_keyact	hist_nav(char **line, char *buff,
						t_readline *rl, t_rl_hist **hist)
{
	t_point		maxc;
	t_keyact	retk;

	if ((retk = rl_history_keys(buff, rl, hist)) != kKeyOK)
		return (retk);
	free(*line);
	if ((*hist)->line)
	{
		*line = ft_strdup((*hist)->line);
		rl->bufflen = ft_strlen(*line);
	}
	else
		rl->bufflen = rl_linebuff_create(line);
	rl->csr.max = ft_strlen(*line);
	rl->csr.pos = rl->csr.max;
	get_line_info_for_pos(&maxc, rl->csr.max, rl);
	go_to_pos(0, rl->csr.pos, rl);
	outcap("cr");
	outcap_arg_fb(tgetstr("DL", NULL), tgetstr("dl", NULL), maxc.y, maxc.y);
	ft_putstr_fd(rl->prompt, rl->opts->outfd);
	ft_putstr_fd(*line, STDIN_FILENO);
	return (kKeyOK);
}

static t_keyact	nav_keys(char **line, char *buff, t_readline *rl)
{
	unsigned int	idx;
	static t_keyact	(*f[7])(char*, t_readline*) =
	{&rl_right_key, &rl_left_key, &rl_home_key, &rl_end_key,
	&rl_movl_key, &rl_movr_key, NULL};
	const char		*keys[7] = {rl->keys.rightk, rl->keys.leftk,
								rl->keys.homek, rl->keys.endk,
								ESC_MOVL, ESC_MOVR, NULL};

	if (!line || !*line || !buff)
		return (kKeyFail);
	idx = 0;
	while (f[idx] && keys[idx])
	{
		if (ft_strequ(keys[idx], buff)
			&& f[idx](*line, rl) == kKeyFail)
			return (kKeyFail);
		idx++;
	}
	return (kKeyOK);
}

static t_keyact	edit_keys(char **line, char *buff, t_readline *rl)
{
	if (!line || !*line || !buff || !rl)
		return (kKeyNone);
	if (rl_input_add_text(line, buff, rl))
		return (kKeyOK);
	if (rl_input_rm_text(line, buff, rl) == 1)
		return (kKeyOK);
	if (*buff == 4 || *buff == 3)
	{
		rl->bufflen = 0;
		ft_strdel(line);
	}
	if (*buff == 3)
		rl->bufflen = rl_linebuff_create(line);
	if (*buff == 4 || *buff == 3)
		return (FALSE);
	if (ft_strequ(buff, "\025"))
		rl_clear_line(line, rl);
	if (ft_strequ(buff, "\t"))
		rl_acroutine(line, rl);
	return (kKeyOK);
}

char			*ft_readline(const char *prompt,
							t_rl_opts *opts, t_rl_hist *hist)
{
	t_readline		rl;
	char			buff[RL_READBUFFSIZE + 1];
	char			*ret;

	if (!rl_init(&rl, prompt, opts))
		return (NULL);
	if (prompt)
		ft_putstr_fd(prompt, rl.opts->outfd);
	ft_bzero(buff, sizeof(buff));
	rl.bufflen = rl_linebuff_create(&ret);
	while (ret && read(STDIN_FILENO, buff, RL_READBUFFSIZE) > 0)
	{
		if ((nav_keys(&ret, buff, &rl) == kKeyFail
			|| hist_nav(&ret, buff, &rl, &hist) == kKeyFail
			|| edit_keys(&ret, buff, &rl) == kKeyFail
			|| cpypaste_keys(&ret, buff, &rl)) && opts->bell)
			outcap("bl");
		if (ft_strequ(buff, "\n"))
			break ;
		ft_bzero(buff, sizeof(buff));
	}
	print_end_newlines(&rl);
	rl_deinit(&rl);
	return (ret);
}
