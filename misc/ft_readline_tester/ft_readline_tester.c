/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_tester.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:49:35 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/02 18:19:48 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libftreadline.h"
#include "ftrl_internal.h"

#ifdef INSMSG
static void	quit_hdl(int sigc)
{
	(void)sigc;
	ftrl_insert_msg("Yolo", STDOUT_FILENO, NO);
}
#endif

#ifdef MLPR
# define PRSTR "\033[1;33mft_readline\033[0;39m\nmultiline_prompt$ "
#elif LGPR
# define PRSTR "IAmAVeryLongPromptAndIHaveNoColorWhatsSoEverMyGoalIsToBeLargerThanAllOfYouToTestAGreatFeatureCauseICanUseVarPromptsThatTheUserCanSelectWithin21sh$ "
#else
# define PRSTR "\033[1;33mft_readline\033[0;39m$ "
#endif

int			main(int ac, char **av, char **env)
{
	int			status;
	char		*line;
	t_rl_opts	opts;
	t_dlist		*hist;
	size_t		len;

#ifdef INSMSG
	signal(SIGUSR1, &quit_hdl);
#endif
	ft_bzero(&opts, sizeof(t_rl_opts));
	opts.bell = TRUE;
	opts.outfd = STDIN_FILENO;
	opts.ac_get_result = NULL;
	opts.ac_show_result = NULL;
#ifdef PPL
	opts.prompt_perline = TRUE;
#endif
	hist = NULL;
#ifdef MLTEST
	ftrl_histadd(&hist, "Et un, Et deux, Et trois ZERO!\nOn est les champions");
#endif
	ft_putstr_fd("This tool is used for debug purposes ONLY!\n"
				"Type something and check if the returned result is OK\n"
				"PS: Autocompletion works for files "
				"using the embbeded routines\n"
				"PS2: Ctrl-D to quit!\n\n", STDIN_FILENO);
	while ((status = ft_readline(&line, PRSTR, &opts, hist)) != FTRL_EOF
		&& status != FTRL_FAIL)
	{
		if (status == FTRL_SIGINT)
			ft_putstr("Aborted.\n\n");
		else
		{
			len = !ftrl_prompt_isvalid_dumb(PRSTR) ? 11 : ft_prompt_len(PRSTR) - 2;
			ft_putnchar_fd('-', len, STDIN_FILENO);
			ft_putstr_fd("> ", STDIN_FILENO);
			ft_putstr_fd(line, STDIN_FILENO);
			ft_putstr_fd("\n\n", STDIN_FILENO);
			ftrl_histadd(&hist, line);
		}
		ft_strdel(&line);
	}
	ft_dlstdel(&hist, &ftrl_histdelf);
	return (0);
}
