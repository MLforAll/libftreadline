/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 01:46:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/26 02:26:07 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftrl_internal.h"
#include "libft.h"

static inline const char	*skip_esc_seq(const char *s)
{
	size_t	chk;

	chk = 0;
	while (chk++ < 8 && s && !ft_isalpha((int)*s))
		s++;
	return (s);
}

size_t						ft_strlen_nocolor(const char *s)
{
	size_t		ret;

	ret = 0;
	while (*s)
	{
		if (*s == '\033')
		{
			s = skip_esc_seq(s);
			ret--;
		}
		ret++;
		s++;
	}
	return (ret);
}

char						*ft_prompt_nocolor(const char *prompt)
{
	t_str	vstr;
	char	buff[2];

	vstr = ft_tstrnew();
	buff[1] = '\0';
	while (*prompt)
	{
		if (*prompt == '\033')
			prompt = skip_esc_seq(prompt);
		else
		{
			buff[0] = *prompt;
			ft_tstrcat(&vstr, buff);
		}
		prompt++;
	}
	return (vstr.s);
}
