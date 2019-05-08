NAME		:=	doomnukem
SRC			:=	main.c \
				sdlpixels.c \
				get_next_line.c \
				tga.c			\
				resize_img.c	\
				tools.c		\
				tools2.c		\
				tools3.c		\
				events.c		\
				player_parsing.c \
				vertex_parsing.c \
				sector_parsing.c \
				vline.c \
				draw_screen.c \
				mini_map.c \
				draw_line.c\
				display_img.c \
				ui.c \
				init_ressources.c \
				draw_img.c \
				ui_comps.c \
				stand_ev.c\
				sprites.c \
				init_sprites.c \
				luminosity.c \
				start_menu.c \
				tools4.c \
				engine_interaction.c \
				init.c \
				ft_exit.c \
				setstring_tools.c \
				story_steps.c \
				move_ev.c \
				game_loop.c \
				init_in_draw.c \
				recycle.c \
				tga2.c \
				init_isec_pside.c \
				sector_parsing2.c
# directories :
OBJDIR 		:=	objs
INCDIR  	:=	includes
# LIBFT
VPATH		:= ./srcs:./srcs/parsing:./srcs/render:./srcs/tools:./srcs/init:./srcs/ui:./srcs/events:
LFT_NAME	:=	libft.a
LFT_PATH	:=	./libft
LFT_LIB		:=	-L $(LFT_PATH) -lft
LFT_INC		:=	-I $(LFT_PATH)
LFT_RULE	:=	$(LFT_PATH)/$(LFT_NAME)
# SDL
LSDL_LIB	:=	$(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LSDL_INC	:=	$(shell sdl2-config --cflags)
# **************************************************************************** #
OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.d))
LIB			:=	$(LFT_LIB) $(LSDL_LIB)
INC			:=	-I $(INCDIR) $(LFT_INC) $(LSDL_INC)
# **************************************************************************** #
CC			:=	clang
CFLAGS		:=  -g3 -Wall -Wextra -Werror
# **************************************************************************** #
all : $(NAME)
.PHONY: all
$(NAME): $(OBJ) $(LFT_RULE)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC) $(LIB)
	@echo "\033[1;34;2m <(^o^)> - MAMA HE LIMPIADO MI DORMITORIO PERFECTAMENTE ~\033[0m"
	@echo "\033[0;31;3m                        (ALL RULE DONE)                               ~ (__)=3 ~\033[0m"
-include $(DEP)
$(LFT_RULE):
	@$(MAKE) -C $(LFT_PATH)/
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir $(OBJDIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) -MMD -c -o $@ $< $(INC)

clean :
	@$(MAKE) -C $(LFT_PATH) clean
	@rm -f $(OBJ)
	@rm -f $(DEP)
	@echo "\033[1;33;2m <(^o^)> - MAMA HE COMIDO TODAS LAS PATATAS, PUEDO JUGAR A SMASHBROS ? \033[0m"
	@echo "\033[0;31;3m                        (CLEAN RULE DONE)                             ~ (__)=3 ~ \033[0m"
.PHONY: clean
fclean : clean
	@$(MAKE) -C $(LFT_PATH) fclean
	@rm -f $(NAME)
	@echo "\033[1;31;2m J^_^L - SEGURO MI PEQUEÑITO SEBASTIAN, PERO LIMPIES TU CUARTO ANTES ~\033[0m"
	@echo "\033[0;31;3m                        (FCLEAN RULE DONE)                            ~ (__)=3  ~\033[0m"
.PHONY: fclean
re : fclean all
	@echo "\033[0;35;2m J^_^L - MUY BIEN, LAVAS LOS PLATOS AHORA ~"
	@echo "\033[0;31;3m                        (RE RULE DONE)                                ~ (__)=3  ~\033[0m"
.PHONY: re
