/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 02:01:46 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 03:19:46 by kdumarai         ###   ########.fr       */
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

int					rl_set_term(t_readline *rl, int echo)
{
	struct termios	t;
	static int		state = 0;

	if (tcgetattr(STDIN_FILENO, &t) || state != echo)
		return (FALSE);
	if (!echo)
	{
		t.c_lflag &= ~(ICANON | ECHO | ISIG);
		t.c_oflag &= ~OPOST;
		outcap("ks");
		if (rl)
		{
			get_winsize_hdl((unsigned long long)rl);
			signal(SIGWINCH, (void (*)(int))&get_winsize_hdl);
		}
		state = 1;
	}
	else
	{
		t.c_lflag |= (ICANON | ECHO | ISIG);
		t.c_oflag |= OPOST;
		outcap("ke");
		signal(SIGWINCH, SIG_DFL);
		state = 0;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	return (TRUE);
}

inline static void	set_keys_movs(t_keys *keys, t_mov *movs)
{
	char			**keysptr;
	unsigned int	idx;
	const char		*caps[8] = {"kl", "kr", "ku", "kd", "kh", "@7", "kD", "kE"};

	keysptr = (char**)keys;
	idx = 0;
	while (idx < sizeof(caps) / sizeof(caps[0]))
	{
		keysptr[idx] = tgetstr((char*)caps[idx], NULL);
		idx++;
	}
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
