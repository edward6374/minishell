# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_pipes.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:41:27 by vduchi            #+#    #+#              #
#    Updated: 2023/07/08 17:58:43 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PIPES	=	srcs/pipes/pipes.c
SRCS_PIPES	+=	srcs/pipes/run_commands.c
SRCS_PIPES	+=	srcs/pipes/minishell.c

OBJS_PIPES	=	$(patsubst $(SRC_DIR_PIPES)/%, $(OBJ_DIR_PIPES)/%, $(SRCS_PIPES:.c=.o))
DEPS_PIPES	=	$(patsubst $(SRC_DIR_PIPES)/%, $(DEP_DIR_PIPES)/%, $(SRCS_PIPES:.c=.d))
