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

/*if (coords.x + 1 + rl->dumb == g_ws.ws_col)
	{
		if (rl->dumb)
			go_to_pos(rl->csr.pos + 1, rl->csr.pos, rl);
		else
		{
			(void)outcapstr(rl->movs.crcap);
			outcapstr(rl->movs.downm);
		}
	}
	else if (rl->dumb)
		ft_putchar_fd(rl->line[rl->csr.pos], STDIN_FILENO);
	else
		(void)outcapstr(rl->movs.rightm);*/

		/*
**t_keyact	rl_historybu_key(t_rl_hist **history, t_readline *rl)
**{
**	if (!history || !*history || !(*history)->next)
**		return (kKeyFail);
**	return (kKeyOK);
**}
**
**t_keyact	rl_historybd_key(t_rl_hist **history, t_readline *rl)
**{
**	if (!history || !*history || !(*history)->prev)
**		return (kKeyFail);
**	return (kKeyOK);
**}
*/
