# libftreadline
ft_readline lib for 42 projects

This is a small C lib that implements 2 functions:
- ft_readline() gets line with editing functionalities
- ft_confirm() asks for user confirmation

It uses termcaps and passes norminette, so it can be used for 42 projects.

# Manpages
The lib includes manpages for each function.
To view them with `man`, you can issue (assuming `$PWD` is the repo dir):<br/>
`man -M man ft_readline`<br/>
or<br/>
`man -M man ft_confirm`<br/>
or even<br/>
`man -M man libftreadline`<br/>

If you want to view them all in a row, issue:<br/>
`man man/man3/*`

# Autocompletion
ft_readline() has its own autocompletion routine. It calls 2 functions passed
in the func ptrs in the t_rl_opts struct. If a ptr is NULL, ft_readline will use
its builtin version.

By default, ft_readline will search the current directory or the directory in the line
for similar starting entries. If there are multiple entries, ft_readline displays the list
and uppon new tab press with same entries, flick between thoses the DOS style.

# History
ft_readline() can browse a line history, via the third argument you pass to it.
It is your resposability to create the ptr, add the returned lines to the history via the lib functions,
pass it to ft_readline() and free it when you're done with it.

# _25/04/18_
The project, while in good shape, is not finished.
Norm issues and bugs can exist.
Autocompletion is done!
History fixed and working.
Copy and paste OK.
NOW, ONLY CODE IMPROVEMENTS/CLEANING AND TWEAKING TO MAKE IT \`\`PERFECT''
