/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 02:01:46 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/27 20:54:25 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "ftrl_internal.h"

static void			get_winsize_hdl(int sigc)
{
	if (sigc != SIGWINCH)
		return ;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_ws);
}

inline static void	set_keys_movs(t_keys *keys, t_mov *movs, uint8_t dumb)
{
	char			**keysptr;
	unsigned int	idx;
	const char		*caps[8] = {"kl", "kr", "ku", "kd", "kh", "@7", "kD", "kE"};
	const char		*dfl[8] = {"\033[D", "\033[C", "\033[A", "\033[B",
							"\033[H", "\033[F", "\033[3~", "\025"};

	keysptr = (char**)keys;
	idx = 0;
	while (idx < sizeof(caps) / sizeof(caps[0]))
	{
		if (dumb
			|| !(keysptr[idx] = tgetstr((char*)((uintptr_t)caps[idx]), NULL)))
			keysptr[idx] = (char*)(uintptr_t)dfl[idx];
		idx++;
	}
	movs->leftm = tgetstr("le", NULL);
	movs->rightm = tgetstr("nd", NULL);
	movs->upm = tgetstr("up", NULL);
	movs->downm = tgetstr("do", NULL);
	movs->cecap = tgetstr("ce", NULL);
}

int					rl_deinit(t_readline *rl)
{
	if (!rl_set_term(YES))
		return (FALSE);
	outcap("ke");
	signal(SIGWINCH, SIG_DFL);
	ft_strdel(&rl->cpypste.dat);
	return (TRUE);
}

inline static void	rl_makesure_start(void)
{
	char	rbuff[8];
	char	*tmp;

	ft_putstr_fd("\033[6n", STDIN_FILENO);
	bzero(rbuff, sizeof(rbuff));
	if (read(STDIN_FILENO, rbuff, 7) < 1)
		return ;
	if (!(tmp = ft_strrchr(rbuff, ';')) || ft_atoi(tmp + 1) < 2)
		return ;
	outcap("mr");
	ft_putstr_fd("%\n", STDIN_FILENO);
	outcap("cr");
	outcap("me");
}

int					rl_init(t_readline *rl, const char *prompt, t_rl_opts *opts)
{
	char	*termenv;
	char	*pcstr;

	ft_bzero(rl, sizeof(t_readline));
	if (!(termenv = getenv("TERM")))
	{
		rl->dumb = TRUE;
		termenv = "dumb";
	}
	rl->prlen = ft_strlen_nocolor(prompt);
	rl->prompt = (rl->dumb) ? ft_prompt_nocolor(prompt) : prompt;
	rl->opts = opts;
	if (!(tgetent(NULL, termenv)))
		return (FALSE);
	if ((pcstr = tgetstr("pc", NULL)))
		PC = *pcstr;
	set_keys_movs(&rl->keys, &rl->movs, rl->dumb);
	if (!(rl_set_term(NO)))
		return (FALSE);
	rl_makesure_start();
	outcap("ks");
	get_winsize_hdl(SIGWINCH);
	signal(SIGWINCH, &get_winsize_hdl);
	return (TRUE);
}
