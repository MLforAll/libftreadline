/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:46:30 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/04 18:12:18 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRL_INTERNAL_H
# define FTRL_INTERNAL_H

# include "libftreadline.h"
# include "ftrl_termcap.h"
# include "ftrl_dev.h"
# include <termcap.h>
# include <termios.h>
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
** cpy/paste structs
*/

typedef struct	s_cpypste
{
	unsigned long	mkrs[2];
	char			*dat;
}				t_cpypste;

/*
** quit functions data
*/

typedef enum	e_abort
{
	kAbortNone,
	kAbortQuit,
	kAbortReload
}				t_abort;

typedef struct	s_quit
{
	void			(*func)(void *);
	void			*func_data;
	void			(*free_func)(void *);
	t_abort			reason;
	char			reserved_pad[4];
}				t_quit;

/*
** struct for moving around data
*/

typedef struct	s_readline
{
	t_rl_opts		*opts;
	const char		*prompt;
	size_t			prlen;
	char			*line;
	size_t			bufflen;
	t_cursor		csr;
	t_cpypste		cpypste;
	t_quit			quit;
	t_mov			movs;
	t_keys			keys;
	t_uint8			dumb;
	char			reserved_pad[7];
}				t_readline;

/*
** some enums
*/

typedef enum	e_keyact
{
	kKeyNone,
	kKeyOK,
	kKeyFail,
	kKeyFatal
}				t_keyact;

typedef enum	e_direct
{
	kDirectLeft,
	kDirectRight
}				t_direct;

/*
** line edit (keys)
*/

t_keyact		rl_input_add_text(char *buff, t_readline *rl);
t_keyact		rl_input_rm_text(char *buff, t_readline *rl);
t_keyact		rl_clear_line(t_readline *rl);

/*
** line edit (sys)
*/

void			rl_line_rm(size_t len, t_readline *rl);
void			rl_line_add(char *add, t_readline *rl);

/*
** line buffer
*/

t_uint8			rl_linebuff_create(t_readline *rl);
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
** navigation funcs
*/

void			get_line_info_for_pos(t_point *pt, unsigned long pos,
									t_readline *rl);
void			get_line_info(t_point *pt, t_readline *rl);
void			go_to_point(t_point *to, t_point *from, t_readline *rl);
void			go_to_pos(unsigned long to, unsigned long from, t_readline *rl);

/*
** copy/paste
*/

t_keyact		rl_paste_key(t_readline *rl);
t_keyact		rl_cpy_key(t_readline *rl);
t_keyact		rl_rightcpy_key(t_readline *rl);
t_keyact		rl_leftcpy_key(t_readline *rl);

/*
** autocompletion
*/

t_keyact		rl_acroutine(t_readline *rl);
t_list			*search_files_begin(const char *f_path, char *s_dir,
									int exec);

/*
** history
*/

t_keyact		hist_nav(char *buff, t_readline *rl, t_dlist **hist);

/*
** terminal
*/

int				rl_set_term(t_uint8 echo);
t_uint8			rl_set_timeout(t_uint8 enable, cc_t timeout);

/*
** init
*/

int				rl_deinit(t_readline *rl);
int				rl_init(t_readline *rl, const char *prompt, t_rl_opts *opts);

/*
** signals
*/

void			set_signals(void);
void			restore_signals(void);

/*
** quit functions
*/

t_uint8			quit_with_reason(t_abort reason,
								void (*func)(void *),
								void *data,
								void (*free_func)(void *));

/*
** utils
*/

char			*ft_prompt_nocolor(const char *prompt);
size_t			ft_strlen_nocolor(const char *s);

t_readline		*rl_latest_session(t_uint8 set, t_readline *new_session);

#endif
