/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_termcap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 01:36:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/29 01:37:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRL_TERMCAP
# define FTRL_TERMCAP

/*
** termcaps
*/

int				outcap(char *name);
int				outcapstr(char *cstr);
int				outcap_arg_fb(char *cstr, char *fb, int arg, int affcnt);

#endif
