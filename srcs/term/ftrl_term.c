/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 02:01:46 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/25 16:26:55 by kdumarai         ###   ########.fr       */
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

int					rl_set_term(int echo)
{
	static struct termios	saved_t;
	struct termios			t;
	static uint8_t			state = 0;

	if (state != echo || (!echo && tcgetattr(STDIN_FILENO, &saved_t)))
		return (FALSE);
	if (!echo)
	{
		t = saved_t;
		t.c_lflag &= ~(ICANON | ECHO | ISIG);
		t.c_oflag &= ~OPOST;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
		state = 1;
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_t);
		state = 0;
	}
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

int					rl_deinit(void)
{
	if (!rl_set_term(YES))
		return (FALSE);
	outcap("ke");
	signal(SIGWINCH, SIG_DFL);
	return (TRUE);
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
	if (!(rl_set_term(NO)))
		return (FALSE);
	outcap("ks");
	get_winsize_hdl((unsigned long long)rl);
	signal(SIGWINCH, (void (*)(int))&get_winsize_hdl);
	return (TRUE);
}
