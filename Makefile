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

CFLAGS		:=
ifeq (${OS}, Windows_NT)
	CFLAGS	= 	-O0 -g3 -pthread -lregex
else
	CFLAGS	=	-Werror -Wall -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls -pthread
endif

ECHO_FLAG	:=
ifeq (${OS}, Windows_NT)
	ECHO_FLAG	=	-e
endif


${O_PATH}%.o:	${S_PATH}%.c
				@mkdir -p ${dir $@}
				@${CC} ${CFLAGS} -c $< -o $@
				@echo ${ECHO_FLAG} "${ESC}${BOLD}${ESC}${CYAN}Compiling${ESC}${S}${ESC}${S} ${ESC}${IGREY}$<${ESC}${S} ${ESC}${YELLOW}-> ${ESC}${S}${ESC}${SBLUE}$@${ESC}${S} ⚙️"


${NAME}:			${OBJS}
					@${CC} ${OBJS} ${CFLAGS} -o ${NAME} -I ${I_PATH}
					@echo ""
					@echo ${ECHO_FLAG} "${ESC}${BOLD}${ESC}${PURPLE}Building${ESC}${S}${ESC}${S} ${ESC}${IGREY}$@${ESC}${S} 🖥️"
					@echo ""
					@echo ${ECHO_FLAG} "${ESC}${ITALIC}${ESC}${SGREEN}Compilation is completed !${ESC}${S} 🎉"

all:		${NAME}

clean:
			@${RM} ${O_PATH}*
			@echo ${ECHO_FLAG} "${ESC}${BOLD}${ESC}${SRED}Removing${ESC}${S}${ESC}${S} ${ESC}${IGREY}${O_PATH}${ESC}${S} 🗑️"

fclean:		clean
			@${RM} ${NAME}
			@echo ${ECHO_FLAG} "${ESC}${BOLD}${ESC}${SRED}Removing${ESC}${S}${ESC}${S} ${ESC}${IGREY}${NAME}${ESC}${S} 🗑️"

space:
			@echo " "

re:			fclean space all

.PHONY: all clean fclean re build space

ESC		=		\033
S 		=		[0m
BOLD 	= 		[1m
ITALIC 	= 		[3m
UNDER 	= 		[4m
REV 	= 		[7m

# Colors
GREY 	= 		[30m
RED 	= 		[31m
GREEN	=		[32m
YELLOW	=		[33m
BLUE	=		[34m
PURPLE	=		[35m
CYAN	=		[36m
WHITE	=		[37m

SGREY	=		[90m
SRED	=		[91m
SGREEN	=		[92m
SYELLOW	=		[93m
SBLUE	=		[94m
SPURPLE	=		[95m
SCYAN	=		[96m
SWHITE	=		[97m

# Colored backgrounds
IGREY	=		[40m
IRED	=		[41m
IGREEN	=		[42m
IYELLOW	=		[43m
IBLUE	=		[44m
IPURPLE	=		[45m
ICYAN	=		[46m
IWHITE	=		[47m
