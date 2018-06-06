/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quittest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:49:35 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/06 23:56:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libftreadline.h"

static void	sighdl(int sigc)
{
	ftrl_quit();
}

int			main(int ac, char **av, char **env)
{
	char		*line;
	char		*prompt;
	t_rl_opts	opts;
	t_dlist		*hist;

	signal(SIGTERM, &sighdl);
	ft_bzero(&opts, sizeof(t_rl_opts));
	opts.bell = TRUE;
	opts.outfd = STDIN_FILENO;
	opts.ac_get_result = NULL;
	opts.ac_show_result = NULL;
	hist = NULL;
	prompt = "\033[1;33mft_readline\033[0;39m$ ";
	while ((line = ft_readline(prompt, &opts, hist)))
	{
		ft_putstr_fd("-----------> ", STDIN_FILENO);
		ft_putstr_fd(line, STDIN_FILENO);
		ft_putstr_fd("\n\n", STDIN_FILENO);
		ftrl_histadd(&hist, line);
		ft_strdel(&line);
	}
	ft_dlstdel(&hist, &ftrl_histdelf);
	return (0);
}
