# libftreadline
ft_readline lib for 42 projects

This is a small C lib that implements 2 functions:

- ft_readline() reads a line from <b>stdin</b> with editing functionalities
- ft_confirm() displays a message and asks for user confirmation

It uses termcaps and passes norminette, so it can be used for 42 projects.

# Manpages
The lib includes manpages for each function.
To view them with `man(1)`, you can issue (assuming `$PWD` is the repo dir):<br/>
`$> man -M man ft_readline`<br/>
or<br/>
`$> man -M man ft_confirm`<br/>
or even<br/>
`$> man -M man libftreadline`<br/>

If you want to view them all in a row, issue:<br/>
`$> man man/man3/*`

# Autocompletion
ft\_readline() has its own autocompletion routine. It calls 2 functions passed
in the func ptrs in the _t\_rl\_opts_ struct. If a ptr is NULL, ft\_readline() will use
its builtin version.

By default, ft\_readline() will search the current directory or the directory in the line
for similar starting entries. If there are multiple entries, ft\_readline() displays the list.

# History
ft\_readline() can browse a line history, via the third argument you pass to it.
It is your resposability to create the ptr, add the returned lines to the history via the lib functions, pass it to ft\_readline() and free it when you're done with it.

# Copy/Cut/Paste
ft\_readline() has a copy/cut/paste feature. By using the Shift+Left or Shift+Right keys, you can select text. With Shift+Up you can copy or cut if you double-press it.
With Shift+Down, you paste the copied text. If nothing is copied, nothing happens.

# Bell
When a key fails, but not because of an internal error, ft_readline() makes the terminal ring a bell.

# Dumb mode
ft\_readline() implements a \`\`dumb mode''. It is used when the terminal is not
known to provide line-editing. In dumb mode, there is only one line that flicks
through multiples \`\`pages''. Copy/Cut/Paste, history and autocompletion features
are still available although the _ac\_show\_result_ func ptr is ignored and the bell is disabled.

