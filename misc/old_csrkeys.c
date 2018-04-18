/*static int	rightk_action(t_readline *rl)
{
	if ((rl->csr.pos + 1 + rl->prlen) % rl->ws.ws_col == 0)
	{
		if (rl->csr.max + rl->prlen == rl->ws.ws_col)
			return (FALSE);
		ft_putstr_fd("\n\r", STDIN_FILENO);
	}
	else
		outcapstr(rl->movs.rightm);
	return (TRUE);
}

t_keyact	rl_csr_keys(char *buff, t_readline *rl)
{
	int				keys[2];

	keys[0] = (ft_strequ(rl->keys.rightk, buff));
	keys[1] = (ft_strequ(rl->keys.leftk, buff));
	if (!keys[0] && !keys[1])
		return (kKeyNone);
	if (keys[0] && rl->csr.pos < rl->csr.max)
	{
		if (!rightk_action(rl))
			return (kKeyNone);
		rl->csr.pos++;
		return (1);
	}
	if (keys[1] && rl->csr.pos > 0)
	{
		rl->csr.pos--;
		outcapstr(rl->movs.leftm);
		return (kKeyOK);
	}
	return (kKeyFail);
}

static void	configure_hekeys(int k[2], size_t *len, char *ckey, t_readline *rl)
{
	if (!k || !len || !ckey || !rl)
		return ;
	if (k[0] && rl->csr.pos < rl->csr.max
		&& rl->csr.max + rl->prlen < rl->ws.ws_col)
	{
		*len = rl->csr.max - rl->csr.pos;
		*ckey = 'C';
		rl->csr.pos = rl->csr.max;
	}
	else if (k[1] && rl->csr.pos > 0)
	{
		*len = rl->csr.pos;
		*ckey = 'D';
		rl->csr.pos = 0;
	}
}

t_keyact	rl_home_end_keys(char *buff, t_readline *rl)
{
	int				keys[2];
	size_t			len;
	char			ckey;

	keys[0] = (ft_strequ(rl->keys.endk, buff));
	keys[1] = (ft_strequ(rl->keys.homek, buff));
	if (!keys[0] && !keys[1])
		return (kKeyNone);
	len = 0;
	configure_hekeys(keys, &len, &ckey, rl);
	if (len == 0)
		return (kKeyFail);
	ft_putstr_fd("\033[", STDIN_FILENO);
	ft_putnbr_fd(len, STDIN_FILENO);
	ft_putchar_fd(ckey, STDIN_FILENO);
	return (kKeyOK);
}*/