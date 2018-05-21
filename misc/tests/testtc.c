#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

int		putcf(int c)
{
	write(0, &c, 1);
	return 1;
}

int		main(void)
{
	tgetent(NULL, getenv("TERM"));
	puts("Salut");
	if (tputs(tgetstr("up", NULL), 1, &putcf) == -1)
	{
		puts(strerror(errno));
		return 1;
	}
	puts("OK");
	tputs(tgoto(tgetstr("UP", NULL), 5, 5), 1, &putcf);
	return 0;
}
