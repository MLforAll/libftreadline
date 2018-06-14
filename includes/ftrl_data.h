/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 06:36:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/14 05:02:12 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRL_DATA_H
# define FTRL_DATA_H

# include <sys/ioctl.h>
# include <stdint.h>

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
	int			outfd;
	uint8_t		bell;
	char		reserved_pad[3];
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
