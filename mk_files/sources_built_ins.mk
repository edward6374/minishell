# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_built_ins.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:46:44 by vduchi            #+#    #+#              #
#    Updated: 2023/08/24 11:55:02 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_BI	=	srcs/built_ins/exit.c
SRCS_BI	+=	srcs/built_ins/env.c
SRCS_BI	+=	srcs/built_ins/export.c
SRCS_BI	+=	srcs/built_ins/export_add.c
SRCS_BI	+=	srcs/built_ins/unset.c
SRCS_BI	+=	srcs/built_ins/pwd.c
SRCS_BI	+=	srcs/built_ins/cd.c
SRCS_BI	+=	srcs/built_ins/echo.c

OBJS_BI	=	$(patsubst $(SRC_DIR_BI)/%, $(OBJ_DIR_BI)/%, $(SRCS_BI:.c=.o))
DEPS_BI	=	$(patsubst $(SRC_DIR_BI)/%, $(DEP_DIR_BI)/%, $(SRCS_BI:.c=.d))