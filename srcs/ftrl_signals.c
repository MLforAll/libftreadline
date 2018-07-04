/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 17:21:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/04 18:13:15 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "ftrl_internal.h"

static void	(*sigorigs[32])(int);

static void	rl_generic_sig_hdl(int sigc)
{
	t_readline	*session;

	if (sigc == SIGINT || sigc == SIGTSTP
		|| !(session = rl_latest_session(NO, NULL)))
		return ;
	(void)rl_deinit(session);
	ft_putchar('\n');
	if (sigorigs[sigc] == SIG_DFL || sigorigs[sigc] == SIG_IGN)
	{
		(void)signal(sigc, sigorigs[sigc]);
		raise(sigc);
		return ;
	}
	(sigorigs[sigc])(sigc);
}

static void	get_winsize_hdl(int sigc)
{
	if (sigc != SIGWINCH)
		return ;
	(void)ioctl(STDIN_FILENO, TIOCGWINSZ, &g_ws);
}

void		set_signals(void)
{
	int		sig;

	sig = 0;
	while (++sig < 32)
	{
		if (sig == SIGURG || sig == SIGCONT || sig == SIGCHLD
			|| sig == SIGIO || sig == SIGWINCH || sig == SIGINFO)
			sigorigs[sig] = (void (*)(int))-1;
		else
			sigorigs[sig] = signal(sig, &rl_generic_sig_hdl);
	}
	get_winsize_hdl(SIGWINCH);
	sigorigs[SIGWINCH] = signal(SIGWINCH, &get_winsize_hdl);
}

void		restore_signals(void)
{
	int		sig;

	sig = 0;
	while (++sig < 32)
	{
		if (sigorigs[sig] != (void (*)(int))-1)
			continue ;
		(void)signal(sig, sigorigs[sig]);
	}
}
