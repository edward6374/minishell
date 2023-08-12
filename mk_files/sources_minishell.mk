# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_minishell.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:46:18 by vduchi            #+#    #+#              #
#    Updated: 2023/08/12 13:22:05 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MS		=	srcs/minishell/main.c
SRCS_MS		+=	srcs/minishell/utils.c
SRCS_MS		+=	srcs/minishell/take_env.c
SRCS_MS		+=	srcs/minishell/free_funcs.c
SRCS_MS		+=	srcs/minishell/free_structs.c

OBJS_MS		=	$(patsubst $(SRC_DIR_MS)/%, $(OBJ_DIR_MS)/%, $(SRCS_MS:.c=.o))
DEPS_MS		=	$(patsubst $(SRC_DIR_MS)/%, $(DEP_DIR_MS)/%, $(SRCS_MS:.c=.d))
