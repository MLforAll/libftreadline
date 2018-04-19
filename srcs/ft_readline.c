/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:45:50 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/19 02:09:11 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ftrl_internal.h"

/*static void		act_keys(char **line, char *buff, t_readline *rl)
{
	int				rval;
	unsigned int	idx;
	static t_keyact	(*f[3])(char*, t_readline*) =
	{&rl_csr_keys, &rl_home_end_keys, NULL};

	if (!line || !*line || !buff)
		return ;
	if ((rval = rl_history_keys(&rl->opts->hist, buff, line)) > 0 && *line)
	{
		outcap("cr");
		outcap("ce");
		ft_putstr_fd(rl->prompt, rl->opts->outfd);
		ft_putstr_fd(*line, STDIN_FILENO);
		rl->csr.max = ft_strlen(*line);
		rl->csr.pos = rl->csr.max;
	}
	idx = -1;
	while (f[++idx])
	{
		if ((rval = f[idx](buff, rl)) > 0)
			return ;
	}
}*/

static void		act_keys(char **line, char *buff, t_readline *rl)
{
	unsigned int	idx;
	static t_keyact	(*f[7])(char*, t_readline*) =
	{&rl_right_key, &rl_left_key, &rl_home_key, &rl_end_key,
	&rl_movl_key, &rl_movr_key, NULL};
	const char		*keys[7] = {rl->keys.rightk, rl->keys.leftk,
								rl->keys.homek, rl->keys.endk,
								ESC_MOVL, ESC_MOVR, NULL};

	if (!line || !*line || !buff)
		return ;
	idx = 0;
	while (f[idx] && keys[idx])
	{
		if (ft_strequ(keys[idx], buff)
			&& f[idx](*line, rl) == kKeyFail && rl->opts->bell)
			outcap("bl");
		idx++;
	}
}

static int		act_on_buff(char *buff, char **line, t_readline *rl)
{
	int				retval;

	if (!line || !*line || !buff || !rl)
		return (FALSE);
	if (rl_input_add_text(buff, line, rl))
		return (TRUE);
	if ((retval = rl_input_rm_text(line, buff, rl)) == 1)
		return (TRUE);
	if (*buff == 4 || *buff == 3)
		ft_strdel(line);
	if (*buff == 3)
		*line = ft_strnew(0);
	if (*buff == 4 || *buff == 3)
		return (FALSE);
	if (*buff == 21)
	{
		outcap("cr");
		outcap("ce");
		free(*line);
		*line = ft_strnew(0);
		ft_putstr_fd(rl->prompt, rl->opts->outfd);
		ft_bzero(&rl->csr, sizeof(t_cursor));
	}
	return (TRUE);
}

static void		print_end_newlines(char *line, char *buff, t_readline *rl)
{
	struct winsize	ws;
	size_t			times;
	size_t			linelen;
	char			*nlb;

	if (!line || !rl || rl->csr.pos == rl->csr.max)
	{
		outcap("cr");
		outcapstr(rl->movs.downm);
		return ;
	}
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		return ;
	linelen = ft_strlen(line) + rl->prlen;
	times = linelen / ws.ws_col + (linelen % ws.ws_col != 0);
	times -= rl->csr.pos / ws.ws_col;
	times = (times <= 0) ? 1 : times;
	times += (buff && *buff != '\n');
	if (!(nlb = (char*)malloc(sizeof(char) * (times + 1))))
		return ;
	ft_memset(nlb, '\n', times);
	nlb[times] = '\0';
	outcap("cr");
	ft_putstr_fd(nlb, STDIN_FILENO);
	free(nlb);
}

char			*ft_readline(const char *prompt, t_rl_opts *opts)
{
	char			buff[5];
	t_readline		rl;
	char			*ret;

	if (!rl_init(&rl, prompt, opts) || !rl_set_term(&rl, NO, prompt))
		return (NULL);
	ft_bzero(buff, sizeof(buff));
	ret = ft_strnew(0);
	while (ret && read(STDIN_FILENO, buff, 4) > 0)
	{
		act_keys(&ret, buff, &rl);
		if (ft_strequ(buff, "\n") || !act_on_buff(buff, &ret, &rl))
			break ;
		ft_bzero(buff, sizeof(buff));
	}
	print_end_newlines(ret, buff, &rl);
	rl_set_term(&rl, YES, prompt);
	return (ret);
}
