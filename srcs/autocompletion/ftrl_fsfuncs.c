/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsexp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 21:26:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/21 20:37:23 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "libftreadline.h"

static char			*get_elem_path(const char *d_path, char *name)
{
	char			*ret;

	if (!d_path || !name)
		return (NULL);
	if (!(ret = ft_strnew(ft_strlen(d_path) + ft_strlen(name) + 1)))
		return (NULL);
	ft_strcpy(ret, d_path);
	ft_strcat(ret, "/");
	ft_strcat(ret, name);
	return (ret);
}

static int			is_exec(const char *d_path, char *name, int folder)
{
	struct stat		st;
	char			*elem_path;
	int				ret;

	if (!d_path || !name || !(elem_path = get_elem_path(d_path, name)))
		return (FALSE);
	ret = FALSE;
	if (stat(elem_path, &st) != -1 && (st.st_mode & S_IXUSR
		|| st.st_mode & S_IXGRP || st.st_mode & S_IXOTH)
		&& S_ISDIR(st.st_mode) == folder)
		ret = TRUE;
	ft_strdel(&elem_path);
	return (ret);
}

inline static void	search_files_add(struct dirent *dird, t_list **ret)
{
	t_list	*new;

	if (!(new = ft_lstnew(dird->d_name, dird->d_namlen + 2)))
		return ;
	ft_strcpy(new->content + dird->d_namlen,
		(dird->d_type == DT_DIR) ? "/" : " ");
	ft_lstadd(ret, new);
}

t_list				*search_files_begin(const char *f_path,
										const char *s_dir,
										int exec)
{
	t_list			*ret;
	DIR				*dirp;
	struct dirent	*dird;
	char			*basedir;
	char			*name;

	basedir = (!s_dir) ? get_basedir(f_path) : (char*)s_dir;
	name = get_name_from_path(f_path);
	dirp = opendir(basedir);
	ret = NULL;
	while (dirp && (dird = readdir(dirp)))
	{
		if ((!exec && ft_strstart(dird->d_name, name))
		|| (exec && ft_strstart(dird->d_name, name)
		&& is_exec(s_dir, dird->d_name, FALSE)))
			search_files_add(dird, &ret);
	}
	if (dirp)
		closedir(dirp);
	if (!s_dir)
		ft_strdel(&basedir);
	return (ret);
}