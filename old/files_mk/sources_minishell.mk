# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_minishell.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:46:18 by vduchi            #+#    #+#              #
#    Updated: 2023/07/08 17:58:19 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MS		=	srcs/general/main.c
SRCS_MS		+=	srcs/general/utils.c
SRCS_MS		+=	srcs/general/free_funcs.c

OBJS_MS		=	$(patsubst $(SRC_DIR_MS)/%, $(OBJ_DIR_MS)/%, $(SRCS_MS:.c=.o))
DEPS_MS		=	$(patsubst $(SRC_DIR_MS)/%, $(DEP_DIR_MS)/%, $(SRCS_MS:.c=.d))
