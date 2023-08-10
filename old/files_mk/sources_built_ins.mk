# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_built_ins.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:46:44 by vduchi            #+#    #+#              #
#    Updated: 2023/07/08 17:57:56 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_BI	=	srcs/built-ins/exit.c
SRCS_BI	+=	srcs/built-ins/env.c
SRCS_BI	+=	srcs/built-ins/export.c
SRCS_BI	+=	srcs/built-ins/unset.c
SRCS_BI	+=	srcs/built-ins/pwd.c
SRCS_BI	+=	srcs/built-ins/cd.c
SRCS_BI	+=	srcs/built-ins/echo.c

OBJS_BI	=	$(patsubst $(SRC_DIR_BI)/%, $(OBJ_DIR_BI)/%, $(SRCS_BI:.c=.o))
DEPS_BI	=	$(patsubst $(SRC_DIR_BI)/%, $(DEP_DIR_BI)/%, $(SRCS_BI:.c=.d))
