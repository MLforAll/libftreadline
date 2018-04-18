/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 02:01:46 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/17 23:41:50 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "ftrl_internal.h"

static void			get_winsize_hdl(unsigned long long sigc)
{
	static t_readline	*rl = NULL;

	if (!rl)
		rl = (t_readline*)sigc;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &rl->ws);
}

int					rl_set_term(t_readline *rl, int echo, const char *prompt)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t))
		return (FALSE);
	if (!echo)
	{
		if (prompt)
			ft_putstr_fd(prompt, rl->opts->outfd);
		t.c_lflag &= ~(ICANON | ECHO | ISIG);
		t.c_oflag &= ~OPOST;
		outcap("ks");
		get_winsize_hdl((unsigned long long)rl);
		signal(SIGWINCH, (void (*)(int))&get_winsize_hdl);
	}
	else
	{
		t.c_lflag |= (ICANON | ECHO | ISIG);
		t.c_oflag |= OPOST;
		outcap("ke");
		signal(SIGWINCH, SIG_DFL);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	return (TRUE);
}

inline static void	set_keys_movs(t_keys *keys, t_mov *movs)
{
	keys->leftk = tgetstr("kl", NULL);
	keys->rightk = tgetstr("kr", NULL);
	keys->upk = tgetstr("ku", NULL);
	keys->downk = tgetstr("kd", NULL);
	keys->homek = tgetstr("kh", NULL);
	keys->endk = tgetstr("@7", NULL);
	keys->delk = tgetstr("kD", NULL);
	keys->clrk = tgetstr("kE", NULL);
	movs->leftm = tgetstr("le", NULL);
	movs->rightm = tgetstr("nd", NULL);
	movs->upm = tgetstr("up", NULL);
	movs->downm = tgetstr("do", NULL);
}

int					rl_init(t_readline *rl, const char *prompt, t_rl_opts *opts)
{
	char	*termenv;
	int		dumbmode;

	ft_bzero(rl, sizeof(t_readline));
	rl->prompt = prompt;
	rl->prlen = ft_strlen_nocolor(prompt);
	rl->opts = opts;
	dumbmode = FALSE;
	if (!(termenv = getenv("TERM")))
	{
		termenv = "dumb";
		dumbmode = TRUE;
	}
	if (!(tgetent(NULL, termenv)))
		return (FALSE);
	set_keys_movs(&rl->keys, &rl->movs);
	return (TRUE);
}
