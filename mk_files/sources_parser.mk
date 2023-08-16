# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_parser.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 19:06:12 by vduchi            #+#    #+#              #
#    Updated: 2023/08/16 18:46:30 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PARSER	=	srcs/parser/parser.c
SRCS_PARSER	+=	srcs/parser/env_var.c
SRCS_PARSER	+=	srcs/parser/pars_utils.c
SRCS_PARSER	+=	srcs/parser/handle_words.c
SRCS_PARSER	+=	srcs/parser/redirections.c
SRCS_PARSER	+=	srcs/parser/cmd_and_args.c
SRCS_PARSER	+=	srcs/parser/create_tokens.c
SRCS_PARSER	+=	srcs/parser/handle_quotes.c

OBJS_PARSER	=	$(patsubst $(SRC_DIR_PARSER)/%, $(OBJ_DIR_PARSER)/%, $(SRCS_PARSER:.c=.o))
DEPS_PARSER	=	$(patsubst $(SRC_DIR_PARSER)/%, $(DEP_DIR_PARSER)/%, $(SRCS_PARSER:.c=.d))

