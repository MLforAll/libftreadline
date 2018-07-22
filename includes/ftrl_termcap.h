/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_termcap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 01:36:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/22 14:35:35 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRL_TERMCAP_H
# define FTRL_TERMCAP_H

/*
** structs for termcaps
*/

typedef struct	s_keys
{
	char	*leftk;
	char	*rightk;
	char	*upk;
	char	*downk;
	char	*homek;
	char	*endk;
	char	*delk;
	char	*clrk;
	char	*tabk;
}				t_keys;

typedef struct	s_mov
{
	char	*leftm;
	char	*rightm;
	char	*upm;
	char	*downm;
	char	*cecap;
	char	*crcap;
	char	*dlargcap;
	char	*dlcap;
}				t_mov;

/*
** termcap functions
*/

int				outcap_fd(char *name, int fd);
int				outcap(char *name);
int				outcapstr(char *cstr);
int				outcap_arg_fb(char *cstr, char *fb, int arg, int affcnt);

#endif
