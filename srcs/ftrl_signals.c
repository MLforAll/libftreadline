/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 17:21:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/04 18:54:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "ftrl_internal.h"

static void	(*g_sig_origs[32])(int);

static void	rl_generic_sig_hdl(int sigc)
{
	t_readline	*session;

	if (g_sig_origs[sigc] == (void (*)(int))-1
		|| sigc == SIGINT || sigc == SIGTSTP
		|| !(session = rl_latest_session(NO, NULL)))
		return ;
	(void)rl_deinit(session);
	ft_putchar('\n');
	if (g_sig_origs[sigc] == SIG_DFL || g_sig_origs[sigc] == SIG_IGN)
	{
		(void)signal(sigc, g_sig_origs[sigc]);
		raise(sigc);
		return ;
	}
	(g_sig_origs[sigc])(sigc);
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
			g_sig_origs[sig] = (void (*)(int))-1;
		else
			g_sig_origs[sig] = signal(sig, &rl_generic_sig_hdl);
	}
	get_winsize_hdl(SIGWINCH);
	g_sig_origs[SIGWINCH] = signal(SIGWINCH, &get_winsize_hdl);
}

void		restore_signals(void)
{
	int		sig;

	sig = 0;
	while (++sig < 32)
	{
		if (g_sig_origs[sig] == (void (*)(int))-1)
			continue ;
		(void)signal(sig, g_sig_origs[sig]);
	}
}
