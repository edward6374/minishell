# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_execute.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:41:27 by vduchi            #+#    #+#              #
#    Updated: 2023/08/23 22:35:32 by nmota-bu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_EXEC	=	srcs/execute/exec_cmds.c
SRCS_EXEC	+=	srcs/execute/exec_utils.c
SRCS_EXEC	+=	srcs/execute/pipes_and_hdoc.c
SRCS_EXEC	+=	srcs/execute/run_here_doc.c

OBJS_EXEC	=	$(patsubst $(SRC_DIR_EXEC)/%, $(OBJ_DIR_EXEC)/%, $(SRCS_EXEC:.c=.o))
DEPS_EXEC	=	$(patsubst $(SRC_DIR_EXEC)/%, $(DEP_DIR_EXEC)/%, $(SRCS_EXEC:.c=.d))
