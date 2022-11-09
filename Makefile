FILES 	=	main.c 			\
			parser.c 		\
			token.c 		\
			options.c 		\
			files/f_dir.c 	\
			files/f_date.c 	\
			files/f_grep.c 	\
			files/f_mime.c 	\
			files/f_name.c 	\
			files/f_size.c 	\
			files/f_perm.c	\
			display.c 		\
			validation.c 	\
			errors.c 		\
			utils.c 		\
			mime.c 			\
			files.c 		\
			exec/exec.c		\
			exec/exec_1.c	\
			exec/exec_2.c	\
			exec/exec_3.c	\
			exec/exec_4.c	\
			exec/exec_5.c	\
			exec/exec_6.c	\
			t_arg.c			\
			entry.c

S_PATH	=	srcs/
O_PATH	=	objs/
I_PATH	=	includes/

SRCS	=	${addprefix ${S_PATH}, ${FILES}}
OBJS	=	${addprefix ${O_PATH}, ${FILES:.c=.o}}

CC		=	gcc

NAME	=	ftc

RM		=	rm -rf

CFLAGS	= 	-Werror -Wall -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -pthread

${O_PATH}%.o:	${S_PATH}%.c
				@mkdir -p ${dir $@}
				@${CC} ${CFLAGS} -c $< -o $@
				@echo "${BOLD}${CYAN}Compiling${S}${S} ${IGREY}$<${S} ${YELLOW}-> ${S}${SBLUE}$@${S} ⚙️"


${NAME}:			${OBJS}
					@${CC} ${OBJS} ${CFLAGS} -o ${NAME} -I ${I_PATH}
					@echo ""
					@echo "${BOLD}${PURPLE}Building${S}${S} ${IGREY}$@${S} 🖥️"
					@echo ""
					@echo "\033[3;92mCompilation is completed !${S} 🎉"

all:		${NAME}

clean:
			@${RM} ${O_PATH}*
			@echo "${BOLD}${SRED}Removing${S}${S} ${IGREY}${O_PATH}${S} 🗑️"

fclean:		clean
			@${RM} ${NAME}
			@echo "${BOLD}${SRED}Removing${S}${S} ${IGREY}${NAME}${S} 🗑️"

space:
			@echo " "

re:			fclean space all

.PHONY: all clean fclean re build space

S 		=		\033[0m
BOLD 	= 		\033[1m
ITALIC 	= 		\033[3m
UNDER 	= 		\033[4m
REV 	= 		\033[7m

# Colors
GREY 	= 		\033[30m
RED 	= 		\033[31m
GREEN	=		\033[32m
YELLOW	=		\033[33m
BLUE	=		\033[34m
PURPLE	=		\033[35m
CYAN	=		\033[36m
WHITE	=		\033[37m

SGREY	=		\033[90m
SRED	=		\033[91m
SGREEN	=		\033[92m
SYELLOW	=		\033[93m
SBLUE	=		\033[94m
SPURPLE	=		\033[95m
SCYAN	=		\033[96m
SWHITE	=		\033[97m

# Colored backgrounds

IGREY	=		\033[40m
IRED	=		\033[41m
IGREEN	=		\033[42m
IYELLOW	=		\033[43m
IBLUE	=		\033[44m
IPURPLE	=		\033[45m
ICYAN	=		\033[46m
IWHITE	=		\033[47m
