# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_execute.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:41:27 by vduchi            #+#    #+#              #
#    Updated: 2023/08/12 18:12:29 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_EXEC	=	srcs/execute/utils.c
SRCS_EXEC	+=	srcs/execute/exec_cmds.c

OBJS_EXEC	=	$(patsubst $(SRC_DIR_EXEC)/%, $(OBJ_DIR_EXEC)/%, $(SRCS_EXEC:.c=.o))
DEPS_EXEC	=	$(patsubst $(SRC_DIR_EXEC)/%, $(DEP_DIR_EXEC)/%, $(SRCS_EXEC:.c=.d))
