# libftreadline
ft_readline lib for 42 projects

This is a small lib that implements line editing functionalities
in C.

It uses termcaps and passes norminette, so it can be used for 42 projects.

# Autocompletion
The lib has its own autocompletion routine. It calls 2 functions passed
in the func ptrs in the t_rl_opts struct. If a ptr is NULL, ft_readline will use
its builtin version.

By default, ft_readline will search the current directory or the directory in the line
for similar starting entries. If there are multiple entries, ft_readline displays the list
and uppon new tab press with same entries, flick between thoses the DOS style.

# _18/04/18_
The project, while in good shape, is not finished.
Norm issues and bugs can exist.
Autocompletion is to be implemented again.
