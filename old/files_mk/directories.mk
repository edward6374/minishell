# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    directories.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:45:46 by vduchi            #+#    #+#              #
#    Updated: 2023/07/08 17:57:33 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS_DIR			=	libs
SRC_DIR				=	srcs
INC_DIR				=	incs
INC_DIR				+=	libft
INC_DIR				+=	readline
OBJS_DIR			=	.objs
DEPS_DIR			=	.deps
SRC_DIR_MS			=	$(SRC_DIR)/general
OBJ_DIR_MS			=	$(OBJS_DIR)/general
DEP_DIR_MS			=	$(DEPS_DIR)/general
SRC_DIR_PIPES		=	$(SRC_DIR)/pipes
OBJ_DIR_PIPES		=	$(OBJS_DIR)/pipes
DEP_DIR_PIPES		=	$(DEPS_DIR)/pipes
SRC_DIR_BI			=	$(SRC_DIR)/built-ins
OBJ_DIR_BI			=	$(OBJS_DIR)/built-ins
DEP_DIR_BI			=	$(DEPS_DIR)/built-ins
SRC_DIR_PARSER		=	$(SRC_DIR)/parser
OBJ_DIR_PARSER		=	$(OBJS_DIR)/parser
DEP_DIR_PARSER		=	$(DEPS_DIR)/parser
SRC_DIR_TESTER		=	$(SRC_DIR)/tester
OBJ_DIR_TESTER		=	$(OBJS_DIR)/tester
DEP_DIR_TESTER		=	$(DEPS_DIR)/tester
