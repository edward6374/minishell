# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_built_ins.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:46:44 by vduchi            #+#    #+#              #
#    Updated: 2023/08/10 16:02:58 by nmota-bu         ###   ########.fr        #
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
