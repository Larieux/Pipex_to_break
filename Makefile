# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlarieux <jlarieux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 13:59:35 by jlarieux          #+#    #+#              #
#    Updated: 2024/02/23 09:39:19 by jlarieux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = pipex_children_managment.c pipex_utilities.c pipex_heredoc.c \
	pipex_args.c pipex_children.c pipex_exec.c pipex.c \

OBJ_PATH = obj/

OBJS = ${addprefix ${OBJ_PATH}, ${SRCS:.c=.o}}

CFLAGS = -Wall -Werror -Wextra
LIB = libft/libft.a

NAME = pipex

all : ${OBJ_PATH} $(LIB) $(NAME)

${OBJ_PATH}:
	mkdir ${OBJ_PATH}

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB)

${OBJ_PATH}%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(LIB) :
	$(MAKE) -C libft bonus

clean :
	$(MAKE) -C libft clean
	$(RM) $(OBJS)
	rm -rf $(OBJ_PATH)

fclean : clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re : fclean all

.PHONY : all $(LIB)