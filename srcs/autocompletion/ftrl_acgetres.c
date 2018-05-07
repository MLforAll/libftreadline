/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_acgetres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 20:53:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/07 14:44:38 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "ftrl_internal.h"

static char			*get_last_components(const char *s, const char *comps)
{
	char	*ret;
	char	*tmp;
	char	*chk;

	if (!s || !comps)
		return (NULL);
	tmp = (char*)s;
	ret = tmp;
	while (*tmp)
	{
		chk = (char*)comps;
		while (*chk)
		{
			if (*tmp == *chk)
				ret = tmp;
			chk++;
		}
		tmp++;
	}
	ret += (ret > s);
	return (ret);
}

inline static char	*get_region(char *line, t_cursor *csr)
{
	char			*tmp;
	unsigned int	idx;

	if (csr->pos == csr->max)
	{
		if (!(tmp = get_last_components(line, " |;>")))
			return (NULL);
		return (ft_strdup(tmp));
	}
	idx = csr->pos;
	while (idx--)
	{
		if (line[idx] == ' ')
			break ;
	}
	idx++;
	return (ft_strsub(line, idx, csr->pos - idx));
}

t_list				*get_ac_result_bltn(char *line, t_cursor *csr)
{
	t_list	*ret;
	char	*region;

	region = get_region(line, csr);
	ret = search_files_begin(region, NULL, FALSE);
	free(region);
	return (ret);
}
