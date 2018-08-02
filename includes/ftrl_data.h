/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 06:36:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/02 18:18:06 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRL_DATA_H
# define FTRL_DATA_H

# include <sys/ioctl.h>
# include <stdint.h>

/*
** Return values macros
*/

# define FTRL_OK		0
# define FTRL_FAIL		-1
# define FTRL_SIGINT	1
# define FTRL_EOF		2

/*
** global for window size
*/

extern struct winsize	g_ws;
struct winsize			g_ws;

/*
** struct for cursor mgmt
*/

typedef struct			s_cursor
{
	unsigned long	pos;
	size_t			max;
}						t_cursor;

/*
** options struct
*/

typedef struct			s_rl_opts
{
	t_list		*(*ac_get_result)(char *, t_cursor *);
	char		*(*ac_show_result)(t_list **);
	char		*(*ac_show_result_dumb)(t_list **);
	int			outfd;
	t_uint8		bell;
	t_uint8		dumb_prompt;
	t_uint8		prompt_perline;
	char		reserved_pad;
}						t_rl_opts;

/*
** enum for ft_confirm
*/

typedef enum			e_dflact
{
	kDefaultYes,
	kDefaultNo
}						t_dflact;

#endif
