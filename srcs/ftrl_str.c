/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 01:46:20 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/12 23:23:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_nocolor(const char *s)
{
	size_t		ret;
	size_t		chk;

	ret = 0;
	while (*s)
	{
		if (*s == '\033')
		{
			chk = 0;
			while (chk++ < 7 && s && *s != 'm')
				s++;
			ret--;
		}
		ret++;
		s++;
	}
	return (ret);
}
