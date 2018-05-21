# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/04 06:10:18 by kdumarai          #+#    #+#              #
#    Updated: 2018/05/21 20:38:42 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftreadline.a

CC_FLAGS = -Wall -Werror -Wextra
CC_LIB = -I includes -I ../libft/includes
LD_FLAGS = -L ../libft -lft

SRCDIR = srcs
SRCFILES = ft_readline.c \
	ft_confirm.c \
	line/ftrl_line.c \
	line/ftrl_linekeys.c \
	line/ftrl_linebuff.c \
	navigation/ftrl_csrkeys.c \
	navigation/ftrl_movtab.c \
	autocompletion/ftrl_acroutine.c \
	autocompletion/ftrl_acgetres.c \
	autocompletion/ftrl_fsfuncs.c \
	autocompletion/ftrl_acshowres.c \
	term/ftrl_term.c \
	term/ftrl_termcaps.c \
	ftrl_utils.c \
	history/ftrl_history.c \
	history/ftrl_historykeys.c \
	ftrl_cpypaste.c \
	lst_utils.c
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

NSRC = $(shell echo "$(SRCS)" | awk '{print NF}')
ifeq ($(shell [ ! -z "`which bc`" ] && [ ! -z "`which awk`" ] && echo true),true)
	CSRC = 1
else
	CSRC = 0
endif

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

PROJTEXT = \033[1;35mlibftreadline \033[0;39m

all: $(NAME)

$(NAME): $(OBJS)
	@ printf "\033[K$(PROJTEXT)Compiling\n"
	@ printf "$(PROJTEXT)Linking\n"
	@ ar rcs $(NAME) $?
	@ printf "$(PROJTEXT)\033[1;32mLib built at $(NAME)\033[0;39m\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	@ printf "\033[K$(PROJTEXT)Compiling \033[1;33m$<"
ifneq ($(CSRC),0)
	@ printf " %.0s" {1..$(shell expr 40 - $(shell printf "$<" | wc -m))}
	@ export LC_ALL=C; printf "\033[1;34m[%3.0f%%]" "$(shell bc <<< "scale=1; $(CSRC) / $(NSRC) * 100")"
	@ $(eval CSRC = $(shell expr $(CSRC) + 1))
endif
	@ printf "\033[0;39m\r"
	@ gcc $(CC_FLAGS) $(CC_LIB) -c $< -o $@

clean:
	@ rm -rf $(OBJDIR)
	@ printf "$(PROJTEXT)Removed objects\n"

fclean: clean
	@ rm -f $(NAME)
	@ printf "$(PROJTEXT)Removed $(NAME)\n"

re: fclean all

.PHONY: all clean fclean re
