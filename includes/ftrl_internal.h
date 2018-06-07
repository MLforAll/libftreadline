/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/07 02:06:11 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRL_INTERNAL_H
# define FTRL_INTERNAL_H

# include "libftreadline.h"
# include "ftrl_termcap.h"
# include "ftrl_dev.h"
# include <termcap.h>
# include <sys/ioctl.h>

/*
** Macros
*/

# define DFL_LINEBUFFSIZE	10
# define RL_READBUFFSIZE	6

/*
** ANSI Sequences Codes
*/

# define ESC_MOVL			"\033b"
# define ESC_MOVR			"\033f"

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
}				t_mov;

typedef struct	s_cpypste
{
	unsigned int	mkrs[2];
	char			*dat;
}				t_cpypste;

typedef enum	e_abort
{
	kAbortNone,
	kAbortQuit,
	kAbortReload
}				t_abort;

/*
** struct for moving around data
*/

typedef struct	s_readline
{
	const char		*prompt;
	size_t			prlen;
	char			*line;
	size_t			bufflen;
	uint8_t			dumb;
	t_abort			abort_reason;
	t_cursor		csr;
	t_cpypste		cpypste;
	t_keys			keys;
	t_mov			movs;
	t_rl_opts		*opts;
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

typedef enum	e_direct
{
	kDirectLeft = -1,
	kDirectRight = 1
}				t_direct;

/*
** line edit (keys)
*/

int				rl_input_add_text(char *buff, t_readline *rl);
int				rl_input_rm_text(char *buff, t_readline *rl);
t_keyact		rl_clear_line(t_readline *rl);

/*
** line edit (sys)
*/

void			rl_line_rm(size_t len, t_readline *rl);
void			rl_line_add(char *add, t_readline *rl);

/*
** line buffer
*/

size_t			rl_linebuff_create(char **line);
int				rl_linebuff_rm(size_t len, t_readline *rl);
int				rl_linebuff_add(char *add, size_t addlen, t_readline *rl);

/*
** cursor motion (left/right - home/end - alt+left/alt+right)
*/

t_keyact		rl_right_key(t_readline *rl);
t_keyact		rl_left_key(t_readline *rl);
t_keyact		rl_home_key(t_readline *rl);
t_keyact		rl_end_key(t_readline *rl);

t_keyact		rl_movl_key(t_readline *rl);
t_keyact		rl_movr_key(t_readline *rl);

/*
** copy/paste (to be changed, refined etc!!!)
*/

t_keyact		rl_paste_key(t_readline *rl);
t_keyact		rl_cpy_key(t_readline *rl);
t_keyact		rl_rightcpy_key(t_readline *rl);
t_keyact		rl_leftcpy_key(t_readline *rl);

/*
** autocompletion
*/

t_keyact		rl_acroutine(t_readline *rl);
t_list			*search_files_begin(const char *f_path, const char *s_dir,
									int exec);

/*
** history
*/

t_keyact		rl_history_keys(char *buff, t_readline *rl, t_dlist **hist);

/*
** terminal
*/

int				rl_set_term(uint8_t echo);
int				rl_set_opost(uint8_t opost);

/*
** init
*/

int				rl_deinit(t_readline *rl);
int				rl_init(t_readline *rl, const char *prompt, t_rl_opts *opts);

/*
** utils
*/

size_t			ft_strlen_nocolor(const char *s);
void			get_line_info_for_pos(t_point *pt, unsigned int pos,
									t_readline *rl);
void			get_line_info(t_point *pt, t_readline *rl);
void			go_to_point(t_point *to, t_point *from, t_readline *rl);
void			go_to_pos(unsigned int to, unsigned int from, t_readline *rl);
t_readline	*rl_latest_session(t_readline *set);

#endif
