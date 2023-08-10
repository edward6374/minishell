# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    directories.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:45:46 by vduchi            #+#    #+#              #
#    Updated: 2023/08/10 15:12:05 by nmota-bu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR				=	srcs
INC_DIR				=	incs
INC_DIR				+=	libft
INC_DIR				+=	readline
OBJS_DIR			=	.objs
DEPS_DIR			=	.deps
SRC_DIR_MS			=	$(SRC_DIR)/minishell
OBJ_DIR_MS			=	$(OBJS_DIR)/minishell
DEP_DIR_MS			=	$(DEPS_DIR)/minishell
SRC_DIR_EXEC		=	$(SRC_DIR)/execute
OBJ_DIR_EXEC		=	$(OBJS_DIR)/execute
DEP_DIR_EXEC		=	$(DEPS_DIR)/execute
SRC_DIR_BI			=	$(SRC_DIR)/built-ins
OBJ_DIR_BI			=	$(OBJS_DIR)/built-ins
DEP_DIR_BI			=	$(DEPS_DIR)/built-ins
SRC_DIR_PARSER		=	$(SRC_DIR)/parser
OBJ_DIR_PARSER		=	$(OBJS_DIR)/parser
DEP_DIR_PARSER		=	$(DEPS_DIR)/parser
SRC_DIR_TESTER		=	$(SRC_DIR)/tester
OBJ_DIR_TESTER		=	$(OBJS_DIR)/tester
DEP_DIR_TESTER		=	$(DEPS_DIR)/tester
