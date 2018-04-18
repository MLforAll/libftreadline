/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/18 19:22:44 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRL_INTERNAL_H
# define FTRL_INTERNAL_H

# include "libft.h"
# include "ftrl_data.h"
# include <termcap.h>
# include <sys/ioctl.h>

/*
** ANSI Sequences Codes
*/

# define ESC_LEFTK	"\033[D"
# define ESC_RIGHTK	"\033[C"
# define ESC_HOMEK	"\033[H"
# define ESC_ENDK	"\033[F"
# define ESC_DELK	"\033[3~"
# define ESC_CLRL	"\033[K"
# define ESC_SAVEP	"\033[s"
# define ESC_RESTP	"\033[u"

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
}				t_mov;

/*
** struct for cursor mgmt
*/

typedef struct	s_cursor
{
	unsigned int	pos;
	size_t			max;
}				t_cursor;

/*
** struct for moving around data
*/

typedef struct	s_readline
{
	const char		*prompt;
	size_t			prlen;
	t_cursor		csr;
	t_keys			keys;
	t_mov			movs;
	t_rl_opts		*opts;
	struct winsize	ws;
}				t_readline;

/*
** some enums
*/

typedef enum	e_keyact
{
	kKeyNone,
	kKeyOK,
	kKeyFail
}				t_keyact;

/*
** autocompletion
*/

t_keyact		rl_ac_routine(char **line, t_readline *rl);

/*
** cursor
*/

/*t_keyact		rl_csr_keys(char *buff, t_readline *rl);
t_keyact		rl_home_end_keys(char *buff, t_readline *rl);*/
t_keyact		rl_right_key(char *buff, t_readline *rl);
t_keyact		rl_left_key(char *buff, t_readline *rl);
t_keyact		rl_home_key(char *buff, t_readline *rl);
t_keyact		rl_end_key(char *buff, t_readline *rl);

/*
** line edit
*/

void			rl_line_rm(char **line, size_t len, t_readline *rl);
void			rl_line_add(char **line, char *add, t_readline *rl);
int				rl_input_add_text(char *buff, char **line, t_readline *rl);
int				rl_input_rm_text(char **line, char *buff, t_readline *rl);

/*
** history
*/

t_history		*ft_histnew(char *line);
void			ft_histadd(t_history **headref, char *line);
void			ft_histdelone(t_history	**hist);
void			ft_histdel(t_history **headref);
t_keyact		rl_history_keys(t_history **history, char *buff, char **line);

/*
** terminal
*/

int				rl_init(t_readline *rl, const char *prompt, t_rl_opts *opts);
int				rl_set_term(t_readline *rl, int echo, const char *prompt);

/*
** termcaps
*/

int				outcap(char *name);
int				outcapstr(char *cstr);
int				outcap_arg_fb(char *cstr, char *fb, int arg);

/*
** utils
*/

size_t			ft_strlen_nocolor(const char *s);
void			get_line_info_for_pos(t_point *pt, unsigned int pos, t_readline *rl);
void			get_line_info(t_point *pt, t_readline *rl);

#endif
