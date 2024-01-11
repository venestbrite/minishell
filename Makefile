# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stribuzi <stribuzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:59:55 by stribuzi          #+#    #+#              #
#    Updated: 2021/08/13 10:22:55 by stribuzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	check_add_variable.c \
					echo.c \
					main.c \
					redirection.c \
					export.c \
					utils/ft_itoa.c \
					utils/ft_lstadd_back.c \
					utils/ft_lstadd_front.c \
					utils/ft_lstnew.c \
					utils/ft_lstlast.c \
					utils/ft_split.c \
					utils/ft_strncmp.c \
					utils/ft_strcmp.c \
					utils/ft_strnstr.c \
					utils/ft_strjoin.c \
					utils/libft_addons.c \
					echo_search.c \
					utils/ft_strdup.c \
					cd.c \
					pipe.c \
					utils/libft_utils.c \
					functions.c \
					redir_double_in.c \
					functions_supp.c \
					unset.c \
					binaries.c \
					find_last.c \
					pwd.c \
					value.c \


OBJS			= $(SRCS:.c=.o)
CC				= gcc
RM				= rm -f


CFLAGS = -L /goinfre/$(USER)/homebrew/opt/readline/lib -I /goinfre/$(USER)/homebrew/opt/readline/include -lreadline -Qunused-arguments -Wall -Wextra -Werror

NAME			= minishell

all:		$(NAME)

$(NAME):		 $(OBJS)
						$(CC) $(OBJS) $(CFLAGS) -o $(NAME)


clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re

# \U0001F602 -- laughing emoji
# \U0001F642 -- Ludovica's smile
# \U0001F609 -- Occhiolino
# \U0001F62E -- :O 