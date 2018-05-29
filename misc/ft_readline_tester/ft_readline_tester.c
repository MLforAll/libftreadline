/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_tester.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:49:35 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/28 20:03:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftreadline.h"

int		main(int ac, char **av, char **env)
{
	char		*line;
	char		*prompt;
	t_rl_opts	opts;
	t_dlist		*hist;


	ft_bzero(&opts, sizeof(t_rl_opts));
	opts.bell = TRUE;
	opts.outfd = STDIN_FILENO;
	opts.ac_get_result = NULL;
	opts.ac_show_result = NULL;
	hist = NULL;
	prompt = "\033[1;33mft_readline\033[0;39m$ ";
	ft_putstr_fd("This tool is used for debug purposes ONLY!\n"
				"Type something and check if the returned result is OK\n"
				"PS: Autocompletion works for files "
				"using the embbeded routines\n"
				"PS2: Ctrl-D to quit!\n\n", STDIN_FILENO);
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
