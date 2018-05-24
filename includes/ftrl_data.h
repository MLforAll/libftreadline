/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 06:36:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/24 23:07:16 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRL_DATA_H
# define FTRL_DATA_H

# include <sys/ioctl.h>
# include <stdint.h>

/*
** linked list for history mgmt
*/

typedef struct	s_rl_hist
{
	char				*line;
	struct s_rl_hist	*next;
	struct s_rl_hist	*prev;
}				t_rl_hist;

/*
** struct for cursor mgmt
*/

typedef struct	s_cursor
{
	unsigned int	pos;
	size_t			max;
}				t_cursor;

/*
** struct for ac results
*/

typedef struct	s_acres
{
	char	*visible_str;
	char	*str;
}				t_acres;

/*
** options struct
*/

typedef struct	s_rl_opts
{
	uint8_t		bell;
	int			outfd;
	t_list		*(*ac_get_result)(char *, t_cursor *);
	char		*(*ac_show_result)(t_list **);
	t_rl_hist	*hist;
}				t_rl_opts;

/*
** global for window size
*/

struct winsize	g_ws;

/*
** enum for ft_confirm
*/

typedef enum	e_dflact
{
	kDefaultYes,
	kDefaultNo
}				t_dflact;

#endif
